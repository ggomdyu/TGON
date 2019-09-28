#include "PrecompiledHeader.h"

#include <Windows.h>

#include "Diagnostics/Debug.h"
#include "Misc/Algorithm.h"
#include "String/Encoding.h"

#include "../FileStream.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 32767> g_tempUtf16Buffer;

namespace
{

HANDLE CreateFileOpenHandle(const std::string_view& path, FileMode mode, FileAccess access, FileShare share, FileOptions options)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return {};
    }

    auto desiredAccess = (access == FileAccess::Read) ? GENERIC_READ : (access == FileAccess::Write) ? GENERIC_WRITE : GENERIC_READ | GENERIC_WRITE;

    bool useSecurityAttributes = UnderlyingCast(share) & UnderlyingCast(FileShare::Inheritable);
    SECURITY_ATTRIBUTES securityAttributes {};
    if (useSecurityAttributes)
    {
        if ((UnderlyingCast(share) & UnderlyingCast(FileShare::Inheritable)) != 0)
        {
            securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
            securityAttributes.bInheritHandle = TRUE;
        }
    }
    
    // The named pipe on Windows allows the server to impersonate the client.
    // So we have to add the below flags because of this security vulnerability.
    DWORD flagsAndAttributes = UnderlyingCast(options) | SECURITY_SQOS_PRESENT | SECURITY_ANONYMOUS;

    return CreateFileW(reinterpret_cast<LPCWSTR>(g_tempUtf16Buffer.data()), desiredAccess, static_cast<DWORD>(share), useSecurityAttributes ? &securityAttributes : nullptr, static_cast<DWORD>(mode), flagsAndAttributes, nullptr);
}

} /* namespace */

FileStream::FileStream(const std::string_view& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, FileOptions options) :
    m_nativeHandle(CreateFileOpenHandle(path, mode, access, share, options)),
    m_bufferSize(bufferSize),
    m_readPos(0),
    m_readLen(0),
    m_writePos(0),
    m_filePos(0),
    m_access(access),
    m_fileName(path)
{
    if (m_nativeHandle == INVALID_HANDLE_VALUE)
    {
        Debug::Fail("Failed to construct the FileStream.", "Could not create the file handle.");
    }

    if (GetFileType(m_nativeHandle) != FILE_TYPE_DISK)
    {
        Debug::Fail("Failed to construct the FileStream.", "The FileStream instance is not a file.");
    }
}

bool FileStream::IsClosed() const noexcept
{
    return m_nativeHandle == INVALID_HANDLE_VALUE;
}

int64_t FileStream::Length() const
{
    LARGE_INTEGER li;
    if (GetFileSizeEx(m_nativeHandle, &li) == FALSE)
    {
        return -1;
    }

    int64_t length = li.QuadPart;
    if (m_filePos + m_writePos > length)
    {
        length = m_filePos + m_writePos;
    }

    return length;
}

void FileStream::Close()
{
    this->FlushWriteBuffer();

    if (m_nativeHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_nativeHandle);
        m_nativeHandle = INVALID_HANDLE_VALUE;
    }
}

void FileStream::FlushWriteBuffer()
{
    if (m_writePos <= 0)
    {
        return;
    }

    this->WriteCore(&m_buffer[0], m_writePos);

    m_writePos = 0;
}

int32_t FileStream::ReadCore(std::byte* buffer, int32_t count)
{
    DWORD readBytes = 0;
    if (ReadFile(m_nativeHandle, buffer, count, &readBytes, nullptr) == FALSE)
    {
        return -1;
    }

    m_filePos += readBytes;
    return readBytes;
}

int32_t FileStream::WriteCore(const std::byte* buffer, int32_t bufferBytes)
{
    DWORD writtenBytes = 0;
    if (WriteFile(m_nativeHandle, buffer, bufferBytes, &writtenBytes, nullptr) == FALSE)
    {
        return -1;
    }

    m_filePos += writtenBytes;
    return writtenBytes;
}

int64_t FileStream::SeekCore(int64_t offset, SeekOrigin origin)
{
    LARGE_INTEGER distanceToMove;
    distanceToMove.QuadPart = offset;

    LARGE_INTEGER newFilePointer;
    if (SetFilePointerEx(m_nativeHandle, distanceToMove, &newFilePointer, static_cast<DWORD>(origin)) == FALSE)
    {
        return -1;
    }

    m_filePos = newFilePointer.QuadPart;

    return newFilePointer.QuadPart;
}

bool FileStream::SetLengthCore(int64_t value)
{
    auto prevFilePos = m_filePos;
    if (m_filePos != value)
    {
        if (this->SeekCore(value, SeekOrigin::Begin) == -1)
        {
            return false;
        }
    }

    if (SetEndOfFile(m_nativeHandle) == FALSE)
    {
        return false;
    }

    if (prevFilePos != value)
    {
        if (value <= prevFilePos)
        {
            if (this->SeekCore(0, SeekOrigin::End) == false)
            {
                return false;
            }
        }
        else
        {
            // Roll back the seek position
            if (this->SeekCore(prevFilePos, SeekOrigin::Begin))
            {
                return false;
            }
        }
    }

    return true;
}

void FileStream::FlushCore()
{
    FlushFileBuffers(m_nativeHandle);
}

} /* namespace tgon */

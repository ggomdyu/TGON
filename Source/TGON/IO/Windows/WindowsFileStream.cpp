#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "String/Encoding.h"
#include "Misc/Algorithm.h"
#include "Diagnostics/Debug.h"

#include "../FileStream.h"

namespace tgon
{
namespace
{

HANDLE CreateFileOpenHandle(const std::string& path, FileMode mode, FileAccess access, FileShare share, FileOptions options)
{
    auto utf16Path = Encoding<UTF8>::ConvertTo<UTF16LE>(std::string_view(path));
    auto desiredAccess = (access == FileAccess::Read) ? GENERIC_READ : (access == FileAccess::Write) ? GENERIC_WRITE : GENERIC_READ | GENERIC_WRITE;

    bool useSecurityAttributes = UnderlyingCast(share) & UnderlyingCast(FileShare::Inheritable);
    SECURITY_ATTRIBUTES securityAttributes{};
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

    return CreateFileW(reinterpret_cast<LPCWSTR>(utf16Path.data()), desiredAccess, static_cast<DWORD>(share), useSecurityAttributes ? &securityAttributes : nullptr, static_cast<DWORD>(mode), flagsAndAttributes, nullptr);
}

}

FileStream::FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, FileOptions options) :
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

int64_t FileStream::Seek(int64_t offset, SeekOrigin origin)
{
    if (this->CanSeek() == false)
    {
        return -1;
    }

    if (m_writePos > 0)
    {
        this->FlushWriteBuffer();
    }
    else if (origin == SeekOrigin::Current)
    {
        // If we've read the buffer once before, then the seek offset is automatically moved to the end of the buffer.
        // So we must adjust the offset to set the seek offset as required.
        offset -= m_readLen - m_readPos;
    }

    m_readPos = m_readLen = 0;

    return SeekCore(offset, origin);
}

int64_t FileStream::Length() const
{
    LARGE_INTEGER li;
    if (GetFileSizeEx(m_nativeHandle, &li) == FALSE)
    {
        return -1;
    }

    DWORD lowPart = 0, highPart = 0;
    if ((lowPart = GetFileSize(m_nativeHandle, &highPart)) == -1)
    {
        return -1;
    }

    int64_t length = li.QuadPart;
    if (m_filePos + m_writePos > li.QuadPart)
    {
        length = m_filePos + m_writePos;
    }

    return length;
}

void FileStream::Close()
{
    if (m_writePos == 0)
    {
        return;
    }

    this->FlushWriteBuffer();

    if (m_nativeHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_nativeHandle);
        m_nativeHandle = INVALID_HANDLE_VALUE;
    }
}

int32_t FileStream::ReadCore(uint8_t* buffer, int32_t count)
{
    DWORD readBytes = 0;
    if (ReadFile(m_nativeHandle, buffer, count, &readBytes, nullptr) == FALSE)
    {
        return -1;
    }

    m_filePos += readBytes;
    return readBytes;
}

int32_t FileStream::WriteCore(const uint8_t* buffer, int32_t bufferBytes)
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

}
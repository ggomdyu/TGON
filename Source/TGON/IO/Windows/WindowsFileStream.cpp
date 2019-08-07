#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "String/Encoding.h"
#include "Diagnostics/Debug.h"
#include "Misc/Algorithm.h"
#include "Misc/Windows/SafeFileHandle.h"

#include "../FileStream.h"

namespace tgon
{
namespace
{

HANDLE CreateFileOpenHandle(const std::string& path, FileMode mode, FileAccess access, FileShare share, FileOptions options)
{
    auto utf16Path = Encoding<UTF8>::ConvertTo<UTF16LE>(std::string_view(path));

    DWORD desiredAccess = (UnderlyingCast(access) & UnderlyingCast(FileAccess::Read)) ? GENERIC_READ : (UnderlyingCast(access) & UnderlyingCast(FileAccess::Write)) ? GENERIC_WRITE : GENERIC_READ | GENERIC_WRITE;

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

//int32_t NativeWriteFile(HANDLE handle, uint8_t* buffer, )
//{
//
//}

} /* namespace */

FileStream::FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, FileOptions options) :
    m_nativeHandle(CreateFileOpenHandle(path, mode, access, share, options)),
    m_bufferSize(bufferSize),
    m_readPos(0),
    m_writePos(0),
    m_canSeek(false),
    m_isUseAsync(false),
    m_access(access),
    m_fileName(path)
{
    if (m_nativeHandle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (GetFileType(m_nativeHandle) != FILE_TYPE_DISK)
    {
        Debug::Fail("Failed to construct the FileStream.", "The FileStream is not a file.");
        return;
    }
}

FileStream::~FileStream()
{
    if (m_nativeHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_nativeHandle);
        m_nativeHandle = INVALID_HANDLE_VALUE;
    }
}

const std::string& FileStream::Name() const noexcept
{
    return m_fileName;
}

bool FileStream::IsClosed() const noexcept
{
    return m_nativeHandle == INVALID_HANDLE_VALUE;
}

void FileStream::FlushWriteBuffer()
{
    
    m_writePos = 0;
}

void FileStream::FlushWriteBufferAsync()
{
    m_writePos = 0;
}

int64_t FileStream::Seek(int64_t offset, SeekOrigin origin)
{
    return 0;
}

void FileStream::Close()
{
}

} /* namespace tgon */

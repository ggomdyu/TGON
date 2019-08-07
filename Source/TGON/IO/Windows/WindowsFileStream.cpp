#include "..\FileStream.h"
#include "..\FileStream.h"
#include "PrecompiledHeader.h"

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
    // So we have to add the below flags because of the security vulnerability.
    DWORD flagsAndAttributes = UnderlyingCast(options) | SECURITY_SQOS_PRESENT | SECURITY_ANONYMOUS;

    return CreateFileW(reinterpret_cast<LPCWSTR>(utf16Path.data()), desiredAccess, static_cast<DWORD>(share), useSecurityAttributes ? &securityAttributes : nullptr, static_cast<DWORD>(mode), flagsAndAttributes, nullptr);
}

} /* namespace */

FileStream::FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, FileOptions options) :
    m_nativeHandle(CreateFileOpenHandle(path, mode, access, share, options)),
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

void FileStream::Write( uint8_t * buffer, int32_t offset, int32_t count )
{
}
void tgon::FileStream::WriteByte( uint8_t value )
{
}

bool FileStream::IsClosed() const noexcept
{
    return m_nativeHandle == INVALID_HANDLE_VALUE;
}

} /* namespace tgon */

#include "PrecompiledHeader.h"

#include "Misc/Algorithm.h"

#include "FileStream.h"

namespace tgon
{

FileStream::FileStream(const std::string& path, FileMode mode) :
    FileStream(path, mode, (mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite), DefaultShare, DefaultBufferSize, DefaultIsAsync)
{
}

FileStream::FileStream(const std::string& path, FileMode mode, FileAccess access) :
    FileStream(path, mode, access, DefaultShare, DefaultBufferSize, DefaultIsAsync)
{
}

FileStream::FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share) :
    FileStream(path, mode, access, share, DefaultBufferSize, DefaultIsAsync)
{
}

FileStream::FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize) :
    FileStream(path, mode, access, share, bufferSize, DefaultIsAsync)
{
}

FileStream::FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, bool isUseAsync) :
    FileStream(path, mode, access, share, bufferSize, isUseAsync ? FileOptions::Asynchronous : FileOptions::None)
{
}

bool FileStream::operator==(const FileStream& rhs) const noexcept
{
    return m_nativeHandle == rhs.m_nativeHandle;
}

bool FileStream::operator!=(const FileStream& rhs) const noexcept
{
    return !this->operator==(rhs);
}

bool FileStream::CanRead() const
{
    return this->IsClosed() == false && (UnderlyingCast(m_access) & UnderlyingCast(FileAccess::Read)) != 0;
}

bool FileStream::CanWrite() const
{
    return this->IsClosed() == false && (UnderlyingCast(m_access) & UnderlyingCast(FileAccess::Write)) != 0;
}

} /* namespace tgon */

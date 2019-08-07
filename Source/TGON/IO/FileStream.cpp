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

bool FileStream::CanSeek() const
{
    // TODO: impl
    return false;
}

bool FileStream::CanWrite() const
{
    return this->IsClosed() == false && (UnderlyingCast(m_access) & UnderlyingCast(FileAccess::Write)) != 0;
}

bool FileStream::IsAsync() const
{
    // TODO: impl
    return false;
}

void FileStream::SetLength(int64_t value)
{
    // TODO: impl
}

int64_t FileStream::Length() const
{
    // TODO: impl
    return int64_t();
}

int64_t FileStream::Position() const
{
    // TODO: impl
    return int64_t();
}

std::vector<uint8_t>& FileStream::GetBuffer() noexcept
{
    if (m_buffer.size() == 0)
    {
        m_buffer.resize(m_bufferSize);
    }

    return m_buffer;
}

int32_t FileStream::Read(uint8_t* buffer, int32_t offset, int32_t count)
{
    // TODO: impl
    return 0;
}

int32_t FileStream::ReadByte()
{
    // TODO: impl
    return 0;
}

bool FileStream::Write(uint8_t* buffer, int32_t offset, int32_t count)
{
    if (this->CanWrite() == false)
    {
        return false;
    }
    // TODO: impl
    return true;
}

bool FileStream::WriteByte(uint8_t value)
{
    if (this->CanWrite() == false)
    {
        return false;
    }

    if (m_writePos == m_bufferSize)
    {
        this->FlushWriteBuffer();
    }

    this->GetBuffer()[m_writePos++] = value;

    return true;
}

} /* namespace tgon */

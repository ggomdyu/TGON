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

FileStream::~FileStream()
{
    FileStream::Close();
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
    return this->IsClosed() == false;
}

bool FileStream::CanWrite() const
{
    return this->IsClosed() == false && (UnderlyingCast(m_access) & UnderlyingCast(FileAccess::Write)) != 0;
}

void FileStream::SetLength(int64_t value)
{
    // TODO: impl
}

int64_t FileStream::Position() const
{
    return m_filePos + m_writePos;
}

const std::string& FileStream::Name() const noexcept
{
    return m_fileName;
}

std::vector<uint8_t>& FileStream::GetBuffer() noexcept
{
    if (m_buffer.empty())
    {
        m_buffer.resize(m_bufferSize);
    }

    return m_buffer;
}

int32_t FileStream::ReadByte()
{
    if (this->CanRead() == false)
    {
        return -1;
    }

    int32_t leftReadBufferSpace = m_readLen - m_readPos;
    if (leftReadBufferSpace == 0)
    {
        this->FlushWriteBuffer();

        auto readBytes = this->ReadCore(&this->GetBuffer()[0], m_bufferSize);
        m_readPos = 0;
        m_readLen = readBytes;

        if (readBytes == 0)
        {
            return -1;
        }
    }

    return m_buffer[m_readPos++];;
}

int32_t FileStream::Read(uint8_t* buffer, int32_t count)
{
    if (this->CanRead() == false || m_bufferSize < count)
    {
        return -1;
    }

    int32_t leftReadBufferSpace = m_readLen - m_readPos;
    if (leftReadBufferSpace == 0)
    {
        this->FlushWriteBuffer();
    
        auto readBytes = this->ReadCore(&this->GetBuffer()[0], m_bufferSize);
        m_readPos = 0;
        m_readLen = leftReadBufferSpace = readBytes;

        if (readBytes == 0)
        {
            return -1;
        }
    }
    
    int32_t copiedBytes = std::min(leftReadBufferSpace, count);
    std::memcpy(buffer, &m_buffer[0] + m_readPos, copiedBytes);

    // Copied less than the required bytes?
    if (copiedBytes < count)
    {
        int32_t moreReadBytes = this->ReadCore(buffer + m_readPos + copiedBytes, count - copiedBytes);
        copiedBytes += moreReadBytes;

        m_readLen = 0;
        m_readPos = 0;
    }

    m_readPos += copiedBytes;

    return copiedBytes;
}

bool FileStream::WriteByte(uint8_t value)
{
    if (m_writePos == 0)
    {
        if (this->CanWrite() == false)
        {
            return false;
        }

        // todo: Flush read buffer
        m_readLen = 0;
        m_readPos = 0;
    }
    if (m_writePos == m_bufferSize)
    {
        this->FlushWriteBuffer();
    }

    this->GetBuffer()[m_writePos++] = value;

    return true;
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

} /* namespace tgon */
#include "PrecompiledHeader.h"

#include "Misc/Algorithm.h"

#include "FileStream.h"

namespace tgon
{

FileStream::FileStream(const char* path, FileMode mode) :
    FileStream(path, mode, (mode == FileMode::Append ? FileAccess::Write : FileAccess::ReadWrite), DefaultShare, DefaultBufferSize, DefaultFileOption)
{
}

FileStream::FileStream(const char* path, FileMode mode, FileAccess access) :
    FileStream(path, mode, access, DefaultShare, DefaultBufferSize, DefaultFileOption)
{
}

FileStream::FileStream(const char* path, FileMode mode, FileAccess access, FileShare share) :
    FileStream(path, mode, access, share, DefaultBufferSize, DefaultFileOption)
{
}

FileStream::FileStream(const char* path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize) :
    FileStream(path, mode, access, share, bufferSize, DefaultFileOption)
{
}

FileStream::FileStream(FileStream&& rhs) noexcept :
    m_nativeHandle(rhs.m_nativeHandle),
    m_buffer(std::move(rhs.m_buffer)),
    m_bufferSize(rhs.m_bufferSize),
    m_readPos(rhs.m_readPos),
    m_readLen(rhs.m_readLen),
    m_writePos(rhs.m_writePos),
    m_filePos(rhs.m_filePos),
    m_access(rhs.m_access),
    m_fileName(std::move(rhs.m_fileName))
{
    rhs.m_nativeHandle = nullptr;
    rhs.m_bufferSize = 0;
    rhs.m_readPos = 0;
    rhs.m_readLen = 0;
    rhs.m_writePos = 0;
    rhs.m_filePos = 0;
}

FileStream::~FileStream()
{
    this->Close();
}

FileStream& FileStream::operator=(FileStream&& rhs) noexcept
{
    this->Close();
    
    m_nativeHandle = rhs.m_nativeHandle;
    m_buffer = std::move(rhs.m_buffer);
    m_bufferSize = rhs.m_bufferSize;
    m_readPos = rhs.m_readPos;
    m_readLen = rhs.m_readLen;
    m_writePos = rhs.m_writePos;
    m_filePos = rhs.m_filePos;
    m_access = rhs.m_access;
    m_fileName = std::move(rhs.m_fileName);

    rhs.m_nativeHandle = nullptr;
    rhs.m_bufferSize = 0;
    rhs.m_readPos = 0;
    rhs.m_readLen = 0;
    rhs.m_writePos = 0;
    rhs.m_filePos = 0;

    return *this;
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

bool FileStream::SetLength(int64_t value)
{
    if (CanRead() == false || CanWrite() == false)
    {
        return false;
    }

    // If the write buffer is not empty
    if (m_writePos > 0)
    {
        this->FlushWriteBuffer();
    }
    // If the read buffer is not empty
    else if (m_readPos < m_readLen)
    {
        this->FlushReadBuffer();
    }

    return this->InternalSetLength(value);
}

int64_t FileStream::Position() const
{
    return m_filePos + m_writePos;
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
    
    return InternalSeek(offset, origin);
}

const std::string& FileStream::Name() const noexcept
{
    return m_fileName;
}

void FileStream::Flush()
{
    this->Flush(false);
}

std::vector<std::byte>& FileStream::GetBuffer() noexcept
{
    if (m_buffer.empty())
    {
        m_buffer.resize(m_bufferSize);
    }

    return m_buffer;
}

int32_t FileStream::Read(std::byte* buffer, int32_t count)
{
    if (this->CanRead() == false || m_bufferSize < count)
    {
        return -1;
    }

    int32_t leftReadBufferSpace = m_readLen - m_readPos;
    if (leftReadBufferSpace == 0)
    {
        this->FlushWriteBuffer();
    
        auto readBytes = this->InternalRead(&this->GetBuffer()[0], m_bufferSize);
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
        int32_t moreReadBytes = this->InternalRead(buffer + m_readPos + copiedBytes, count - copiedBytes);
        copiedBytes += moreReadBytes;

        m_readLen = 0;
        m_readPos = 0;
    }

    m_readPos += copiedBytes;

    return copiedBytes;
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

        auto readBytes = this->InternalRead(&this->GetBuffer()[0], m_bufferSize);
        m_readPos = 0;
        m_readLen = readBytes;

        if (readBytes == 0)
        {
            return -1;
        }
    }

    return static_cast<int32_t>(m_buffer[m_readPos++]);
}

bool FileStream::Write(const std::byte* buffer, int32_t count)
{
    if (this->CanWrite() == false)
    {
        return false;
    }

    this->FlushReadBuffer();

    if (m_writePos > 0)
    {
        int32_t numBytes = m_bufferSize - m_writePos;
        if (numBytes > 0)
        {
            // If the specified buffer can be stored into the m_buffer directly
            if (count <= numBytes)
            {
                std::memcpy(&GetBuffer()[m_writePos], buffer, count);
                m_writePos += count;
                return true;
            }
            else
            {
                std::memcpy(&GetBuffer()[m_writePos], buffer, static_cast<size_t>(numBytes));
                m_writePos += numBytes;
                buffer += numBytes;
                count -= numBytes;
            }
        }

        this->FlushWriteBuffer();
    }

    if (m_bufferSize < count)
    {
        this->InternalWrite(buffer, count);
        return true;
    }

    std::memcpy(&GetBuffer()[m_writePos], buffer, count);
    m_writePos += count;

    return true;
}

bool FileStream::WriteByte(std::byte value)
{
    if (this->CanWrite() == false)
    {
        return false;
    }

    this->FlushReadBuffer();

    if (m_writePos == m_bufferSize)
    {
        this->FlushWriteBuffer();
    }

    this->GetBuffer()[m_writePos++] = value;

    return true;
}

void FileStream::FlushReadBuffer()
{
    if (m_writePos != 0)
    {
        return;
    }

    // We must rewind the seek pointer if a write occured.
    int32_t rewindOffset = m_readPos - m_readLen;
    if (rewindOffset != 0)
    {
        this->InternalSeek(rewindOffset, SeekOrigin::Current);
    }

    m_readLen = m_readPos = 0;
}

void FileStream::Flush(bool flushToDisk)
{
    if (m_writePos > 0 && this->CanWrite())
    {
        this->FlushWriteBuffer();
    }
    else if (m_readPos < m_readLen && this->CanSeek())
    {
        this->FlushReadBuffer();
    }

    if (flushToDisk)
    {
        this->InternalFlush();
    }
}

} /* namespace tgon */
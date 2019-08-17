#include "PrecompiledHeader.h"

#include <cstdio>

#include "Diagnostics/Debug.h"

#include "../FileStream.h"
#include "../File.h"

namespace tgon
{
namespace
{
    
constexpr const char* ConvertFileModeAccessToNative(FileMode mode, FileAccess access)
{
    constexpr const char* fopenModeTable[][3] = {
        {nullptr, "wb", "wb+"},
        {nullptr, "wb", "wb+"},
        {"rb", "wb", "rb+"},
        {"rb", "wb", "rb+"},
        {nullptr, "wb", "wb+"},
        {nullptr, "ab", "ab+"},
    };

    return fopenModeTable[static_cast<int32_t>(mode) - 1][static_cast<int32_t>(access) - 1];
}

FILE* CreateFileOpenHandle(const std::string& path, FileMode mode, FileAccess access)
{
    if (mode == FileMode::OpenOrCreate && File::Exists(path) == false)
    {
        FileStream(path, FileMode::CreateNew);
    }

    return fopen(path.data(), ConvertFileModeAccessToNative(mode, access));
}

} /* namespace */

FileStream::FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, FileOptions options) :
    m_nativeHandle(CreateFileOpenHandle(path, mode, access)),
    m_bufferSize(bufferSize),
    m_readPos(0),
    m_readLen(0),
    m_writePos(0),
    m_filePos(0),
    m_access(access),
    m_fileName(path)
{
}

bool FileStream::IsClosed() const noexcept
{
    return m_nativeHandle == nullptr;
}

int64_t FileStream::Length() const
{
    FILE* nativeHandle = reinterpret_cast<FILE*>(m_nativeHandle);
    
    auto prevSeekOffset = ftell(nativeHandle);
    fseek(nativeHandle, 0, SEEK_END);
    
    auto length = ftell(nativeHandle);
    fseek(nativeHandle, prevSeekOffset, SEEK_SET);
    
    if (m_filePos + m_writePos > length)
    {
        length = m_filePos + m_writePos;
    }

    return length;
}

void FileStream::Close()
{
    this->FlushWriteBuffer();

    if (m_nativeHandle != nullptr)
    {
        fclose(reinterpret_cast<FILE*>(m_nativeHandle));
        m_nativeHandle = nullptr;
    }
}

void FileStream::FlushWriteBuffer()
{
    if (m_writePos <= 0)
    {
        return;
    }

    this->WriteCore(&m_buffer[0], m_writePos);

    fflush(reinterpret_cast<FILE*>(m_nativeHandle));

    m_writePos = 0;
}

int32_t FileStream::ReadCore(uint8_t* buffer, int32_t count)
{
    auto readBytes = fread(buffer, 1, count, reinterpret_cast<FILE*>(m_nativeHandle));
    if (readBytes == static_cast<decltype(readBytes)>(-1))
    {
        return -1;
    }
    
    m_filePos += readBytes;
    return readBytes;
}

int32_t FileStream::WriteCore(const uint8_t* buffer, int32_t count)
{
    auto writtenBytes = fwrite(buffer, 1, count, reinterpret_cast<FILE*>(m_nativeHandle));
    if (writtenBytes == static_cast<decltype(writtenBytes)>(-1))
    {
        return -1;
    }

    m_filePos += writtenBytes;
    return writtenBytes;
}

int64_t FileStream::SeekCore(int64_t offset, SeekOrigin origin)
{
    auto nativeHandle = reinterpret_cast<FILE*>(m_nativeHandle);
    auto result = fseek(nativeHandle, offset, static_cast<int>(origin));
    if (result != 0)
    {
        return -1;
    }

    int64_t newFilePos = ftell(nativeHandle);
    if (newFilePos == -1)
    {
        return -1;
    }
    
    m_filePos = newFilePos;

    return newFilePos;
}

bool FileStream::SetLengthCore(int64_t value)
{
    return false;
}

void FileStream::FlushCore()
{
    fflush(reinterpret_cast<FILE*>(m_nativeHandle));
}

} /* namespace tgon */

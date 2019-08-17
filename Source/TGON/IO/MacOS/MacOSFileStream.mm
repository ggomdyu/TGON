#import "PrecompiledHeader.h"

#import <cstdio>

#import "Misc/Algorithm.h"
#import "Diagnostics/Debug.h"

#import "../FileStream.h"

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
    
    return fopenModeTable[static_cast<int32_t>(mode)][static_cast<int32_t>(access)];
}
//
//long ConvertSeekOriginToNative(SeekOrigin seekOrigin)
//{
//    constexpr const char* fopenModeTable[][3] = {
//        {nullptr, "wb", "wb+"},
//        {nullptr, "wb", "wb+"},
//        {"rb", "wb", "rb+"},
//        {"rb", "wb", "rb+"},
//        {nullptr, "wb", "wb+"},
//        {nullptr, "ab", "ab+"},
//    };
//
//    return fopenModeTable[static_cast<int32_t>(mode)][static_cast<int32_t>(access)];
//}

FILE* CreateFileOpenHandle(const std::string& path, FileMode mode, FileAccess access)
{
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

int64_t FileStream::ReadCore(uint8_t* buffer, int64_t count)
{
    auto readBytes = fread(buffer, 1, count, reinterpret_cast<FILE*>(m_nativeHandle));
    if (readBytes == -1)
    {
        return -1;
    }
    
    m_filePos += readBytes;
    return readBytes;
}

int64_t FileStream::WriteCore(const uint8_t* buffer, int64_t bufferBytes)
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
    FlushFileBuffers(m_nativeHandle);
}

} /* namespace tgon */

/**
 * @file    FileStream.h
 * @author  ggomdyu
 * @since   08/04/2019
 */

#pragma once
#include <vector>
#include <string>

#include "Stream.h"

namespace tgon
{

enum class FileMode
{
    CreateNew = 1,
    Create = 2,
    Open = 3,
    OpenOrCreate = 4,
    Truncate = 5,
    Append = 6,
};

enum class FileAccess
{
    Read = 1,
    Write = 2,
    ReadWrite = 3
};

enum class FileShare
{
    None = 0,
    Read = 1,
    Write = 2,
    ReadWrite = 3,
    Delete = 4,
    Inheritable = 16
};

enum class FileOptions
{
    WriteThrough = std::numeric_limits<int>::min(),
    None = 0,
    Encrypted = 16384,
    DeleteOnClose = 67108864,
    SequentialScan = 134217728,
    RandomAccess = 268435456,
    Asynchronous = 1073741824
};

class TGON_API FileStream :
    public Stream
{
/**@section Constructor */
public:
    FileStream(const std::string& path, FileMode mode);
    FileStream(const std::string& path, FileMode mode, FileAccess access);
    FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share);
    FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize);
    FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, bool isUseAsync);
    FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, FileOptions options);
    FileStream(FileStream&& rhs) noexcept;

/**@section Destructor */
public:
    virtual ~FileStream() override;
    
/**@section Operator */
public:
    FileStream& operator=(FileStream&& rhs) noexcept;
    bool operator==(const FileStream& rhs) const noexcept;
    bool operator!=(const FileStream& rhs) const noexcept;

/**@section Method */
public:
    virtual bool CanRead() const override;
    virtual bool CanSeek() const override;
    virtual bool CanWrite() const override;
    virtual bool SetLength(int64_t value) override;
    virtual int64_t Length() const override;
    virtual int64_t Position() const override;
    virtual int64_t Read(uint8_t* buffer, int64_t count) override;
    virtual int32_t ReadByte() override;
    virtual bool Write(const uint8_t* buffer, int64_t count) override;
    virtual bool WriteByte(uint8_t value) override;
    virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;
    virtual void Close() override;
    const std::string& Name() const noexcept;
    virtual void Flush() override;
    void Flush(bool flushToDisk);
    /*
    virtual void Lock(long position, long length)
    virtual void Unlock(long position, long length)
    */

protected:
    bool IsClosed() const noexcept;
    std::vector<uint8_t>& GetBuffer() noexcept;
    void FlushWriteBuffer();
    void FlushReadBuffer();
    int64_t ReadCore(uint8_t* buffer, int64_t count);
    int64_t WriteCore(const uint8_t* buffer, int64_t count);
    int64_t SeekCore(int64_t offset, SeekOrigin origin);
    void FlushCore();
    bool SetLengthCore(int64_t value);

/**@section Variable */
protected:
    static constexpr FileShare DefaultShare = FileShare::Read;
    static constexpr bool DefaultIsAsync = false;
    static constexpr int DefaultBufferSize = 4096;

    void* m_nativeHandle;
    std::vector<uint8_t> m_buffer;
    int64_t m_bufferSize;
    int64_t m_readPos;
    int64_t m_readLen;
    int64_t m_writePos;
    int64_t m_filePos;
    FileAccess m_access;
    std::string m_fileName;    
};

} /* namespace tgon */

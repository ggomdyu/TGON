/**
 * @file    FileStream.h
 * @author  ggomdyu
 * @since   08/04/2019
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <numeric>
#include <vector>

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
    public Stream,
    private boost::noncopyable
{
/**@section Constructor */
public:
    FileStream(const std::string& path, FileMode mode);
    FileStream(const std::string& path, FileMode mode, FileAccess access);
    FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share);
    FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize);
    FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, bool isUseAsync);
    FileStream(const std::string& path, FileMode mode, FileAccess access, FileShare share, int32_t bufferSize, FileOptions options);
    FileStream(FileStream&& rhs);

/**@section Destructor */
public:
    ~FileStream();
    
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
    virtual bool IsAsync() const;
    virtual void SetLength(int64_t value) override;
    virtual int64_t Length() const override;
    virtual int64_t Position() const override;
    const std::string& Name() const noexcept;
    virtual int Read(uint8_t* buffer, int32_t offset, int32_t count) override;
    virtual int32_t ReadByte() override;
    virtual void Write(uint8_t* buffer, int32_t offset, int32_t count) override;
    virtual void WriteByte(uint8_t value) override;
    virtual long Seek(int64_t offset, SeekOrigin origin) override;
    virtual void Close() override;
    /*virtual SafeFileHandle SafeFileHandle
    FileStream(SafeFileHandle handle, FileAccess access)
    FileStream(SafeFileHandle handle, FileAccess access, int bufferSize)
    FileStream(SafeFileHandle handle, FileAccess access, int bufferSize, bool isAsync)
    override IAsyncResult BeginRead(byte[] array, int offset, int numBytes, AsyncCallback callback, object state)
    override IAsyncResult BeginWrite(byte[] array, int offset, int numBytes, AsyncCallback callback, object state)
    override void Dispose(bool disposing)
    override int EndRead(IAsyncResult asyncResult)
    override void EndWrite(IAsyncResult asyncResult)
    override void Flush()
    virtual void Flush(bool flushToDisk)
    override Task FlushAsync(CancellationToken cancellationToken)
    virtual void Lock(long position, long length)
    override Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)
    virtual void Unlock(long position, long length)
    override Task WriteAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken);
    */

private:
    bool IsClosed() const noexcept;

/**@section Variable */
private:
    static constexpr FileShare DefaultShare = FileShare::Read;
    static constexpr bool DefaultIsAsync = false;
    static constexpr int DefaultBufferSize = 4096;

    void* m_nativeHandle;
    std::vector<uint8_t> m_buffer;
    bool m_canSeek;
    bool m_canRead;
    bool m_canWrite;
    bool m_isUseAsync;
    int32_t m_readPos;
    int32_t m_writePos;
    FileAccess m_access;
    std::string m_fileName;    
};

} /* namespace tgon */

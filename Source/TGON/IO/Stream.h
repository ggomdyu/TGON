/**
 * @file    Stream.h
 * @author  ggomdyu
 * @since   08/06/2019
 */

#pragma once
#include <cstdint>
#include <string>

#include "Platform/Config.h"

namespace tgon
{

enum class SeekOrigin
{
    Begin,
    Current,
    End
};
 
class TGON_API Stream
{
/**@section Method */
public:
    virtual bool CanRead() const = 0;
    virtual bool CanSeek() const = 0;
    virtual bool CanWrite() const = 0;
    virtual bool IsAsync() const = 0;
    virtual void SetLength(int64_t value) = 0;
    virtual int64_t Length() const = 0;
    virtual int64_t Position() const = 0;
    virtual int Read(uint8_t* buffer, int32_t offset, int32_t count) = 0;
    virtual int32_t ReadByte() {}
    virtual void Write(uint8_t* buffer, int32_t offset, int32_t count) = 0;
    virtual void WriteByte(uint8_t value) = 0;
    virtual long Seek(int64_t offset, SeekOrigin origin) = 0;
    virtual void Close() = 0;
    //static readonly Stream Null;
    //virtual bool CanTimeout
    //virtual int ReadTimeout
    //virtual int WriteTimeout
    //virtual IAsyncResult BeginRead(byte[] buffer, int offset, int count, AsyncCallback callback, object state) = 0
    //virtual IAsyncResult BeginWrite(byte[] buffer, int offset, int count, AsyncCallback callback, object state) = 0;
    //void Dispose()
    //virtual int EndRead(IAsyncResult asyncResult)
    //virtual void EndWrite(IAsyncResult asyncResult)
    //abstract void Flush();
    //Task FlushAsync()
    //virtual Task FlushAsync(CancellationToken cancellationToken)
    //virtual int Read(Span<byte> buffer)
    //Task<int> ReadAsync(byte[] buffer, int offset, int count)
    //virtual Task<int> ReadAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)
    //virtual ValueTask<int> ReadAsync(Memory<byte> buffer, CancellationToken cancellationToken = default(CancellationToken))
    //static Stream Synchronized(Stream stream)
    //virtual void Write(ReadOnlySpan<byte> buffer)
    //Task WriteAsync(byte[] buffer, int offset, int count)
    //virtual Task WriteAsync(byte[] buffer, int offset, int count, CancellationToken cancellationToken)
    //
    //virtual ValueTask WriteAsync(ReadOnlyMemory<byte> buffer, CancellationToken cancellationToken = default(CancellationToken))
};

} /* namespace tgon */

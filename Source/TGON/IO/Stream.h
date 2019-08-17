/**
 * @file    Stream.h
 * @author  ggomdyu
 * @since   08/06/2019
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <cstdint>

#include "Platform/Config.h"
#include "Core/Span.h"

namespace tgon
{

enum class SeekOrigin
{
    Begin,
    Current,
    End
};
 
class TGON_API Stream :
    private boost::noncopyable
{
/**@section Destructor */
public:
    virtual ~Stream() = default;
    
/**@section Method */
public:
    virtual bool CanRead() const = 0;
    virtual bool CanSeek() const = 0;
    virtual bool CanWrite() const = 0;
    virtual bool SetLength(int64_t value) = 0;
    virtual int64_t Length() const = 0;
    virtual int64_t Position() const = 0;
    int32_t Read(const Span<uint8_t>& buffer);
    virtual int32_t Read(uint8_t* buffer, int32_t count) = 0;
    virtual int32_t ReadByte() = 0;
    bool Write(const Span<const uint8_t>& buffer);
    virtual bool Write(const uint8_t* buffer, int32_t count) = 0;
    virtual bool WriteByte(uint8_t value) = 0;
    virtual int64_t Seek(int64_t offset, SeekOrigin origin) = 0;
    virtual void Close() = 0;
    virtual void Flush() = 0;
    //virtual bool CanTimeout
    //virtual int ReadTimeout
    //virtual int WriteTimeout
};
    
inline int32_t Stream::Read(const Span<uint8_t>& buffer)
{
    return this->Read(&buffer[0], buffer.Length());
}

inline bool Stream::Write(const Span<const uint8_t>& buffer)
{
    return this->Write(&buffer[0], buffer.Length());
}

} /* namespace tgon */

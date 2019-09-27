/**
 * @file    Stream.h
 * @author  ggomdyu
 * @since   08/06/2019
 */

#pragma once
#include <gsl/span>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{

enum class SeekOrigin
{
    Begin,
    Current,
    End
};
 
class TGON_API Stream :
    private NonCopyable
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
    int32_t Read(const gsl::span<uint8_t>& buffer);
    virtual int32_t Read(uint8_t* buffer, int32_t count) = 0;
    virtual int32_t ReadByte() = 0;
    bool Write(const gsl::span<const uint8_t>& buffer);
    virtual bool Write(const uint8_t* buffer, int32_t count) = 0;
    virtual bool WriteByte(uint8_t value) = 0;
    virtual int64_t Seek(int64_t offset, SeekOrigin origin) = 0;
    virtual void Close() = 0;
    virtual void Flush() = 0;
};
    
inline int32_t Stream::Read(const gsl::span<uint8_t>& buffer)
{
    return this->Read(&buffer[0], buffer.size());
}

inline bool Stream::Write(const gsl::span<const uint8_t>& buffer)
{
    return this->Write(&buffer[0], buffer.size());
}

} /* namespace tgon */

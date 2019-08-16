#include "PrecompiledHeader.h"

#include "Stream.h"

namespace tgon
{

int32_t Stream::Read(const Span<uint8_t>& buffer)
{
    return this->Read(&buffer[0], buffer.Length());
}

bool Stream::Write(const Span<const uint8_t>& buffer)
{
    return this->Write(&buffer[0], buffer.Length());
}

} /* namespace tgon */
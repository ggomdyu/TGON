/**
 * @filename    UUID.h
 * @author      ggomdyu
 * @date        10/28/2017
 */

#pragma once
#include <uuid/uuid.h>

namespace tgon
{
namespace hash
{

struct UUID
{
/* section  Private constructor */
private:
    constexpr UUID() noexcept = default;

/* section  Public method */
public:
    static UUID NewUUID();
    static UUID Empty();

/* section  Private variable */
private:
    char m_uuid[37] {};
}

UUID UUID::NewUUID()
{
    uuid_t uuid;
    uuid_generate_random(uuid);

    UUID ret;
    uuid_unparse(uuid, ret.m_uuid);
    return ret;
}

} /* namespace hash */
} /* namespace tgon */


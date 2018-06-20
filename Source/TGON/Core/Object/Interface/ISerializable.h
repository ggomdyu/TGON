/**
 * @filename    ICloneable.h
 * @author      ggomdyu
 * @since       10/28/2017
 * @brief       Interface class for virtual copy constructor.
 */

#pragma once
#include <map>
#include <boost/any.hpp>

namespace tgon
{

class SerializationInfo
{
public:
    template <typename _ValueType>
    void AddValue(const std::string& name, const _ValueType& value);
    
private:
    std::map<std::string, std::string> m_valueTable;
};

class ISerializable
{
/* @section Public destructor */
public:
    virtual ~ISerializable() = default;

/* @section Public method */
public:
    /* @brief   Returns copied one from this instance. */
};

} /* namespace tgon */

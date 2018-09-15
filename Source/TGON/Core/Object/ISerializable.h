/**
 * @file    ISerializable.h
 * @author  ggomdyu
 * @since   10/28/2017
 */

#pragma once
#include <map>

namespace tgon
{

class SerializationInfo
{
/**@section Public method */
public:
    template <typename _ValueType>
    void AddValue(const std::string& name, const _ValueType& value);
    
/**@section Private variable */
private:
    std::map<std::string, std::string> m_variableTable;
};

class ISerializable
{
/**@section Public destructor */
public:
    virtual ~ISerializable() = default;

/**@section Public method */
public:
    /**@brief   Returns copied one from this instance. */
};

template <typename _ValueType>
inline void SerializationInfo::AddValue(const std::string& name, const _ValueType& value)
{
    m_variableTable.insert(name, value);
}

} /* namespace tgon */

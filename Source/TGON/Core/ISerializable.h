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
/**@section Method */
public:
    template <typename _ValueType>
    void AddValue(const std::string& name, const _ValueType& value)
    {
        m_variableTable.insert(name, value);
    }
    
/**@section Variable */
private:
    std::map<std::string, std::string> m_variableTable;
};

class ISerializable
{
/**@section Destructor */
public:
    virtual ~ISerializable() = default;

/**@section Method */
public:
    /**@brief   Returns copied one from this instance. */
};

} /* namespace tgon */

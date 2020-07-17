#pragma once

#include <map>
#include <string>

namespace tg
{

class SerializationInfo
{
/**@section Method */
public:
    template <typename _ValueType>
    void AddValue(const std::string& name, const _ValueType& value);
    
/**@section Variable */
private:
    std::map<std::string, std::string> m_variableTable;
};

template <typename _ValueType>
void SerializationInfo::AddValue(const std::string& name, const _ValueType& value)
{
    m_variableTable.insert(name, value);
}

class ISerializable
{
/**@section Destructor */
public:
    virtual ~ISerializable() = default;

/**@section Method */
public:
};

}

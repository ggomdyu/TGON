#pragma once

#include "SerializationInfo.h"

namespace tg
{

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

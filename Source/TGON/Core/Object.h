/**
 * @file    Object.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include "RuntimeObject.h"

#include "String/StringHash.h"

namespace tgon
{

class TGON_API Object :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(Object)
    
/**@section Constructor */
public:
    Object() = default;
    Object(const StringHash& name);
    Object(StringHash&& name);

/**@section Method */
public:
    void SetName(const StringHash& name);
    const StringHash& GetName() const noexcept;

/**@section Variable */
private:
    StringHash m_name;
};

} /* namespace tgon */

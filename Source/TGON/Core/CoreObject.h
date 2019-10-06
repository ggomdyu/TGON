/**
 * @file    CoreObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include "RuntimeObject.h"

#include "String/StringHash.h"

namespace tgon
{

class TGON_API CoreObject :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(CoreObject)
    
/**@section Constructor */
public:
    CoreObject() = default;
    CoreObject(const StringHash& name);
    CoreObject(StringHash&& name);

/**@section Method */
public:
    void SetName(const StringHash& name);
    const StringHash& GetName() const noexcept;

/**@section Variable */
private:
    StringHash m_name;
};

} /* namespace tgon */

/**
 * @file    CoreObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <boost/any.hpp>
#include <string>

#include "RuntimeObject.h"

namespace tgon
{

class TGON_API CoreObject :
    public RuntimeObject,
    private boost::noncopyable
{
public:
    TGON_DECLARE_RTTI(CoreObject);

/**@section Public constructor */
public:
    CoreObject() = default;

/**@section Public destructor */
public:
    virtual ~CoreObject() override = default;
    
/**@section Public method */
public:
    template <typename _Type>
    void SetExtraData(_Type&& extraData);
    
    template <typename _Type>
    _Type* GetExtraData();
    
    template <typename _Type>
    const _Type* GetExtraData() const;
    
/**@section Private variable */
private:
    boost::any m_extraData;
};

template <typename _Type>
inline void CoreObject::SetExtraData(_Type&& extraData)
{
    m_extraData = std::forward<_Type>(extraData);
}

template <typename _Type>
inline _Type* CoreObject::GetExtraData()
{
    return boost::any_cast<_Type>(&m_extraData);
}

template <typename _Type>
inline const _Type* CoreObject::GetExtraData() const
{
    return const_cast<CoreObject*>(this)->GetExtraData<_Type>();
}

} /* namespace tgon */

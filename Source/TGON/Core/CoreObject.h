/**
 * @file    CoreObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <string>
#include <any>

#include "RuntimeObject.h"

namespace tgon
{

class TGON_API CoreObject :
    public RuntimeObject,
    private boost::noncopyable
{
public:
    TGON_DECLARE_RTTI(CoreObject);

/**@section Constructor */
public:
    CoreObject() = default;

/**@section Destructor */
public:
    virtual ~CoreObject() override = default;
    
/**@section Method */
public:
    template <typename _Type>
    void SetExtraData(_Type&& extraData);
    
    template <typename _Type>
    _Type* GetExtraData();
    
    template <typename _Type>
    const _Type* GetExtraData() const;
    
/**@section Variable */
private:
    std::any m_extraData;
};

template <typename _Type>
inline void CoreObject::SetExtraData(_Type&& extraData)
{
    m_extraData = std::forward<_Type>(extraData);
}

template <typename _Type>
inline _Type* CoreObject::GetExtraData()
{
    return std::any_cast<_Type>(&m_extraData);
}

template <typename _Type>
inline const _Type* CoreObject::GetExtraData() const
{
    return const_cast<decltype(this)>(this)->GetExtraData<_Type>();
}

} /* namespace tgon */

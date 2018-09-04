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
#include "RuntimeObjectUtility.h"

namespace tgon
{

class TGON_API CoreObject :
    public RuntimeObject,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(CoreObject);

/* @section Public constructor */
public:
    CoreObject() = default;

/* @section Public destructor */
public:
    virtual ~CoreObject() override = default;
    
/* @section Public method */
public:
    template <typename _Type>
    void SetExtraData(_Type&& extraData)
    {
        m_extraData = std::forward<_Type>(extraData);
    }
    
    template <typename _Type>
    _Type* GetExtraData()
    {
        return boost::any_cast<_Type>(&m_extraData);
    }
    
    template <typename _Type>
    const _Type* GetExtraData() const
    {
        return const_cast<CoreObject*>(this)->GetExtraData<_Type>();
    }
    
/* @section Private variable */
private:
    boost::any m_extraData;
};

} /* namespace tgon */

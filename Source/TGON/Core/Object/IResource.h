/**
 * @file    IResource.h
 * @author  ggomdyu
 * @since   09/24/2018
 */

#pragma once
#include <map>

namespace tgon
{

class IResource
{
/**@section Public constructor */
public:
    explicit IResource(size_t id);

/**@section Public destructor */
public:
    virtual ~IResource() = default;

/**@section Public method */
public:
    /**@brief   Gets the id of this resource. */
    const size_t GetID() const noexcept;
    
/**@section Private variable */
private:
    size_t m_id;
};

} /* namespace tgon */

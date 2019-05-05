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
/**@section Constructor */
public:
    explicit IResource(size_t id);

/**@section Destructor */
public:
    virtual ~IResource() = default;

/**@section Method */
public:
    /**@brief   Gets the id of this resource. */
    const size_t GetID() const noexcept;
    
/**@section Variable */
private:
    size_t m_id;
};

} /* namespace tgon */

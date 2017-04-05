/**
 * filename IGraphicsInstance.h
 * author   ggomdyu
 * since    04/02/2017
 */

#pragma once
#include <boost/noncopyable.hpp>

namespace tgon
{

enum class EGraphicsInstanceState
{
    Unknown,
    Succeed,
    FailedToCreate,
};

class IGraphicsInstance :
    private boost::noncopyable
{
public:
    IGraphicsInstance();
    virtual ~IGraphicsInstance();

    EGraphicsInstanceState GetInstanceState() const noexcept;

protected:
    EGraphicsInstanceState m_state;
};

}
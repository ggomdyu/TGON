/**
 * filename IGraphicsInstance.h
 * author   ggomdyu
 * since    04/02/2017
 */

#pragma once
#include <boost/noncopyable.hpp>

namespace tgon
{

class IGraphicsInstance :
    private boost::noncopyable
{
public:
    IGraphicsInstance();
    virtual ~IGraphicsInstance();

private:
};

}
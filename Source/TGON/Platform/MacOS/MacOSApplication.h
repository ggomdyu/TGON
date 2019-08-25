/**
 * @file    MacOSApplication.h
 * @author  ggomdyu
 * @since   07/21/2017
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"

namespace tgon
{

class TGON_API MacOSApplication :
    private boost::noncopyable
{
};

using PlatformApplication = MacOSApplication;

} /* namespace tgon */

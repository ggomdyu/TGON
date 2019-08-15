/**
 * @file    MacOSApplication.h
 * @author  ggomdyu
 * @since   07/21/2017
 */

#pragma once
#import <boost/noncopyable.hpp>

#import "Platform/Config.h"

namespace tgon
{

class TGON_API MacOSApplication :
    private boost::noncopyable
{
};

using PlatformApplication = MacOSApplication;

} /* namespace tgon */

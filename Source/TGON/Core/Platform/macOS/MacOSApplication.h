/**
 * @filename    MacOSApplication.h
 * @author      ggomdyu
 * @since       09/22/2017
 */

#pragma once
#import "Core/Platform/Base/BaseApplication.h"

namespace tgon
{
namespace platform
{
namespace macos
{

class TGON_API MacOSApplication :
    public BaseApplication
{
/* @section public constructor */
public:
    MacOSApplication() = default;

/* @section public destructor */
public:
    virtual ~MacOSApplication() = default;

public:
};

} /* namespace windows */

using Application = macos::MacOSApplication;

} /* namespace platform */
} /* namespace tgon */

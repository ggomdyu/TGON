/**
 * @file    MacOSApplicationType.h
 * @author  ggomdyu
 * @since   06/09/2018
 */

#pragma once
#import <AppKit/NSAlert.h>

namespace tgon
{

enum class MessageBoxIcon
{
    No = -1,
    Informational = NSAlertStyleInformational,
    Warning = NSAlertStyleCritical,
};

} /* namespace tgon */

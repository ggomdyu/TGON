#import "iOSApplication.h"

#import <UIKit/UIScreen.h>
#import <cstring>

namespace tgon
{
namespace platform
{
namespace ios
{
    
iOSApplication::iOSApplication(UIApplication* uiApplication) :
    m_uiApplication(uiApplication),
    m_uiWindow([[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]])
{
}

void iOSApplication::ShowTopStatusBar()
{
    // Use this instead
    //[m_rootViewController prefersStatusBarHidden];
    //[[UIApplication sharedApplication] setStatusBarHidden:FALSE];
}
    
void iOSApplication::HideTopStatusBar()
{
    //[[UIApplication sharedApplication] setStatusBarHidden:TRUE];
}
    
} /* namespace ios */
} /* namespace platform */
} /* namespace tgon */

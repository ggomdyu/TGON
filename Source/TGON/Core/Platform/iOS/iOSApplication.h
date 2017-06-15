#pragma once
#import <UIKit/UIApplication.h>
#import <UIKit/UIWindow.h>


#import "Core/Platform/Generic/GenericApplication.h"

class Foo
{
    
};

namespace tgon
{
namespace platform
{
namespace ios
{
    
class iOSApplication : public GenericApplication
{
public:
    TGON_MAKE_OBJECT_INTERFACE(tgon::platform::ios::iOSApplication)
    
/**
 * @section Ctor/Dtor
 */
public:
    explicit iOSApplication(UIApplication* uiApplication);
    virtual ~iOSApplication() = default;
    
/**
 * @section Public method
 */
public:
     virtual void ShowTopStatusBar() override;
     virtual void HideTopStatusBar() override;
   
/**
 * @section Private variable
 */
private:
    UIApplication* m_uiApplication;
    UIWindow* m_uiWindow;
};
    
} /* namespace ios */
} /* namespace platform */
} /* namespace tgon */

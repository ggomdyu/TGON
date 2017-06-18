#import <UIKit/UIKit.h>

#import "iOSRootViewController.h"

@interface iOSAppDelegate : UIResponder <UIApplicationDelegate>
{
    iOSRootViewController* m_rootViewController;}

- (void)InitializeRootViewController;

@end


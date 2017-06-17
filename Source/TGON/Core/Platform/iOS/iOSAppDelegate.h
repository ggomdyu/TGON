#import <UIKit/UIKit.h>

#import "iOSRootViewController.h"

@interface iOSAppDelegate : UIResponder <UIApplicationDelegate>
{
    iOSRootViewController* m_rootViewController;
}

@property (strong, nonatomic) UIWindow *window;

- (void)InitializeRootViewController;
- (void)InitializeWindow:(UIViewController*)rootViewController;

@end


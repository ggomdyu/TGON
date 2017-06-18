#import "PrecompiledHeader.h"
#import "iOSAppDelegate.h"

#import <memory>
#import "Core/String/FixedStringUtility.h"

//#import "iOSApplication.h"

#import "Core/Utility/Expression.h"

using namespace tgon::utility;

class Vec
{
public:
    Vec() noexcept
    {
        for (int i = 0; i < std::extent<decltype(m)>::value; ++i)
        {
            m[i] = 0;
        }
    }

    Vec(int a, int b, int c, int d)
    {
        m[0] = a;
        m[1] = b;
        m[2] = c;
        m[3] = d;
    }

    template <typename ExpressionTy>
    Vec(ExpressionTy expression) noexcept
    {
        for (int i = 0; i < std::extent<decltype(m)>::value; ++i)
        {
            m[i] = expression[i];
        }
    }

    int operator[](int index) const
    {
        return m[index];
    }

    PlusExpression<Vec, Vec> operator+(const Vec& rhs)
    {
        return {*this, rhs};
    }

    int m[4];
};



@implementation iOSAppDelegate

- (void)InitializeRootViewController
{
    using namespace tgon::string;
    
    Vec v{1,2,3,4};
    Vec v1{5,6,7,8};

    Vec v2 = v + v1 + v1 + v + v1 + v;

    NSLog(@"%d %d %d %d", v2[0], v2[1], v2[2], v[3]);
    
    m_rootViewController = [[iOSRootViewController alloc] init];
    [m_rootViewController presentViewController:m_rootViewController animated:TRUE completion:nil];
}

- (BOOL)application:(UIApplication*)uiApplication didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
    [self InitializeRootViewController];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end

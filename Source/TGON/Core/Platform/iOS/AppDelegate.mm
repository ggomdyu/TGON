   //
//  AppDelegate.m
//  ModelJoy
//
//  Created by 차준호 on 2017. 6. 17..
//  Copyright © 2017년 ggomdyu. All rights reserved.
//

#import "AppDelegate.h"

#import <iostream>
#import <string>
#import "Core/String/FixedString.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.

    using namespace tgon::string;

    FixedString128 fs = "Powerful";
    auto f1 = fs.CStr();
    auto f2 = fs.Find('e');
    auto f3 = fs.Find('m');
    auto f4 = fs.Find("fu");
    auto f5 = fs.Find("fow");

    for (auto ch : fs)
    {

    }

    int n = 3;
    {
        std::string str = "Powerful";
        auto f1 = str.find("str");
    }

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end

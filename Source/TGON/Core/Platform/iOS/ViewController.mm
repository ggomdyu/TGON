//
//  ViewController.m
//  ModelJoy
//
//  Created by 차준호 on 2017. 6. 11..
//  Copyright © 2017년 ggomdyu. All rights reserved.
//

#import "ViewController.h"

#import "iOSApplication.h"

namespace
{

tgon::platform::ios::iOSApplication* g_iosApplication = nullptr;

}

@implementation RootViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    g_iosApplication = new tgon::platform::ios::iOSApplication(nullptr);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

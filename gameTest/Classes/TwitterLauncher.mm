//
//  TwitterLauncher.mm
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/03/29.
//

#include "TwitterLauncher.h"
#import <Social/Social.h>

void TwitterLauncher::openTweetDialog(const char* $tweet)
{
    UIViewController *myViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    NSArray *activityItems = @[@"ミッションクリア #Mr.Parfect"];
    
    UIActivityViewController *activityController = [[UIActivityViewController alloc] initWithActivityItems:activityItems applicationActivities:nil];
    [myViewController presentViewController:activityController animated:YES completion:nil];
}

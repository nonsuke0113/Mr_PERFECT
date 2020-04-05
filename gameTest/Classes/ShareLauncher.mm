//
//  ShareLauncher.mm
//  gameTest-mobile
//
//  Created by 丹野健介 on 2020/04/04.
//

#include "ShareLauncher.h"

/**
    共有機能呼び出し
 
    @param text 共有するテキスト
    @param imagePath 共有する画像のパス
 */
void ShareLauncher::openShareDialog(std::string text, std::string imagePath)
{
    UIViewController *myViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    NSString *str= [NSString stringWithUTF8String:text.c_str()];
    NSString *imagePathStr = [NSString stringWithUTF8String:imagePath.c_str()];
    UIImage *image = [UIImage imageWithContentsOfFile:imagePathStr];
    NSArray *activityItems = @[str, image];
    
    UIActivityViewController *activityController = [[UIActivityViewController alloc] initWithActivityItems:activityItems applicationActivities:nil];
    [myViewController presentViewController:activityController animated:YES completion:nil];
}


/**
    外部ブラウザ表示
 
    @param path 表示するURL
 */
void ShareLauncher::openURL(std::string path)
{
    NSString *pathStr = [NSString stringWithUTF8String:path.c_str()];
    NSURL *url = [NSURL URLWithString:pathStr];
    [[UIApplication sharedApplication] openURL:url];
}

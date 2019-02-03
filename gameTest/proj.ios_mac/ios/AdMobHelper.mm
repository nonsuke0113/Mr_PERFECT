//
//  AdMobHelper.mm
//  gameTest-mobile
//
//  Created by 健介 丹野 on 2019/02/03.
//

#import <Foundation/Foundation.h>
#include "AdMobHelper.h"
#include "AppController.h"

void AdMobHelper::launchInterstitial(){
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController launchInterstitial];
}

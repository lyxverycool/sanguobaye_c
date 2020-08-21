//
//  GamTouchPadView.h
//  baye-ios
//
//  Created by loong on 15/8/16.
//
//

#import <UIKit/UIKit.h>

#include	"inc/dictsys.h"

@class GamTouchPadView;

@protocol GamTouchPadDelegate <NSObject>

- (void)touchPad:(GamTouchPadView*)view raiseKey:(U8)key;

@end

@interface GamTouchPadView : UIView

@property id<GamTouchPadDelegate> touchDelegate;

@end

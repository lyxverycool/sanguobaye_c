//
//  GamLCDView.m
//  baye-ios
//
//  Created by loong on 15/8/16.
//
//

#import "GamLCDView.h"

#include "consdef.h"

#define SCR_W SCR_WID
#define SCR_H SCR_HGT
#define BYTES_PERLINE (SCR_LINE * 8)

@implementation GamLCDView

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
    if (!self.buffer) {
        return;
    }
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    int ind = 0;
    int x, y;
    float ratio = self.frame.size.width / SCR_W;
    
    for (y = 0; y < SCR_H; y++) {
        for (x = 0; x < SCR_W; x++) {
            ind = BYTES_PERLINE*y + x;
            int pixel = self.buffer[ind];
            
            if (pixel) {
                CGContextSetRGBFillColor(ctx, 0, 0, 0, 1);
            }
            else {
                CGContextSetRGBFillColor(ctx, 0.8, 0.85, 0.8, 1);
            }
            CGContextFillRect(ctx, CGRectMake(x*ratio, (y)*ratio, ratio, ratio));
        }
    }
}

@end

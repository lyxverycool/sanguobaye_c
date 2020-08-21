//
//  GamTouchPadView.m
//  baye-ios
//
//  Created by loong on 15/8/16.
//
//

#import "GamTouchPadView.h"
#include "baye/comm.h"

@interface GamTouchPadView()

@property UITouch* activeTouch;

@property CGFloat originX;
@property CGFloat originY;

@property CGFloat lastX;
@property CGFloat lastY;

@property BOOL touchMoved;

@property int xMoved;
@property int yMoved;

@property NSTimeInterval previousMovingTime;
@property UIColor* normalBackgroundColor;

@end

@implementation GamTouchPadView

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (void)resetTouch
{
    self.activeTouch = nil;
    self.touchMoved = NO;
    self.xMoved = 0;
    self.yMoved = 0;
    self.backgroundColor = self.normalBackgroundColor;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.activeTouch) {
        return;
    }
    for (id touch in touches) {
        self.activeTouch = touch;
        break;
    }
    self.previousMovingTime = self.activeTouch.timestamp;
    CGPoint p = [self.activeTouch locationInView:self];
    
    self.lastX = self.originX = p.x;
    self.lastY = self.originY = p.y;
    self.touchMoved = NO;
    if (!self.normalBackgroundColor) {
        self.normalBackgroundColor = self.backgroundColor;
    }
    self.backgroundColor = [UIColor clearColor];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.activeTouch && [touches containsObject:self.activeTouch]) {
        if (!self.touchMoved) {
            [self.touchDelegate touchPad:self raiseKey:VK_ENTER];
        }
        [self resetTouch];
    }
}

- (void)processPointMoveWithPoint:(CGFloat)point
                    previousPoint:(CGFloat) previousPoint
                previousStayPoint:(CGFloat*) previousStayPoint
                               dT:(NSTimeInterval) dT
                          stepMax:(CGFloat) stepMax
                          stepMin:(CGFloat) stepMin
                         speedMax:(CGFloat) speedMax
                   speedThreshold:(CGFloat) speedThreshold
                             vkUp:(int) vkUp
                           vkDown:(int) vkDown
{
    CGFloat speed = (point - previousPoint) / dT;
    CGFloat step;
    int count;
    
    CGFloat dP = point - *previousStayPoint;
    
    speedMax = pow(speedMax, 3);
    speed = fabs(speed);
    if (speed > speedThreshold) {
        speed -= speedThreshold;
    }
    else {
        speed = 0;
    }
    speed = pow(speed, 3);
    speed = MIN(speed, speedMax);
    
    step = stepMax - speed / speedMax * (stepMax - stepMin);
    
    count = fabs(dP) / step;
    if (count) {
        for (int i = 0; i < count; i++) {
            [self.touchDelegate touchPad:self raiseKey:(dP < 0? vkUp : vkDown)];
        }
        *previousStayPoint = point;
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.activeTouch && [touches containsObject:self.activeTouch]) {
        CGPoint p = [self.activeTouch locationInView:self];
        CGPoint pp = [self.activeTouch previousLocationInView:self];
        NSTimeInterval dt = self.activeTouch.timestamp - self.previousMovingTime;
        self.previousMovingTime = self.activeTouch.timestamp;
        
        {
            CGFloat speedX;
            CGFloat speedY;
            CGFloat dX, dY;
            dX = p.x - pp.x;
            dY = p.y - pp.y;
            speedX = dX / dt;
            speedY = dY / dt;
            CGFloat ratio = fabs(speedX / speedY);
            if (ratio < 0.6) {// 考虑垂直锁定
                self.lastX = p.x;
            }
            if (ratio > 1.8) {// 考虑水平锁定
                self.lastY = p.y;
            }
        }
        [self processPointMoveWithPoint:p.y
                          previousPoint:pp.y
                      previousStayPoint:&_lastY
                                     dT:dt
                                stepMax:30
                                stepMin:0.3
                               speedMax:2000
                         speedThreshold:800
                                   vkUp:VK_UP
                                 vkDown:VK_DOWN];
        [self processPointMoveWithPoint:p.x
                          previousPoint:pp.x
                      previousStayPoint:&_lastX
                                     dT:dt
                                stepMax:30
                                stepMin:8
                               speedMax:1000
                         speedThreshold:500
                                   vkUp:VK_LEFT
                                 vkDown:VK_RIGHT];
        self.touchMoved = YES;
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (self.activeTouch && [touches containsObject:self.activeTouch]) {
        [self resetTouch];
    }
}

@end

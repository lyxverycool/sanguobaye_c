//
//  timer.m
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#import <Foundation/Foundation.h>

static NSTimer* _timer1;
NSTimeInterval _timerInterval;

#define ratio 100.0

@interface GamTimerRecv: NSObject
@property void(*callback)();
@end

@implementation GamTimerRecv
- (void)timerFired
{
    if (_callback) {
        _callback();
    }
}
@end

static GamTimerRecv *receiver;

int gam_timer_interval()
{
    return (int)(_timerInterval * ratio);
}

void gam_timer_init()
{
    receiver = [GamTimerRecv new];
}

void gam_timer_set_callback(void(*cb)())
{
    receiver.callback = cb;
}

void gam_timer_open(int interval)
{
    _timerInterval = interval / ratio;
    dispatch_async(dispatch_get_main_queue(), ^{
        if (!_timer1) {
            _timer1 = [NSTimer scheduledTimerWithTimeInterval:_timerInterval
                                                       target:receiver
                                                     selector:@selector(timerFired)
                                                     userInfo:nil repeats:YES];
        }
    });
}

void gam_timer_close()
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (_timer1) {
            [_timer1 invalidate];
            _timer1 = nil;
        }
    });
}


static NSTimer* timer2;
static GamTimerRecv *receiver2;

void gam_timer2_open(int interval, void(*callback))
{
    receiver2 = [GamTimerRecv new];
    receiver2.callback = callback;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        if (!timer2) {
            timer2 = [NSTimer scheduledTimerWithTimeInterval:interval / ratio
                                                       target:receiver2
                                                     selector:@selector(timerFired)
                                                     userInfo:nil repeats:YES];
        }
    });
}
//
//  ViewController.m
//  Baye-iOS
//
//  Created by loong on 15/8/16.
//
//

#import "ViewController.h"
#import "GamLCDView.h"
#import "GamTouchPadView.h"

#include	"inc/dictsys.h"
#include	"baye/comm.h"
#include	"baye/consdef.h"
FAR void GamBaYeEng(void);


#define kLcdFlushNotification @"kLcdFlushNotification"

void GamSetLcdFlushCallback(void(*lcd_fluch_cb)(char*buffer));

@interface LCDBufferWrapper : NSObject
@property char *buffer;

@end
@implementation LCDBufferWrapper
@end

static void _lcd_flush_cb(char*buffer)
{
    LCDBufferWrapper* wBuffer = [LCDBufferWrapper new];
    wBuffer.buffer = buffer;
    [[NSNotificationCenter defaultCenter] postNotificationName:kLcdFlushNotification object:wBuffer];
}

@interface ViewController ()
<GamTouchPadDelegate>

@property dispatch_queue_t queue;
@property (weak) IBOutlet GamLCDView *lcdView;
@property (weak, nonatomic) IBOutlet GamTouchPadView *touchPanelView;
@property (weak, nonatomic) IBOutlet UILabel *versionLabel;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.queue = dispatch_queue_create("gam", nil);
    
    self.touchPanelView.touchDelegate = self;
    
    NSString *version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    
    self.versionLabel.text = [NSString stringWithFormat:@"V %@", version];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(lcdFlush:)
                                                 name:kLcdFlushNotification
                                               object:nil];
    dispatch_async(self.queue, ^{
        NSLog(@"Starting game...");
        
        NSString *datPath
            = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"dat.lib"];
        NSString *fontPath
            = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"font.bin"];
        
    	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    	NSString *documentsDir = [documentPaths objectAtIndex:0];
        
        GamSetResourcePath((U8*)[datPath UTF8String], (U8*)[fontPath UTF8String]);
        GamSetDataDir((U8*)[documentsDir UTF8String]);
        GamSetLcdFlushCallback(_lcd_flush_cb);
        GamBaYeEng();
        exit(0);
    });

    NSLayoutConstraint* constrait = [NSLayoutConstraint constraintWithItem:self.lcdView
                                                                 attribute:NSLayoutAttributeHeight
                                                                 relatedBy:NSLayoutRelationEqual
                                                                    toItem:self.lcdView
                                                                 attribute:NSLayoutAttributeWidth
                                                                multiplier:SCR_HGT / (CGFloat)SCR_WID
                                                                  constant:0];
    [self.lcdView addConstraint:constrait];
}

- (void)lcdFlush:(NSNotification*)notification
{
    dispatch_async(dispatch_get_main_queue(), ^{
        LCDBufferWrapper*wBuffer = notification.object;
        self.lcdView.buffer = wBuffer.buffer;
        [self.lcdView setNeedsDisplay];
    });
}

#pragma mark - IBActions

static void sendKey(int key)
{
//    NSLog(@"sendKey:%d", key);
    MsgType msg;
    msg.type = VM_CHAR_FUN;
    msg.param = key;
    GuiPushMsg(&msg);
}

- (IBAction)exitAction:(id)sender {
    sendKey(VK_EXIT);
}

- (IBAction)searchAction:(id)sender {
    sendKey(VK_SEARCH);
}

- (IBAction)helpAction:(id)sender {
    sendKey(VK_HELP);
}
- (IBAction)upAction:(id)sender {
    sendKey(VK_UP);
}

- (IBAction)downAction:(id)sender {
    sendKey(VK_DOWN);
}

- (IBAction)feedbackAction:(id)sender {
    NSURL *url = [NSURL URLWithString:@"http://git.oschina.net/loongw/iBaye"];
    [[UIApplication sharedApplication] openURL:url];
}

- (IBAction)versionAction:(id)sender {
    NSURL *url = [NSURL URLWithString:@"http://fir.im/baye"];
    [[UIApplication sharedApplication] openURL:url];
}

- (IBAction)sourceAction:(id)sender {
    NSURL *url = [NSURL URLWithString:@"http://git.oschina.net/loongw/iBaye"];
    [[UIApplication sharedApplication] openURL:url];
}

#pragma mark - touchPadDelegate
- (void)touchPad:(GamTouchPadView *)view raiseKey:(U8)key
{
    sendKey(key);
}

@end

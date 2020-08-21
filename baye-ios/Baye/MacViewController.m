//
//  ViewController.m
//  Baye
//
//  Created by loong on 15/8/15.
//
//

#import "MacViewController.h"
#include	"inc/dictsys.h"
#include	"baye/comm.h"
#import "LCDView.h"

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
    [[NSNotificationCenter defaultCenter] postNotificationName:@"lcdflush" object:wBuffer];
}

FAR void GamBaYeEng(void);
@interface ViewController ()
@property dispatch_queue_t queue;
@property (weak) IBOutlet LCDView *lcdView;

@end

@interface ViewController()
<KeyboardDelegate>

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.queue = dispatch_queue_create("gam", nil);

    dispatch_async(self.queue, ^{
        NSLog(@"Starting game...");
        BOOL debug = YES;
        NSString *fontPath
            = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"font.bin"];

        if (debug) {
            GamSetResourcePath((U8*)"/Users/loong/l/lab/baye/BayeCompiler/baye/libs/dat-mod.lib", (U8*)[fontPath UTF8String]);
            GamSetDataDir((U8*)"/Users/loong/l/lab/baye/sav");
        } else {
            NSString *datPath
            = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"dat.lib"];

            NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
            NSString *documentsDir = [documentPaths objectAtIndex:0];
            GamSetResourcePath((U8*)[datPath UTF8String], (U8*)[fontPath UTF8String]);
            GamSetDataDir((U8*)[documentsDir UTF8String]);
        }

        extern U8 g_engineDebug;
        g_engineDebug = 1;
        
        GamBaYeEng();
        exit(0);
    });
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(lcdFlush:)
                                                 name:@"lcdflush" object:nil];
    GamSetLcdFlushCallback(_lcd_flush_cb);
}

- (void)lcdFlush:(NSNotification*)notification
{
    LCDBufferWrapper*wBuffer = notification.object;
    self.lcdView.buffer = wBuffer.buffer;
    [self.lcdView setNeedsDisplay:YES];
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (void)updateLcdWithBuffer:(char*)buffer
{
    
}

static void sendKey(int key)
{
    MsgType msg;
    msg.type = VM_CHAR_FUN;
    msg.param = key;
    GuiPushMsg(&msg);
}

- (IBAction)upAction:(id)sender {
    sendKey(VK_UP);
}

- (IBAction)rightAction:(id)sender {
    sendKey(VK_RIGHT);
}

- (IBAction)downAction:(id)sender {
    sendKey(VK_DOWN);
}

- (IBAction)leftAction:(id)sender {
    sendKey(VK_LEFT);
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
- (IBAction)pageUpAction:(id)sender {
    sendKey(VK_PGUP);
}
- (IBAction)pageDownAction:(id)sender {
    sendKey(VK_PGDN);
}
- (IBAction)enterAction:(id)sender {
    sendKey(VK_ENTER);
}

- (void)keyDown:(NSEvent *)theEvent {
    switch (theEvent.keyCode) {
        case 123:
            sendKey(VK_LEFT);
            break;
        case 124:
            sendKey(VK_RIGHT);
            break;
        case 125:
            sendKey(VK_DOWN);
            break;
        case 126:
            sendKey(VK_UP);
            break;
        case 36:
            sendKey(VK_ENTER);
            break;
        case 49:
            sendKey(VK_EXIT);
            break;
        case 4:
            sendKey(VK_HELP);
            break;
        case 1:
            sendKey(VK_SEARCH);
            break;
        default:
            break;
    }
}

@end

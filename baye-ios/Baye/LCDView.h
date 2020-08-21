//
//  LCDView.h
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#import <Cocoa/Cocoa.h>

@protocol KeyboardDelegate <NSObject>

- (void)keyDown:(NSEvent *)theEvent;


@end

@interface LCDView : NSView

@property (weak) id<KeyboardDelegate> delegate;
@property char *buffer;

@end

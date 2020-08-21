//
//  touch.h
//  baye-ios
//
//  Created by loong on 16/10/3.
//
//

#ifndef touch_h
#define touch_h

#include <stdio.h>
#include "inc/dictsys.h"
#include "baye/comm.h"

typedef struct {
    I16 left;
    I16 top;
    I16 right;
    I16 bottom;
} Rect;

typedef struct {
    U8 completed;
    U8 touched;
    U8 moved;
    I16 startX;
    I16 startY;
    I16 currentX;
    I16 currentY;
} Touch;

typedef struct {
    I16 x;
    I16 y;
} Point;

U8 touchIsPointInRect(I16 x, I16 y, Rect r);
I16 touchListViewItemIndexAtPoint(I16 x, I16 y, Rect listRect, I16 topPadding, I16 bottomPadding, U16 itemStart, U16 itemCount, U16 itemHeight);

Point touchListViewCalcTopLeftForMove(Touch *touch_,
                                      U16 leftWhenTouchDown,
                                      U16 xMax,
                                      U16 itemWitdh,
                                      U16 topWhenTouchDown,
                                      U16 yMax,
                                      U16 itemHeight
                                      );

void touchSendTouchEvent(U16 event, I16 x, I16 y);
I8 touchUpdate(Touch *touch, MsgType msg);
I32 limitValueInRange(I32 value, I32 min, I32 max);

Rect MakeRect(I16 x, I16 y, I16 w, I16 h);

void touchDrawButton(Rect rect, const char*title);

#endif /* touch_h */

//
//  touch.c
//  baye-ios
//
//  Created by loong on 16/10/3.
//
//

#include "touch.h"
#include "baye/compa.h"

void touchSendTouchEvent(U16 event, I16 x, I16 y)
{
    MsgType msg;
    msg.type = VM_TOUCH;
    msg.param = event;
    msg.param2.i16.p0 = x;
    msg.param2.i16.p1 = y;
    GuiPushMsg(&msg);
}

///判断一个点是否在矩形框内
U8 touchIsPointInRect(I16 x, I16 y, Rect r)
{
    return (r.left <= x && x <= r.right) && (r.top <= y && y <= r.bottom);
}

///获取触摸点在list内的item序号。
I16 touchListViewItemIndexAtPoint(I16 x, I16 y, Rect listRect, I16 topPadding, I16 bottomPadding, U16 itemStart, U16 itemCount, U16 itemHeight)
{
    if (!touchIsPointInRect(x, y, listRect)) {
        return -2;
    }
    U16 yOffset = y - listRect.top - topPadding;
    U16 index = itemStart + yOffset / itemHeight;
    return index < itemCount ? index : -1;
}

I8 touchUpdate(Touch *touch, MsgType msg)
{
    if (msg.type != VM_TOUCH) {
        return -1;
    }

    touch->currentX = msg.param2.i16.p0;
    touch->currentY = msg.param2.i16.p1;

    switch (msg.param) {
        case VT_TOUCH_DOWN:
            touch->startX = touch->currentX;
            touch->startY = touch->currentY;
            touch->touched = 1;
            touch->moved = 0;
            break;
        case VT_TOUCH_UP:
            touch->completed = touch->touched;
            touch->touched = 0;
            break;
        case VT_TOUCH_MOVE:
            if (abs(touch->currentX - touch->startX) > 2 || abs(touch->currentY - touch->startY) > 2) {
                touch->moved = 1;
            }
            break;
        case VT_TOUCH_CANCEL:
            touch->touched = 0;
            touch->completed = 0;
            break;
        default:
            break;
    }
    return 0;
}

I32 limitValueInRange(I32 value, I32 min, I32 max)
{
    if (value > max) value = max;
    if (value < min) value = min;
    return value;
}

Point touchListViewCalcTopLeftForMove(Touch *touch_,
                                      U16 leftWhenTouchDown,
                                      U16 xMax,
                                      U16 itemWitdh,
                                      U16 topWhenTouchDown,
                                      U16 yMax,
                                      U16 itemHeight
                                      )
{
#define touch (*touch_)
    Point result = {leftWhenTouchDown, topWhenTouchDown};

    if (itemWitdh) {
        I16 dx = touch.currentX - touch.startX;
        I16 cols = dx / itemWitdh;
        I16 x = leftWhenTouchDown - cols;
        result.x = limitValueInRange(x, 0, xMax);
    }
    if (itemHeight) {
        I16 dy = touch.currentY - touch.startY;
        I16 rows = dy / itemHeight;
        I16 y = topWhenTouchDown - rows;
        result.y = limitValueInRange(y, 0, yMax);
    }
    return result;
}

Rect MakeRect(I16 x, I16 y, I16 w, I16 h)
{
    return (Rect){
        x, y, x + w - 1, y + h - 1
    };
}

void touchDrawButton(Rect rect, const char*title)
{
#define gam_rect2(r) gam_rect(r.left, r.top, r.right, r.bottom)
#define gam_clr_rect2(r) gam_clrlcd(r.left, r.top, r.right, r.bottom)
    gam_clr_rect2(rect);
    gam_rect2(rect);
    GamStrShowS(rect.left+2, rect.top+1, (const U8*)title);
}
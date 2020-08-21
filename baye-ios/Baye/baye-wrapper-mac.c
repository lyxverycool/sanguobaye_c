//
//  baye-wrapper-mac.c
//  baye-ios
//
//  Created by loong on 16/10/3.
//
//

#include "baye-wrapper-mac.h"
#include "touch.h"


void bayeTouchSendTouchEvent(U16 event, I16 x, I16 y)
{
    touchSendTouchEvent(event, x, y);
}


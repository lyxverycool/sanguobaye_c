//
//  sys.c
//  baye-ios
//
//  Created by loong on 16/11/8.
//
//

#include <stdio.h>
#include "baye/compa.h"
#include "baye/comm.h"
#include <sys/time.h>

FAR U8 SysGetSecond(void)
{
    return (U8)time(0);
}

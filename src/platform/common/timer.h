//
//  timer.h
//  baye-ios
//
//  Created by loong on 15/8/15.
//
//

#ifndef baye_ios_timer_h
#define baye_ios_timer_h


void gam_timer_init();
void gam_timer_set_callback(void(*cb)());
void gam_timer_open(int interval);
void gam_timer_close();
int gam_timer_interval();

void gam_timer2_open(int interval, void(*callback)());

#endif

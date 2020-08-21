//
//  dummy-script.c
//  baye-ios
//
//  Created by loong on 16/9/30.
//
//

#include <stdio.h>
#include "baye/script.h"

void script_init(void) {}
int has_hook(const char* name) { return 1; }
int call_hook_s(const char* name, Value* context) { return -1; }

int call_hook_a(const char* name, Value* context) { return -1; }
int call_script(const char*script) { return -1; };
#define call_hook call_hook_a

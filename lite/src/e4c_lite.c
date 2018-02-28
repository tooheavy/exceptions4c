/*
 * exceptions4c lightweight version 2.0
 *
 * Copyright (c) 2016 Guillermo Calvo
 * Licensed under the GNU Lesser General Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include "e4c_lite.h"

E4C_DEFINE_EXCEPTION(RuntimeException, "Runtime exception.", RuntimeException);
E4C_DEFINE_EXCEPTION(NullPointerException, "Null pointer.", RuntimeException);

/* 全局变量，只能单线程，并且只能在一个地方使用（不可重入） */
struct e4c_context e4c = {0};
static const char * err_msg[] = {"\n\nError: %s (%s)\n\n", "\n\nUncaught %s: %s\n\n    thrown at %s:%d\n\n"};

/* 当前层出现异常，跳转至当前层的异常处理地址 */
static void e4c_propagate(void){

    e4c.frame[e4c.frames].uncaught = 1;

    if(e4c.frames > 0){
        longjmp(e4c.jump[e4c.frames - 1], 1);
    }

    if(fprintf(stderr, e4c.err.file ? err_msg[1] : err_msg[0], e4c.err.type->name, e4c.err.message, e4c.err.file, e4c.err.line) > 0){
        (void)fflush(stderr);
    }

    exit(EXIT_FAILURE);
}

/* 更新层计数，当前层所处阶段为开始，未出现异常（或异常都已处理？） */
int e4c_try(const char * file, int line){

    if(e4c.frames >= E4C_MAX_FRAMES){
        e4c_throw(&RuntimeException, file, line, "Too many `try` blocks nested.");
    }

    e4c.frames++;

    e4c.frame[e4c.frames].stage = e4c_beginning;
    e4c.frame[e4c.frames].uncaught = 0;

    return 1;
}

/* 异常是否捕获处理（类型已匹配） */
int e4c_hook(int is_catch){

    int uncaught;

    if(is_catch){
        e4c.frame[e4c.frames].uncaught = 0;
        return 1;
    }

    /* 
    异常未匹配
    更新当前层进入下一个处理阶段
    更新后：
        如果处于e4c_catching阶段且异常已被处理，则直接更新当前层进入下一个处理阶段e4c_finalizing
        如果更新后仍未处于e4c_done阶段，则直接返回1

    如果异常在当前层仍未被捕获，则向上层传递
    返回0
    */

    uncaught = e4c.frame[e4c.frames].uncaught;

    e4c.frame[e4c.frames].stage++;
    if(e4c.frame[e4c.frames].stage == e4c_catching && !uncaught){
        e4c.frame[e4c.frames].stage++;
    }

    if(e4c.frame[e4c.frames].stage < e4c_done){
        return 1;
    }

    e4c.frames--;

    if(uncaught){
        e4c_propagate();
    }

    return 0;
}

/* 判断异常类型是否相同（父类类型）*/
int e4c_extends(const struct e4c_exception_type * child, const struct e4c_exception_type * parent){

    for(; child && child->supertype != child; child = child->supertype){
        if(child->supertype == parent){
            return 1;
        }
    }

    return 0;
}

/* 按照当前指定的异常类别初始化全局异常，并传递异常 */
void e4c_throw(const struct e4c_exception_type * exception_type, const char * file, int line, const char * message){

    e4c.err.type = (exception_type ? exception_type : &NullPointerException);
    e4c.err.file = file;
    e4c.err.line = line;

    (void)sprintf(e4c.err.message, "%.*s", (int)E4C_MESSAGE_SIZE - 1, (message ? message : e4c.err.type->default_message));

    e4c_propagate();
}

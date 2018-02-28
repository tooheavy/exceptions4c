/*
 * exceptions4c lightweight version 2.1
 *
 * Copyright (c) 2016 Guillermo Calvo
 * Licensed under the GNU Lesser General Public License
 */

#ifndef EXCEPTIONS4C_LITE
#define EXCEPTIONS4C_LITE

#include <stddef.h>
#include <setjmp.h>

/* Maximum number of nested `try` blocks */
#ifndef E4C_MAX_FRAMES
# define E4C_MAX_FRAMES 16
#endif

/* Maximum length (in bytes) of an exception message */
#ifndef E4C_MESSAGE_SIZE
# define E4C_MESSAGE_SIZE 128
#endif

/* Controls whether file/line info is attached to exceptions */
#ifndef NDEBUG
# define E4C_DEBUG_INFO __FILE__, __LINE__
#else
# define E4C_DEBUG_INFO NULL, 0
#endif

/* Represents an exception type */
struct e4c_exception_type{
    const char * name;
    const char * default_message;
    const struct e4c_exception_type * supertype;
};

/* Declarations and definitions of exception types */
#define E4C_DECLARE_EXCEPTION(name) extern const struct e4c_exception_type name
#define E4C_DEFINE_EXCEPTION(name, default_message, supertype) const struct e4c_exception_type name = { #name, default_message, &supertype }

/* Predefined exception types */
E4C_DECLARE_EXCEPTION(RuntimeException);
E4C_DECLARE_EXCEPTION(NullPointerException);

/* Represents an instance of an exception type */
struct e4c_exception{
    char message[E4C_MESSAGE_SIZE];
    const char * file;
    int line;
    const struct e4c_exception_type * type;
};

/* Retrieve current thrown exception */
#define E4C_EXCEPTION e4c.err

/* Returns whether current exception is of a given type */
#define E4C_IS_INSTANCE_OF(t) ( E4C_EXCEPTION.type == &t || e4c_extends(E4C_EXCEPTION.type, &t) )

/*

初始化当前层，将当前位置（调用setjmp()函数的位置）设置成跳转目标（捕获到异常时，从这里开始检查是否可以处理该异常）
发生异常时，将跳转到当前层保存的跳转目标，longjmp传递给setjmp的值为1，则从 setjmp 函数返回时也为1

while(e4c_hook(0))
当异常发生时将会让当前层依次经过e4c_trying, e4c_catching, e4c_finalizing, e4c_done，该循环才正式结束

int e4c_hook(int is_catch) 当前层处于e4c_done状态时才返回0

while(e4c_hook(0))第一次执行将更新当前层进入e4c_trying阶段

如果try中的代码块执行正常，没有异常抛出，则下次循环while(e4c_hook(0))将会更新当前层阶段进入e4c_catching，
但由于没有异常，将直接跳过e4c_catching，进入e4c_finalizing阶段，执行finally块代码

如果try中的代码块有异常抛出，则将跳转到setjmp位置执行代码，while(e4c_hook(0))更新当前层阶段进入e4c_catching
有异常，则会判断各e4c_catching分支是否类型匹配，如果匹配则执行异常处理代码
e4c_catching分支中e4c_hook(1)将会更新当前层为异常已匹配
后续再进入e4c_finalizing阶段，执行finally块代码


if(e4c_try(E4C_INFO) && setjmp(e4c.jump[e4c.frames - 1]) >= 0)
	while(e4c_hook(0)) 
		if(e4c.frame[e4c.frames].stage == e4c_trying) {

			代码块

		} else if(e4c.frame[e4c.frames].stage == e4c_catching && E4C_IS_INSTANCE_OF(type) && e4c_hook(1)) {

			异常处理

		} else if(e4c.frame[e4c.frames].stage == e4c_finalizing) {

			最终执行

		}

*/

/* Implementation details */
#define E4C_TRY if(e4c_try(E4C_DEBUG_INFO) && setjmp(e4c.jump[e4c.frames - 1]) >= 0) while(e4c_hook(0)) if(e4c.frame[e4c.frames].stage == e4c_trying)
#define E4C_CATCH(type) else if(e4c.frame[e4c.frames].stage == e4c_catching && E4C_IS_INSTANCE_OF(type) && e4c_hook(1))
#define E4C_FINALLY else if(e4c.frame[e4c.frames].stage == e4c_finalizing)
#define E4C_THROW(type, message) e4c_throw(&type, E4C_DEBUG_INFO, message)

/* This functions must be called only via E4C_TRY, E4C_CATCH, E4C_FINALLY and E4C_THROW */
enum e4c_stage{e4c_beginning, e4c_trying, e4c_catching, e4c_finalizing, e4c_done};
extern struct e4c_context{jmp_buf jump[E4C_MAX_FRAMES]; struct e4c_exception err; struct{unsigned char stage; unsigned char uncaught;} frame[E4C_MAX_FRAMES + 1]; int frames;} e4c;
extern int e4c_try(const char * file, int line);
extern int e4c_hook(int is_catch);
extern int e4c_extends(const struct e4c_exception_type * child, const struct e4c_exception_type * parent);
extern void e4c_throw(const struct e4c_exception_type * exception_type, const char * file, int line, const char * message);

/* OpenMP support */
#ifdef _OPENMP
# pragma omp threadprivate(e4c)
#endif

#endif

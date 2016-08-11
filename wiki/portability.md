---
layout: wiki
title: Portability
---

# Portability

This library should compile in any good old C compiler. It uses nothing but standard C functions. In order to use exceptions4c you have to drop the two files (`e4c.h` and `e4c.c`) in your project and remember to `#include` the header file from your code.

# Keywords

All of the names of the functions, defined types and macros start with the preffix `e4c**` in order to prevent namespace pollution. However, `exceptions4c` defines the next set of **keywords** (through macros) for convenience:

 - `try`
 - `finally`
 - `throw`
 - `catch`
 - `with`
 - `use`
 - `using`

If, for some reason, you don't want the library to define these **keywords**, you can compile the library with the `E4C**NOKEYWORDS` **compile-time** parameter and use their respective alternate versions:

 - `E4C**TRY`
 - `E4C**FINALLY`
 - `E4C**THROW`
 - `E4C**CATCH`
 - `E4C**WITH`
 - `E4C**USE`
 - `E4C**USING`

# C99-only Features

There is a convenience macro that lets you to compose a formatted message and throw an exception **on the fly**.

```

{{{
int bytes = 1024;
void * buffer = malloc(bytes);
if(buffer == NULL){
    throwf(NotEnoughMemoryException, "Could not allocate %d bytes.", bytes);
}
}}}

```

This macro relies on two features that were introduced in **C99**:

  - Variadic macros
  - Buffer-safe function **`vsnprintf`**

In order not to create compatibility issues, this macro will only be defined when the `****STDC**VERSION****` **compile-time** parameter is defined with a value **greater than or equal to** `199901L`, or `HAVE**C99**VARIADIC**MACROS` is defined.

Of course, the alternative way to compose a message and then throw it would be to call `snprintf` (or its **unsafe** alternative `sprintf`):

```

{{{
int bytes = 1024;
void * buffer = malloc(bytes);
if(buffer == NULL){
    char message[E4C_EXCEPTION_MESSAGE_SIZE];
    snprintf(message, E4C_EXCEPTION_MESSAGE_SIZE, "Could not allocate %d bytes.", bytes);
    throw(NotEnoughMemoryException, message);
}
}}}

```

The semantics of this macro are the same as for the `throw` macro.

At least one argument must be passed right after the format string. The message will be composed through the function `vsnprintf` with the specified format and variadic arguments. For further information on the formatting rules, you may look up the specifications for the function `vsnprintf`.

# Multi-threading

In case your application uses threads, `exceptions4c` relies on pthreads, the **POSIX** application programming interface for writing multithreaded applications. This **API** is available for most operating systems and platforms. You only need to compile the library with the `E4C**THREADSAFE` **compile-time** parameter.

----

<https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/logo/exceptions4c**128.png>

---
layout: wiki
title: Multithread support
---

# Multithreading

If you are using threads in your program, you must enable the **thread-safe** version of the library by defining `E4C_THREADSAFE` at compiler level.

The usage of the framework does not vary between single and multithreaded programs. The same semantics apply. The only caveat is that **the behavior of signal handling is undefined in a multithreaded program** so use this feature with caution.

----

![](https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/logo/exceptions4c_128.png)

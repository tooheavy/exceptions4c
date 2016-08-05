
## Portability

This library should compile in any ANSI C compiler. It uses nothing but standard
C functions. In order to use exceptions4c you have to drop the two files
(`e4c.h` and `e4c.c`) in your project and remember to `#include` the header file
from your code.

In case your application uses threads, `exceptions4c` relies on pthreads, the
**POSIX** application programming interface for writing multithreaded
applications. This *API* is available for most operating systems and platforms.

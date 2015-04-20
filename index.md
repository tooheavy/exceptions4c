---
layout: home
overview: true

title: exceptions4c &bull; An exception handling framework for C

intro: An exception handling framework for C

features:

  - title: Error Handling
    description: 'This library provides you with a small set of keywords: <tt>try</tt>, <tt>catch</tt>, <tt>finally</tt>, <tt>throw</tt>...'
    link: Throw & catch exceptions

  - title: Signal Handling
    description: Signals such as <tt>SIGHUP</tt>, <tt>SIGFPE</tt> or <tt>SIGSEGV</tt> can be handled in an <em>exceptional</em> way.
    link: Turn signals into exceptions

  - title: Resource Handling
    description: 'Other keywords allow you to express the <em>Dispose Pattern</em> in your code: <tt>using</tt>, <tt>with... use</tt>.'
    link: Use the Dispose Pattern

  - title: Simple
    description: The API is <strong>intuitive</strong> to any developer with experience on languages with <em>native exceptions</em>.

  - title: Portable
    description: It has no external dependencies, only <strong>standard ANSI C functions</strong> are needed.

  - title: Multithreading
    description: You may also enable the <em>thread-safe</em> version of the library which relies on <strong>pthreads</strong>.

nutshell:

  title: Bring the power of <em>exceptions</em> to your C applications with this tiny, portable library.

  sample: |
    #include "e4c.h"

    int foobar(){
        int * pointer = NULL;
        try{
            int oops = *pointer;
        }catch(BadPointerException){
            printf("No problem!\n");
        }
    }

---

## License

This is free software: you can redistribute it and/or modify it under the terms of the **GNU Lesser General Public License** as published by the *Free Software Foundation*, either version 3 of the License, or (at your option) any later version.

This software is distributed in the hope that it will be useful, but **WITHOUT ANY WARRANTY**; without even the implied warranty of **MERCHANTABILITY** or **FITNESS FOR A PARTICULAR PURPOSE**. See the [GNU Lesser General Public License][LGPL] for more details.

[Learn more about GNU licenses &rarr;][LICENSES]

  [LGPL]: http://www.gnu.org/licenses/lgpl.html
  [LICENSES]: http://www.gnu.org/licenses/

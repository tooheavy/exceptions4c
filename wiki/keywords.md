---
layout: wiki
title: Keywords of exceptions4c
tags: [ "Featured" ]
---

# `exceptions4c` Keywords

![](https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/24x24/exception_handling.png) **Exception handling keywords**:

- [try](keywords.md#try) introduces a block of code aware of exceptions.
- [catch](keywords.md#catch) introduces a block of code capable of handling a specific type of exceptions.
- [finally](keywords.md#finally) introduces a block of code responsible for cleaning up the previous try block.
- [retry](keywords.md#retry) repeats the previous try (or use) block entirely.
- [throw](keywords.md#throw) signals an exceptional situation represented by an exception object.
- [rethrow](keywords.md#rethrow) throws again the currently thrown exception, with a new message.

![](https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/24x24/dispose_pattern.png) **Dispose pattern keywords**:

- [with](keywords.md#with) opens a block of code with automatic disposal of a resource.
- [use](keywords.md#use) closes a block of code with automatic disposal of a resource.
- [using](keywords.md#using) introduces a block of code with automatic acquisition and disposal of a resource.
- [reacquire](keywords.md#reacquire) repeats the previous with block entirely.

![](https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/24x24/thoroughly_tested.png) **Assertion keyword**:

- [assert](keywords.md#assert) expresses a program assertion.

![](https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/24x24/beautifully_crafted.png) **Other convenience keywords (C99 only)**:

- [throwf](keywords.md#throwf) throws an exception with a formatted message.
- [rethrowf](keywords.md#rethrowf) throws again the currently thrown exception, with a new, formatted message.

----

# ![][KEYWORD] `try`

Introduces a block of code aware of exceptions.

## Detailed Description

A `try` statement executes a block of code. If an exception is thrown and there is a `catch` block that can handle it, then control will be transferred to it. If there is a `finally` block, then it will be executed, no matter whether the `try` block completes normally or abruptly, and no matter whether a `catch` block is first given control.

The block of code immediately after the keyword `try` is called **the `try` block** of the `try` statement. The block of code immediately after the keyword `finally` is called **the `finally` block** of the `try` statement.

```
stack_t * stack = stack_new();
try{
    /* the try block */
    int value = stack_pop(stack);
    stack_push(stack, 16);
    stack_push(stack, 32);
}catch(StackOverflowException){
    /* a catch block */
    printf("Could not push.");
}catch(StackUnderflowException){
    /* another catch block */
    printf("Could not pop.");
}finally{
    /* the finally block */
    stack_delete(stack);
}
```

One `try` block may precede many `catch` blocks (also called **exception handlers**). A `catch` block must have exactly one parameter which is the [exception type](types.md#e4c_exception_type) it is capable of handling. Within the `catch` block, the exception can be accessed through the function [e4c_get_exception](functions.md#e4c_get_exception). Exception handlers are considered in left-to-right order: the earliest possible `catch` block handles the exception. If no `catch` block can handle the thrown exception, it will be **propagated**.

Sometimes it can come in handy to [retry](keywords.md#retry) an entire `try` block, for instance, once the exception has been caught and the error condition has been solved.

A `try` block has an associated [status](types.md#e4c_status) according to the way it has been executed:

- It **succeeds** when the execution reaches the end of the block without any exceptions.
- It **recovers** when an exception is thrown but a `catch` block handles it.
- It **fails** when an exception is thrown and it's not caught.

The status of the current `try` block can be retrieved through [e4c_get_status](functions.md#e4c_get_status).

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `try`. Such programming error will lead to an abrupt exit of the program (or thread).
- A `try` block **must** precede, at least, another block of code, introduced by either `catch` or `finally`.
- A `try` block may precede several `catch` blocks.
- A `try` block **can** precede, at most, one `finally` block.
- A `try` block **must not** be exited through any of: `goto`, `break`, `continue` or `return` (but it is legal to throw an exception).

## Postconditions

- A `finally` block will be executed after the `try` block and any `catch` block that might be executed, no matter whether the `try` block **succeeds**, **recovers** or **fails**.

## See Also

- [catch](keywords.md#catch)
- [finally](keywords.md#finally)
- [retry](keywords.md#retry)
- [e4c_status](types.md#e4c_status)
- [e4c_exception_type](types.md#e4c_exception_type)
- [e4c_get_status](functions.md#e4c_get_status)

----

# ![][KEYWORD] `catch`

Introduces a block of code capable of handling a specific type of exceptions.

## Parameters

- `exception_type`: The type of exceptions to be handled.

## Detailed Description

`catch` blocks are optional code blocks that **must** be preceded by `try`, `with... use` or `using` blocks. Several `catch` blocks can be placed next to one another.

When an exception is thrown, the system looks for a `catch` block to handle it. The first capable block (in order of appearance) will be executed and the exception is said to be **caught**.

The caught exception can be accessed through the function [e4c_get_exception](functions.md#e4c_get_exception).

```
try{
    /* ... */
}catch(RuntimeException){
    const e4c_exception * exception = e4c_get_exception();
    printf("Error: %s", exception->message);
}
```

The actual `type` of the exception can be checked against other exception types through the function [e4c_is_instance_of](functions.md#e4c_is_instance_of).

```
try{
    /* ... */
}catch(RuntimeException){
    const e4c_exception * exception = e4c_get_exception();
    if( e4c_is_instance_of(exception, SignalException.type) ){
        // the exception type is SignalException or any subtype
    }
}
```

The `type` might also be compared directly against another specific exception type.

```
try{
    /* ... */
}catch(RuntimeException){
    const e4c_exception * exception = e4c_get_exception();
    if(exception->type == NotEnoughMemoryException.type){
        // the exception type is precisely NotEnoughMemoryException
    }
}
```

After the `catch` block completes, the `finally` block (if any) is executed. Then the program continues by the next line following the set of `try/catch/finally` blocks.

However, if an exception is thrown in a `catch` block, then the `finally` block will be executed right away and the system will look for an outter `catch` block to handle it.

Only one of all the `catch` blocks will be executed for each `try` block, even though the executed `catch` block throws another exception. The only possible way to execute more than one `catch` block would be by [retrying](keywords.md#retry) the entire [try](keywords.md#try) block.

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `catch`. Such programming error will lead to an abrupt exit of the program (or thread).
- A `catch` block **must** be preceded by one of these blocks:
  - A `try` block
  - A `use/with` block
  - A `using` block
  - Another `catch` block.

## See also

- [try](keywords.md#try)
- [e4c_exception_type](types.md#e4c_exception_type)
- [e4c_get_exception](functions.md#e4c_get_exception)
- [e4c_exception](types.md#e4c_exception)
- [e4c_is_instance_of](functions.md#e4c_is_instance_of)

----

# ![][KEYWORD] `finally`

Introduces a block of code responsible for cleaning up the previous **exception-aware** block

## Detailed Description

`finally` blocks are optional code blocks that **must** be preceded by `try`, `with... use` or `using` blocks. It is allowed to place, at most, one `finally` block.

The `finally` block can determine the completeness of the **exception-aware** block through the function  [e4c_get_status](functions.md#e4c_get_status). The thrown exception (if any) can also be accessed through the function [e4c_get_exception](functions.md#e4c_get_exception).

```
try{
   /* ... */
}finally{
   switch( e4c_get_status() ){

       case e4c_succeeded:
           /* ... */
           break;

       case e4c_recovered:
           /* ... */
           break;

       case e4c_failed:
           /* ... */
           break;
   }
}
```

The finally block will be executed only **once**. The only possible way to be executed again would be [retrying](keywords.md#retry) the entire [try](keywords.md#try) block.

## Preconditions

- A `finally` block **must** be preceded by a [try](keywords.md#try), [with](keywords.md#with)/[use](keywords.md#use), [using](keywords.md#using) or [catch](keywords.md#catch) block.
- A program (or thread) **must** begin an exception context prior to using the keyword `finally`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

- [e4c_exception](types.md#e4c_exception)
- [e4c_get_exception](functions.md#e4c_get_exception)
- [e4c_get_status](functions.md#e4c_get_status)
- [e4c_status](types.md#e4c_status)

----

# ![][KEYWORD] `retry`

Repeats the previous try (or use) block entirely.

## Parameters

- `max_retry_attempts`: The maximum number of attempts to retry.

## Detailed Description

This macro discards any thrown exception (if any) and repeats the previous [try](keywords.md#try) or [use](keywords.md#use) block, up to a specified maximum number of attempts.

This macro is intended to be used within [catch](keywords.md#catch) or [finally](keywords.md#finally) blocks as a quick way to fix an error condition and **try again**.

```
const char * file_path = config_get_user_defined_file_path();
try{
    config = read_config(file_path);
}catch(ConfigException){
    file_path = config_get_default_file_path();
    retry(1);
    rethrow("Wrong defaults.");
}
```

**Warning**: If the specified maximum number of attempts is zero, then the block can eventually be attempted an unlimited number of times. Care must be taken in order not to create an **infinite loop**.

**Note**: At a [catch](keywords.md#catch) block, the current exception is considered caught, whether the `retry` takes place or not. If you want the exception to be propagated when the maximum number of attempts has been reached, then you must [rethrow](keywords.md#rethrow) it again.

```
int dividend = 100;
int divisor = 0;
int result = 0;
try{
    result = dividend / divisor;
    do_something(result);
}catch(RuntimeException){
    divisor = 1;
    retry(1);
    rethrow("Error (not a division by zero).");
}
```

**Note**: At a [finally](keywords.md#finally) block, the current exception (if any) will be propagated if the `retry` does not take place, so you don't need to [rethrow](keywords.md#rethrow) it again.

```
int dividend = 100;
int divisor = 0;
int result = 0;
try{
    result = dividend / divisor;
    do_something(result);
}finally{
    if( e4c_get_status() == e4c_failed ){
        divisor = 1;
        retry(1);
        // when we get here, the exception will be propagated
    }
}
```

## Preconditions

- The `retry` keyword must be used from a `catch` or `finally` block.
- A program (or thread) **must** begin an exception context prior to using the keyword `retry`. Such programming error will lead to an abrupt exit of the program (or thread).

## Postconditions

- This macro won't return control unless the block has already been attempted, at least, the specified maximum number of times.

## See Also

- [reacquire](keywords.md#reacquire)
- [try](keywords.md#try)
- [use](keywords.md#use)

----

# ![][KEYWORD] `throw`

Signals an exceptional situation represented by an exception object.

## Parameters

- `exception_type`: The type of exception to be thrown.
- `message`: The **ad-hoc** message describing the exception. If `NULL`, then the default message for the specified exception type will be used.

## Detailed Description

Creates a new instance of the specified type of exception and then throws it. The provided message is copied into the thrown exception, so it can be freely deallocated. If `NULL` is passed, then the default message for that type of exception will be used.

When an exception is thrown, the exception handling framework looks for the appropriate `catch` block that can handle the exception. The system unwinds the call chain of the program and executes the `finally` blocks it finds.

When no `catch` block is able to handle an exception, the system eventually gets to the main function of the program. This situation is called an ***uncaught exception***.

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `throw`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

- [throwf](keywords.md#throwf)
- [rethrow](keywords.md#rethrow)
- [e4c_exception_type](types.md#e4c_exception_type)
- [e4c_exception](types.md#e4c_exception)
- [e4c_uncaught_handler](types.md#e4c_uncaught_handler)
- [e4c_get_exception](functions.md#e4c_get_exception)

----

# ![][KEYWORD] `rethrow`

Throws again the currently thrown exception, with a new message.

## Parameters

- `message`: The new message describing the exception. It should be more specific than the current one.

## Detailed Description

This macro creates a new instance of the thrown exception, with a more specific message.

`rethrow` is intended to be used in a `catch` block and the purpose is to refine the message of the currently caught exception. The previous exception (and its message) will be stored as the **cause** of the newly thrown exception.

```
try{
    image = read_file(file_path);
}catch(FileOpenException){
    rethrow("Image not found.");
}
```

The semantics of this keyword are the same as for the `throw` keyword.

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `rethrow`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

- [throw](keywords.md#throw)
- [rethrowf](keywords.md#rethrowf)

----

# ![][KEYWORD] `with`

Opens a block of code with automatic disposal of a resource.

## Parameters

- `resource`: The resource to be disposed.
- `dispose`: The name of the disposal function (or macro).

## Detailed Description

The `with` keyword is used to encapsulate the **Dispose Pattern**. It **must** be followed by the `use` keyword.

In addition, the `use` block can precede `catch` and `finally` blocks.

This pattern consists of two separate blocks and an implicit call to a given function:

1. the `with` block is responsible for the resource acquisition
2. the `use` block makes use of the resource
3. the disposal function will be called implicitly

The `with` keyword guarantees that the disposal function will be called **if and only if** the acquisition block **completed** without an error (i.e. no exception being thrown from the acquisition block).

If the `with` block does not complete, then neither the disposal function nor the `use` block will be ever executed.

The disposal function is called right after the `use` block. If an exception was thrown, the `catch` or `finally` blocks (if any) will take place **after** the disposal of the resource.

When called, the disposal function will receive two arguments:

- The resource
- A boolean flag indicating if the `use` block did not **complete**

This way, different actions can be taken depending on the success or failure of the block. For example, commiting or rolling back a **transaction** resource.

Legacy functions can be reused by defining macros. For example, a file resource needs to be closed regardless of the errors. Since the function `fclose` only takes one parameter, we could define the next macro:

```
# define e4c_dispose_file(_file_, _failed_) fclose(_file_)
```

The typical usage of a `with` block will be:

```
with(foo, e4c_dispose_foo){
    foo = e4c_acquire_foo(foobar);
    someAssertion(foo, bar);
    /* ... */
}use{
    doSomething(foo);
    /* ... */
}catch(FooAcquisitionFailed){
    recover1();
    /* ... */
}catch(somethingElseFailed){
    recover2();
    /* ... */
}finally{
    cleanup();
    /* ... */
}
```

Nonetheless, one-liners fit nicely too:

```
with(foo, e4c_dispose_foo) foo = e4c_acquire_foo(bar, foobar); use doSomething(foo);
```

There is a way to lighten up even more this pattern by defining convenience macros, customized for a specific kind of resources. For example, `e4c_using_file` or `e4c_using_memory`.

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `with`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

- [use](keywords.md#use)
- [using](keywords.md#using)

----

# ![][KEYWORD] `use`

Closes a block of code with automatic disposal of a resource.

## Detailed Description

A `use` block **must** always be preceded by a `with` block. These two macros are designed so the compiler will complain about **dangling** `with` or `use` blocks.

A code block introduced by the `use` keyword will only be executed when the acquisition of the resource **completes** without any exceptions.

Either if the `use` block completes or not, the disposal function will be executed right away.

## Preconditions

- A `use` block **must** be preceded by a `with` block.
- A program (or thread) **must** begin an exception context prior to using the keyword `use`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

- [with](keywords.md#with)

----

# ![][KEYWORD] `using`

Introduces a block of code with automatic acquisition and disposal of a resource.

## Parameters

- `type`: The type of the resource.
- `resource`: The resource to be acquired, used and then disposed.
- `args`: A list of arguments to be passed to the acquisition function.

## Detailed Description

The specified resource will be acquired, used and then disposed. The automatic acquisition and disposal is achieved by calling the **magic** functions:

- `TYPE e4c_acquire_TYPE(args)`
- `void e4c_dispose_TYPE(TYPE resource, E4C_BOOL failed)`

The resource will be acquired implicitly by assigning to it the result of the **magic** acquisition function `e4c_acquire_TYPE`.

The semantics of the automatic acquisition and disposal are the same as for blocks introduced by the keyword `with`. For example, a `using` block can also precede `catch` and `finally` blocks.

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `using`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

- [with](keywords.md#with)

----

# ![][KEYWORD] `reacquire`

Repeats the previous with block entirely.

## Parameters

- `max_reacquire_attempts`: The maximum number of attempts to reacquire.

## Detailed Description

This macro discards any thrown exception (if any) and repeats the previous
`with` block, up to a specified maximum number of attempts. If the
acquisition completes, then the `use` block will be executed.

It is intended to be used in `catch` or `finally` blocks, next to a
`with... use` or `using` block when the resource acquisition failed,
as a quick way to fix an error condition and try to acquire the resource
again.

```
image_type * image;
const char * image_path = image_get_user_avatar();
with(image, e4c_image_dispose){
    image = e4c_image_acquire(image_path);
}use{
    image_show(image);
}catch(ImageNotFoundException){
    image_path = image_get_default_avatar();
    reacquire(1);
}
```

**Warning**: If the specified maximum number of attempts is zero, then the `with` block can eventually be attempted an unlimited number of times. Care must be taken in order not to create an **infinite loop**.

Once the resource has been acquired, the `use` block can also be repeated **alone** through the `retry` keyword:

```
image_type * image;
const char * image_path = image_get_user_avatar();
display_type * display = display_get_user_screen();
with(image, e4c_image_dispose){
    image = e4c_image_acquire(image_path);
}use{
    image_show(image, display);
}catch(ImageNotFoundException){
    image_path = image_get_default_avatar();
    reacquire(1);
}catch(DisplayException){
    display = display_get_default_screen();
    retry(1);
}
```

## Preconditions

- The `reacquire` keyword must be used from a `catch` or `finally` block, preceded by a `with... use` or `using` block.
- A program (or thread) **must** begin an exception context prior to using the keyword `reacquire`. Such programming error will lead to an abrupt exit of the program (or thread).

## Postconditions

- This macro won't return control unless the `with` block has already been attempted, at least, the specified maximum number of times.

## See Also

- [retry](keywords.md#retry)
- [with](keywords.md#with)
- [use](keywords.md#use)

----

# ![][KEYWORD] `assert`

Expresses a program assertion.

## Parameters

- `condition`: A predicate that must evaluate to `true`.

## Detailed Description

An assertion is a mechanism to express that the developer **thinks** that a specific condition is always met at some point of the program.

`assert` is a convenient way to insert debugging assertions into a program. The `NDEBUG` **compile-time** parameter determines whether the assumptions will be actually verified by the program at **run-time**.

In presence of `NDEBUG`, the assertion statements will be ignored and therefore will have no effect on the program, not even evaluating the condition. Therefore expressions passed to `assert` **must not contain *side-effects***, since they will not take place when debugging is disabled.

In absence of `NDEBUG`, the assertion statements will verify that the condition is met every time the program reaches that point of the program.

If the assertion does not hold at any time, then an `AssertionException` will be thrown to indicate the programming error. This exception cannot be caught whatsoever. The program (or current thread) will be terminated.

The main advantage of using this assertion mechanism (as opposed to the macros provided by the standard header file `assert.h`) is that before actually exiting the program or thread, all of the pending `finally` blocks will be executed.

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `assert`. Such programming error will lead to an an abrupt exit of the program (or thread).

## See Also

- [AssertionException](variables#AssertionException)

----

# ![][KEYWORD] `throwf`

Throws an exception with a formatted message.

## Parameters

- `exception_type`: The type of exception to be thrown.
- `format`: The string containing the specifications that determine the output format for the variadic arguments.
- `...`: The variadic arguments that will be formatted according to the format control.

## Detailed Description

This is a handy way to compose a formatted message and throw an exception **on the fly**:

```
int bytes = 1024;
void * buffer = malloc(bytes);
if(buffer == NULL){
    throwf(NotEnoughMemoryException, "Could not allocate %d bytes.", bytes);
}
```

This macro relies on two features that were introduced in the **ISO/IEC 9899:1999** (also known as **C99**) revision of the C programming language standard in 1999:

- Variadic macros
- Buffer-safe function `vsnprintf`

In order not to create compatibility issues, this macro will only be defined when the `__STDC_VERSION__` **compile-time** parameter is defined as a `long` value **greater than or equal to** `199901L`, or when `HAVE_C99_VARIADIC_MACROS` is defined.

The semantics of this keyword are the same as for the `throw` keyword.

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `throwf`. Such programming error will lead to an abrupt exit of the program (or thread).
- At least one argument **must** be passed right after the format string. The message will be composed through the function `vsnprintf` with the specified format and variadic arguments. For further information on formatting rules, you may look up the specifications for the function `vsnprintf`.

## See Also

- [throw](keywords.md#throw)
- [rethrowf](keywords.md#rethrowf)

----

# ![][KEYWORD] `rethrowf`

Throws again the currently thrown exception, with a new, formatted message.

## Parameters

- `format`: The string containing the specifications that determine the output format for the variadic arguments.
- `...`: The variadic arguments that will be formatted according to the format control.

## Detailed Description

This is a handy way to create (and then `throw`) a new instance of the currently thrown exception, with a more specific, formatted message.

```
try{
    image = read_file(file_path);
}catch(FileOpenException){
    rethrowf("Image '%s' not found.", title);
}
```

This macro relies on two features that were introduced in the **ISO/IEC 9899:1999** (also known as **C99**) revision of the C programming language standard in 1999:

- Variadic macros
- Buffer-safe function `vsnprintf`

In order not to create compatibility issues, this macro will only be defined when the `__STDC_VERSION__` **compile-time** parameter is defined as a `long` value **greater than or equal to** `199901L`, or when `HAVE_C99_VARIADIC_MACROS` is defined.

The semantics of this keyword are the same as for the `throw` keyword.

## Preconditions

- A program (or thread) **must** begin an exception context prior to using the keyword `rethrowf`. Such programming error will lead to an abrupt exit of the program (or thread).
- At least one argument **must** be passed right after the format string. The message will be composed through the function `vsnprintf` with the specified format and variadic arguments. For further information on formatting rules, you may look up the specifications for the function `vsnprintf`.

## See Also

- [rethrow](keywords.md#rethrow)
- [throwf](keywords.md#throwf)

----

![](https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/logo/exceptions4c_128.png)

[KEYWORD]:
https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/keyword.png
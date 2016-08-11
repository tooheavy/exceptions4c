---
layout: wiki
title: Functions exported by exceptions4c.
tags: [ "Featured"]
---

# `exceptions4c` Functions

<https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/24x24/exception**handling.png> **Exception context handling functions**:

  - **<#e4c**context**is**ready e4c**context**is**ready>** checks if the current exception context is ready.
  - **<#e4c**context**begin e4c**context**begin>** begins an exception context.
  - **<#e4c**context**end e4c**context**end>** ends the current exception context.
  - **<#e4c**context**set**signal**mappings e4c**context**set**signal**mappings>** assigns the specified signal mappings to the exception context.
  - **<#e4c**context**get**signal**mappings e4c**context**get**signal**mappings>** retrieves the signal mappings for the current exception context.
  - **<#e4c**get**status e4c**get**status>** returns the completeness status of the executing code block.
  - **<#e4c**get**exception e4c**get**exception>** returns the exception that was thrown.

<https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/24x24/beautifully**crafted.png> **Other integration and convenience functions**:

  - **<#e4c**library**version e4c**library**version>** gets the library version number.
  - **<#e4c**is**instance**of e4c**is**instance**of>** returns whether an exception instance is of a given type.
  - **<#e4c**print**exception e4c**print**exception>** prints a fatal error message regarding the specified exception.
  - **<#e4c**print**exception**type e4c**print**exception**type>** prints an ASCII graph representing an exception type's hierarchy.

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**context**is**ready`

Checks if the current exception context is ready.

## Returns

  - Whether the current exception context of the program (or current thread) is ready to be used.

## Detailed Description

This function returns whether there is an actual exception context ready to be used by the program or current thread.

## See Also

 - **<#e4c**context**begin e4c**context**begin>**
 - **<#e4c**context**end e4c**context**end>**
 - **<macros#e4c**using**context e4c**using**context>**
 - **<macros#e4c**reusing**context e4c**reusing**context>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**context**begin`

Begins an exception context.

## Parameters

  - **`handle**signals`**: if `E4C**TRUE`, the signal handling system will be set up with the default mapping.

## Detailed Description

This function begins the current exception context to be used by the program (or current thread), until <#e4c**context**end e4c**context**end> is called.

Calling `e4c**context**begin` **twice** is considered a programming error, and therefore the program (or thread) will exit abruptly. Nevertheless, `e4c**context**begin` can be called several times **if, and only if,** `e4c**context**end` is called in between.

The signal handling system can be automatically initialized with the default signal mapping via `handle**signals` parameter when calling `e4c**context**begin`. This is equivalent to:

```

{{{
e4c**context**set**signal**mappings(e4c**default**signal**mappings);
}}}

```

**Warning**: Note that, on some specific platforms, the behavior of the standard `signal` function might be undefined for a multithreaded program, so use the signal handling system with caution.

The convenience function <functions#e4c**print**exception e4c**print**exception> will be used as the default <types#e4c**uncaught**handler uncaught handler>. It will be called in the event of an uncaught exception, before exiting the program or thread. This handler can be set through the function <functions#e4c**context**set**handlers e4c**context**set**handlers>.

## See Also

 - **<#e4c**context**end e4c**context**end>**
 - **<#e4c**context**is**ready e4c**context**is**ready>**
 - **<macros#e4c**using**context e4c**using**context>**
 - **<macros#e4c**reusing**context e4c**reusing**context>**
 - **<types#e4c**uncaught**handler e4c**uncaught**handler>**
 - **<#e4c**print**exception e4c**print**exception>**
 - **<#e4c**context**set**handlers e4c**context**set**handlers>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**context**end`

Ends the current exception context.

## Detailed Description

This function ends the current exception context.

## Preconditions

  - A program (or thread) **must** begin an exception context prior to calling `e4c**context**end`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

 - **<#e4c**context**begin e4c**context**begin>**
 - **<#e4c**context**is**ready e4c**context**is**ready>**
 - **<macros#e4c**using**context e4c**using**context>**
 - **<macros#e4c**reusing**context e4c**reusing**context>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**context**set**signal**mappings`

Assigns the specified signal mappings to the exception context.

## Parameters

  - **`mappings`**: the array of mappings.

## Detailed Description

This function assigns an array of mappings between the signals to be handled and the corresponding exception to be thrown.

**Warning**: Note that, on some specific platforms, the behavior of the standard `signal` function might be undefined for a multithreaded program, so use the signal handling system with caution.

## Preconditions

  - A program (or thread) **must** begin an exception context prior to calling `e4c**context**set**signal**mappings`. Such programming error will lead to an abrupt exit of the program (or thread).
  - `mappings` **must** be terminated by <macros#E4C**NULL**SIGNAL**MAPPING E4C**NULL**SIGNAL**MAPPING>.

## See Also

 - **<#e4c**context**get**signal**mappings e4c**context**get**signal**mappings>**
 - **<types#e4c**signal**mapping e4c**signal**mapping>**
 - **<variables#e4c**default**signal**mappings e4c**default**signal**mappings>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**context**get**signal**mappings`

Retrieves the signal mappings for the current exception context.

## Returns

  - The current array of mappings.

## Detailed Description

This function retrieves the current array of mappings between the signals to be handled and the corresponding exception to be thrown.

## Preconditions

  - A program (or thread) **must** begin an exception context prior to calling `e4c**context**get**signal**mappings`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

 - **<#e4c**context**set**signal**mappings e4c**context**set**signal**mappings>**
 - **<types#e4c**signal**mapping e4c**signal**mapping>**
 - **<variables#e4c**default**signal**mappings e4c**default**signal**mappings>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**get**status`

Returns the completeness status of the executing code block.

## Returns

  - The completeness status of the executing code block.

## Detailed Description

**Exception-aware** code blocks have a completeness status regarding the exception handling system. This status determines whether an exception was actually thrown or not, and whether the exception was caught or not.

The status of the current block can be obtained any time, provided that the exception context has begun at the time of the function call. However, it is sensible to call this function only during the execution of `finally` blocks.

## Preconditions

  - A program (or thread) **must** begin an exception context prior to calling `e4c**get**status`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

 - **<#e4c**get**status e4c**get**status>**
 - **<keywords#finally finally>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**get**exception`

Returns the exception that was thrown.

## Returns

  - The exception that was thrown in the current exception context (if any) otherwise `NULL`.

## Detailed Description

This function returns a pointer to the exception that was thrown in the surrounding **exception-aware** block, if any; otherwise `NULL`.

The function <#e4c**is**instance**of e4c**is**instance**of> will determine if the thrown exception is an instance of any of the defined exception types. The type of the thrown exception can also be compared for an exact type match.

```

{{{
try{
    ...
}catch(RuntimeException){
    const e4c_exception * exception = e4c_get_exception();
    if( e4c_is_instance_of(exception, SignalException.type) ){
        ...
    }else if(exception->type == NotEnoughMemoryException.type){
        ...
    }
}
}}}

```

The thrown exception can be obtained any time, provided that the exception context has begun at the time of the function call. However, it is sensible to call this function only during the execution of `finally` or `catch` blocks.

Moreover, a pointer to the thrown exception obtained **inside** a `finally` or `catch` block **must not be used from the **outside****.

The exception system objects are dinamically allocated and deallocated, as the program enters or exits `try`/`catch`/`finally` blocks. While it is legal to **copy** the thrown exception and access its `name` and `message` outside these blocks, care must be taken in order not to dereference the `cause` of the exception, unless it is a **deep copy** (as opposed to a **shallow copy**).

## Preconditions

  - A program (or thread) **must** begin an exception context prior to calling `e4c**get**exception`. Such programming error will lead to an abrupt exit of the program (or thread).

## See Also

 - **<types#e4c**exception e4c**exception>**
 - **<#e4c**is**instance**of e4c**is**instance**of>**
 - **<keywords#throw throw>**
 - **<keywords#catch catch>**
 - **<keywords#finally finally>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**library**version`

Gets the library version number.

## Returns

  - The version number associated with the library.

## Detailed Description

This function provides the same information as the `E4C**VERSION**NUMBER` macro, but the returned version number is associated with the actual, compiled library.

**Note**: This version number can be considered as the **run-time** library version number, as opposed to the **compile-time** library version number (specified by the header file).

**Remarks**: The library must be compiled with the corresponding header (i.e. library version number should be equal to header version number).

## See Also

 - **<macros#E4C**VERSION**NUMBER E4C**VERSION**NUMBER>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**is**instance**of`

Returns whether an exception instance is of a given type.

## Parameters

  - **`instance`**: the thrown exception.
  - **`exception**type`**: a previously defined type of exceptions.

## Returns

  - Whether the specified exception is an instance of the given type.

## Detailed Description

`e4c**is**instance**of` can be used to determine if a thrown exception **is an instance of a given type** defined through `E4C**DEFINE**EXCEPTION` and/or declared through `E4C**DECLARE**EXCEPTION`.

This macro is intended to be used in a `catch` block, or in a `finally` block provided that some exception was actually thrown (i.e. <#e4c**get**status e4c**get**status> returned `e4c**failed` or `e4c**recovered`).

```

{{{
try{
    ...
}catch(RuntimeException){
    const e4c_exception * exception = e4c_get_exception();
    if( e4c_is_instance_of(exception, SignalException.type) ){
        ...
    }else if(exception->type == NotEnoughMemoryException.type){
        ...
    }
}
}}}

```

## Preconditions

  - `instance` cannot be `NULL`.
  - `type` cannot be `NULL`.

## Throws

  - **NullPointerException**: if either `instance` or `type` is `NULL`.

## See Also

 - **<types#e4c**exception e4c**exception>**
 - **<types#e4c**exception**type e4c**exception**type>**
 - **<#e4c**get**exception e4c**get**exception>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**print**exception`

Prints a fatal error message regarding the specified exception.

## Parameters

  - **`exception`**: the uncaught exception.

## Detailed Description

This is a convenience function for showing an error message through the standard error output. It can be passed to <functions#e4c**context**set**handlers e4c**context**set**handlers> as the handler for uncaught exceptions, and will be used, by default, unless otherwise set up.

In absence of `NDEBUG`, this function prints as much information regarding the exception as it is available, whereas in presence of `NDEBUG`, only the `name` and `message` of the exception are printed.

## Preconditions

  - `exception` cannot be `NULL`.

## Throws

  - **NullPointerException**: if `exception` is `NULL`.

## See Also

 - **<types#e4c**uncaught**handler e4c**uncaught**handler>**
 - **<#e4c**context**begin e4c**context**begin>**
 - **<macros#e4c**using**context e4c**using**context>**

----

# <https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/icons/40x40/function.png> `e4c**print**exception**type`

Prints an ASCII graph representing an exception type's hierarchy.

## Parameters

  - **`exception**type`**: an exception type.

## Detailed Description

This is a convenience function for showing an ASCII graph representing an exception type's hierarchy through the standard error output.

For example, the output for `ProgramSignal2Exception` would be:

```

{{{
Exception hierarchy
________________________________________________________________

    RuntimeException
     |
     +--SignalException
         |
         +--ProgramSignalException
             |
             +--ProgramSignal2Exception
________________________________________________________________
}}}

```

## Preconditions

  - `exception**type` cannot be `NULL`.

## Throws

  - **NullPointerException**: if `exception**type` is `NULL`.

## See Also

 - **<types#e4c**exception**type e4c**exception**type>**

----

<https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/logo/exceptions4c**128.png>

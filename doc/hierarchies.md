
## Exception Hierarchies

The possible exceptions in a program are organized in a *pseudo-hierarchy* of
exceptions. `RuntimeException` is the root of the exceptions *pseudo-hierarchy*.
**Any** exception can be caught by a `catch(RuntimeException)` block, **except**
`AssertionException`.

When an exception is thrown, control is transferred to the nearest
dynamically-enclosing `catch` code block that handles the exception. Whether a
particular `catch` block handles an exception is found out by comparing the type
(and supertypes) of the actual thrown exception against the specified exception
in the `catch` clause.

A `catch` block is given an exception as a parameter. This parameter determines
the set of exceptions that can be handled by the code block. A block handles an
actual exception that was thrown if the specified parameter is either:

- the same type of that exception.
- the same type of any of the *supertypes* of that exception.

If you write a `catch` block that handles an exception with no defined
*subtype*, it will only handle that very specific exception. By grouping
exceptions in *hierarchies*, you can design generic `catch` blocks that deal
with several exceptions:

    /*                   Name             Default message   Supertype */
    E4C_DEFINE_EXCEPTION(ColorException, "Colorful error.", RuntimeException);
    E4C_DEFINE_EXCEPTION(RedException,   "Red error.",      ColorException);
    E4C_DEFINE_EXCEPTION(GreenException, "Green error.",    ColorException);
    E4C_DEFINE_EXCEPTION(BlueException,  "Blue error.",     ColorException);

    ...

    try{
        int color = chooseColor();
        if(color == 0xff0000) throw(RedException, "I don't like it.");
        if(color == 0x00ff00) throw(GreenException, NULL);
        if(color == 0x0000ff) throw(BlueException, "It's way too blue.");
        doSomething(color);
    }catch(GreenException){
        printf("You cannot use green.");
    }catch(ColorException){
        const e4c_exception * e = e4c_get_exception();
        printf("You cannot use that color: %s (%s).", e->name, e->message);
    }

When looking for a match, `catch` blocks are inspected in the order they appear
*in the code*. If you place a handler for a superclass before a subclass
handler, the second block will in fact be **unreachable**.

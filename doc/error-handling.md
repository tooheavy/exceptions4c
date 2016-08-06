
## Error Handling

This library provides you with a simple set of keywords (*macros*, actually)
which map the semantics of exception handling you're probably already used to:

- `try`
- `catch`
- `finally`
- `throw`

You can use exceptions in C by writing `try/catch/finally` blocks:

    #include "e4c.h"

    int foobar(){

        int foo;
        void * buffer = malloc(1024);

        if(buffer == NULL){
            throw(NotEnoughMemoryException, "Could not allocate buffer.");
        }

        try{
            foo = get_user_input(buffer, 1024);
        }catch(BadUserInputException){
            foo = 123;
        }finally{
            free(buffer);
        }

        return(foo);
    }

This way you will never have to deal again with boring error codes, or check
return values every time you call a function.

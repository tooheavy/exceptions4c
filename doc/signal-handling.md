
## Signal Handling

In addition, signals such as `SIGHUP`, `SIGFPE` and `SIGSEGV` can be handled in
an *exceptional* way. Forget about scary segmentation faults, all you need is to
catch `BadPointerException`:

    int * pointer = NULL;

    try{
        int oops = *pointer;
    }catch(BadPointerException){
        printf("No problem ;-)");
    }

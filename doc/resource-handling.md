
## Resource Handling

There are other keywords related to resource handling:

- `with... use`
- `using`

They allow you to express the *Dispose Pattern* in your code:

    /* syntax #1 */
    FOO f;
    with(f, e4c_dispose_FOO) f = e4c_acquire_FOO(foo, bar); use do_something(f);

    /* syntax #2 (relies on 'e4c_acquire_BAR' and 'e4c_dispose_BAR') */
    BAR bar;
    using(BAR, bar, ("BAR", 123) ){
        do_something_else(bar);
    }

    /* syntax #3 (customized to specific resource types) */
    FILE * report;
    e4c_using_file(report, "log.txt", "a"){
        fputs("hello, world!\n", report);
    }

This is a clean and terse way to handle all kinds of resources with implicit
acquisition and automatic disposal.

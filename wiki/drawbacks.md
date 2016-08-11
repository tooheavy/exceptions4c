---
layout: wiki
title: Drawbacks and other notes
---

# Drawbacks

 - Blocks introduced by a **keyword** **CAN'T** be **broken**. You cannot use neither `return`, `goto`, `break` or `continue` to jump out of any `try`, `catch`, `finally`, `with` or `use` blocks. You can `throw` exceptions, though. The same apply to blocks introduced by `e4c**using**context` or `e4c**reusing**context`.
 - Exceptions are **unchecked**, so you should wrap your application's main loop with a **catch-all** block if you don't want your application exiting when an exception pops out `main`.

# Special cases

 - `AssertionException` cannot be caught whatsoever. In addition, if a <finally> block attempts to <retry> the block when an assertion exception has been previously thrown, the <retry> will not take place.

 - Fatal errors regarding the exception handling system (such as attempting to <throw> an exception without a proper context) cannot be handled by the program.

----

<https://raw.githubusercontent.com/guillermocalvo/exceptions4c/master/etc/img/logo/exceptions4c**128.png>

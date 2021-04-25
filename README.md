
# C++ Laboratorioes

This proyect contains code which shows how to use, in a basic way, the next concepts:

+ Pointers (**pointer.h/cpp**)
+ *const* keyword on functions (**const.h/cpp**).
+ *mutable* keyword on functions (**mutable.h/cpp**).
+ *virutal* keyword (polymophism) (**virtual.h/cpp**).
+ Left/Right Value (**rlvalue.h/cpp**).
+ Smart Pointers (**smartptr.h/cpp**).
+ Templates (**template.h/cpp**).
+ Constant Exprressions (**constex.h/cpp**).
+ Threads, Async and Promise/Future (**threads.h/cpp**).
+ Generate a Timestamp string with milliseconds. (**timetst.h/cpp**)

# Compiling

## Requierements

    1. GNU Make or above.
    2. g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
    3. GNU gdb (Ubuntu 9.2-0ubuntu1~20.04) 9, for debugin.
    4. Visual Studio Code 1.55 or above.



## Make

To get help to use the Makefile:
```shell
$make help
.............................................
Build test: make
Run, after building: make run
Build and activate debug: make DBGFLG=-g
Clean compiled files: make clean

```

To compile and build all the project:
```shell
$make
```

To compile and activate debug info:

```shell
$make DBGFLG=-g
```

To excute the program:
```shell
$make run
```

or

```shell
$./bin/tutorial
```

To clean all the compiled files:

```shell
$make clean
```

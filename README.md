
# C++ Laboratorioes

This proyect contains code which shows how to use, in a basic way, the next concepts:

+ Pointers (**pointer.h/cpp**)
+ *const* keyword on functions (**const.h/cpp**).
+ *mutable* keyword on functions (**mutable.h/cpp**).
+ *virutal* keyword (polymophism) (**virtual.h/cpp**).
+ Left/Right Value (**rlvalue.h/cpp**).
+ Smart Pointers (**smartptr.h/cpp**).
+ *template* samples (**template.h/cpp**).
+ *constexpr* sample (**constex.h/cpp**).
+ *thread*, *async* and *promise*/*future* samples (**threads.h/cpp**).
+ Generate a Timestamp string with milliseconds. (**timetst.h/cpp**)
+ Getting file information. (**file.h/cpp**)
+ Samples of Lambdas functions. (**lambdas.h/cpp**)
+ Samples of *string_view*. (**str_view.h/cpp**)
+ Pairs and Tupples. (**tpair.h/cpp**)
+ Samples of metaprogramming. (**metaprog.h/cpp**)
+ Passing different kind of parameter in functions. (**parameters.h/cpp**)
+ A Matrix template library and how to use it. (**matrix.hpp, test_matrix.h/cpp**)

# Compiling

## Requierements

    1. C++17 Standar.
    2. GNU Make or above.
    3. CMAKE 3.18 or later
    4. GNU gdb 9 or later, for debugin.
    5. Visual Studio Code
    

## Pre-Compile steps

> Considere **${BASE_DIR}** as the base dir of the proyect.

1. Create a new dir called *{BASE_DIR}/build* and change into that new directory.
2. execute the one of these three commands:

    a. To build a release producto.

```shell
$ cmake ../src
```

	b. To build and activate debug info.

```shell
$ cmake ../src -DUSE_DEBUG=ON
```

    c. To build and deactivate debug info, producing a release product.

```shell
$ cmake ../src -DUSE_DEBUG=OFF
```

## Compiling

Once the precompile stepts have been performed, compile the project with the next command:

> You must be located into the path *{BASE_DIR}/build*

```shell
$ cmake --build .
```

The console should shows an output like this:

```shell
$ cmake --build .
Consolidate compiler generated dependencies of target cpplab
[  5%] Building CXX object CMakeFiles/cpplab.dir/const.cpp.o
[ 10%] Building CXX object CMakeFiles/cpplab.dir/constex.cpp.o
[ 15%] Building CXX object CMakeFiles/cpplab.dir/main.cpp.o
[ 20%] Building CXX object CMakeFiles/cpplab.dir/mutable.cpp.o
[ 25%] Building CXX object CMakeFiles/cpplab.dir/pointer.cpp.o
[ 30%] Building CXX object CMakeFiles/cpplab.dir/rlvalue.cpp.o
[ 35%] Building CXX object CMakeFiles/cpplab.dir/smartptr.cpp.o
[ 40%] Building CXX object CMakeFiles/cpplab.dir/template.cpp.o
[ 45%] Building CXX object CMakeFiles/cpplab.dir/virtual.cpp.o
[ 50%] Building CXX object CMakeFiles/cpplab.dir/threads.cpp.o
[ 55%] Building CXX object CMakeFiles/cpplab.dir/timetst.cpp.o
[ 60%] Building CXX object CMakeFiles/cpplab.dir/file.cpp.o
[ 65%] Building CXX object CMakeFiles/cpplab.dir/lambdas.cpp.o
[ 70%] Building CXX object CMakeFiles/cpplab.dir/str_view.cpp.o
[ 75%] Building CXX object CMakeFiles/cpplab.dir/maps.cpp.o
[ 80%] Building CXX object CMakeFiles/cpplab.dir/tpair.cpp.o
[ 85%] Building CXX object CMakeFiles/cpplab.dir/metaprog.cpp.o
[ 90%] Building CXX object CMakeFiles/cpplab.dir/parameters.cpp.o
/home/jorge/vsworkspace/CPPLab/src/parameters.cpp: En la función ‘jomt::test::KeyClass&& createKey(int)’:
/home/jorge/vsworkspace/CPPLab/src/parameters.cpp:14:21: aviso: reference to local variable ‘key’ returned [-Wreturn-local-addr]
   14 |     return std::move(key);
      |            ~~~~~~~~~^~~~~
/home/jorge/vsworkspace/CPPLab/src/parameters.cpp:11:14: nota: se declara aquí
   11 |     KeyClass key(key_i);
      |              ^~~
[ 95%] Building CXX object CMakeFiles/cpplab.dir/test_matrix.cpp.o
[100%] Linking CXX executable cpplab
[100%] Built target cpplab
```

Once the project has been created, you can run it with the command `./cpplab`, on the same path (*{BASE_DIR}/build*):

```shell
$ ./cpplab 

-----------------------
Commands:
	quit: Quit.
	ptrs: Pointers Test.
	const: Consts Test.
	mutable: Mutable Test.
	virtual: Virutal Test.
	lrvalue: LRValue Test.
	smartptr: Smart Pointers Test.
	templates: Templates Test.
	threads: Threads Test.
	constexpr: Constant Expr Test.
	time: Time Test.
	file: File Test.
	lambdas: Lambdas Test.
	strview: String View Test.
	maps: Maps Test.
	pairs: Pairs & Tuples Test.
	metap: Metaprograming Test.
	params: Parameters Test.
	matrix: Matrix Operations.
-----------------------

$ _
```

To clear the compiler/build output 

```shell
$ cmake --build . --target clean
```
# stdout/stderr glue for Wii U homebrew

This is a simple implementation of code that redirects stdout/stderr to WHBLog functions,
to be used on the Wii U.

This code is licensed under APL 2.0, LGPL 3.0+ and MIT licenses.


## Usage

Simply copy `wiiu-stdout.c` or `wiiu-stdout.cpp` to your project. Either file is fine, and
should work for both C and C++ programs.

To also get `stderr` support, you must also copy `wiiu-stderr.c` or `wiiu-stderr.cpp`.

There is no need to call any function. Everything is initialized and cleaned up
automatically, using GCC's `constructor`/`destructor` attributes.


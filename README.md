# stdout/stderr glue for Wii U homebrew

This is a simple implementation of code that redirects `stdout`/`stderr` to system log (using
`OSConsoleWrite()`) to be used on the Wii U.

This code is licensed under APL 2.0, LGPL 3.0+ and MIT licenses.


## Usage

Simply copy `wiiu-stdout.c` to your project.

The glue code is initialized automatically using GCC's `constructor`/`destructor` attributes.


## Using as a library

If you try to use this code in a library, the linker will discard the objects if you do not call
any function from them.

To avoid this, just include `wiiu-stdout.h` and call `wiiu_init_stdout()` inside your `main()`
function.

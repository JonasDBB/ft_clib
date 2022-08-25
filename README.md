# ft_clib

implementation of c library functions I need for my Codam projects with unit tests and cmake.

`cmake -S . -B build && cmake --build build` to build

`cd build && make` to compile

`./clib_test` (in {src_dir}/build/) to run

`./clib_test --gtest_filter=clib.strlen` to run only `strlen` tests etc

Or use nice CLion integration :)
#
Tested in debian docker container

cmake_minimum_required(VERSION 3.16)
project(clib_test)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(ft_clib ft_clib.c)
target_compile_options(ft_clib PUBLIC
		-Wall
		-Werror
		-Wextra
		-g3
		-fsanitize=address
		)
target_link_options(ft_clib PUBLIC
		-fsanitize=address
)

add_executable(
		clib_test
		clib_test.cpp
)
target_link_libraries(
		clib_test
		GTest::gtest_main
		ft_clib
)

include(GoogleTest)
gtest_discover_tests(clib_test)


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

add_library(ft_clib)
target_include_directories(ft_clib PUBLIC ft_clib)
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

add_executable(clib_test)
target_include_directories(clib_test PRIVATE ft_clib)
target_link_libraries(
		clib_test
		GTest::gtest_main
		ft_clib
)

add_library(ft_list)
target_include_directories(ft_list PUBLIC ft_list)
target_compile_options(ft_list PUBLIC
		-Wall
		-Werror
		-Wextra
		-g3
		-fsanitize=address
		)
target_link_options(ft_list PUBLIC
		-fsanitize=address
		)

add_executable(list_test)
target_include_directories(list_test PRIVATE ft_list)
target_link_libraries(
		list_test
		GTest::gtest_main
		ft_list
)

add_library(ft_printf)
add_dependencies(ft_printf ft_clib)
target_include_directories(ft_printf PUBLIC ft_printf)
target_include_directories(ft_printf PRIVATE ft_clib)
target_compile_options(ft_printf PUBLIC
		-Wall
		-Werror
		-Wextra
		-g3
		-fsanitize=address
		)
target_link_options(ft_printf PUBLIC
		-fsanitize=address
		)
target_link_libraries(ft_printf ft_clib)

add_executable(printf_test)
target_include_directories(printf_test PRIVATE ft_printf)
target_link_libraries(
		printf_test
		GTest::gtest_main
		ft_printf
)

add_subdirectory(ft_clib)
add_subdirectory(ft_list)
add_subdirectory(ft_printf)

include(GoogleTest)
gtest_discover_tests(clib_test)

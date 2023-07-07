target_sources(ft_printf PRIVATE
		ft_printf.c
		buffer.c
		printloop.c
		flags.c
		print_functions.c
		print_number.c
		)

target_sources(printf_test PRIVATE
		printf_test.cpp
		)
target_sources(ft_printf PRIVATE
		ft_printf.c
		buffer.c
		printloop.c
		flags.c
		print_dispatcher.c
		print_number.c
		print_string.c
		)

target_sources(printf_test PRIVATE
		printf_test.cpp
		)
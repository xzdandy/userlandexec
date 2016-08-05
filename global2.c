#include <libstatic/libstatic.h>
#include <libstatic/crt.h>

long uninitialized;
long initialized = 12345678;

void
c_main(int ac, char **av, char **env)
{
	print_string(1, "Initialized global at ");
	print_hex(1, &initialized);
	print_string(1, ", contains ");
	print_long(1, initialized);
	print_string(1, "\n");

	print_string(1, "Unitialized global at ");
	print_hex(1, &uninitialized);
	print_string(1, ", contains ");
	print_long(1, uninitialized);
	print_string(1, "\n");

	linux_exit(0);
}

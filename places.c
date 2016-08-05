#include <libstatic/libstatic.h>

#include <libstatic/crt.h>

unsigned long global = 0x997UL;

void
c_main(int ac, char **av, char **env)
{
	unsigned long local;
	char *str = "Some string";
	char buffer[1024];

	to_hex((unsigned long)&ac, buffer);
	print_string(1, "Address of argc: ");
	print_string(1, buffer);
	print_string(1, "\n");

	to_hex((unsigned long)&global, buffer);
	print_string(1, "Address of global: ");
	print_string(1, buffer);
	print_string(1, "\n");

	to_hex((unsigned long)&local, buffer);
	print_string(1, "Address of local: ");
	print_string(1, buffer);
	print_string(1, "\n");

	to_hex((unsigned long)c_main, buffer);
	print_string(1, "Address of c_main: ");
	print_string(1, buffer);
	print_string(1, "\n");

	to_hex(global, buffer);
	print_string(1, "Contents of global: ");
	print_string(1, buffer);
	print_string(1, "\n");

	linux_exit(0);
}

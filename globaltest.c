#include <libstatic/libstatic.h>
#include <libstatic/crt.h>

int global = 12;

void
print_address(char *phrase, void *address)
{
    char buf[256];
    to_hex((unsigned long)address, buf);
    print_string(1, phrase);
    print_string(1, " 0x");
    print_string(1, buf);
    print_string(1, "\n");
}

void
c_main(int ac, char **av, char **ev)
{
	print_address("global at ", (void *)&global);
	print_address("global contains ", (void *)global);
	global = ac;
	linux_exit(global);
}

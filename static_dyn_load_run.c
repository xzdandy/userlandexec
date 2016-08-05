#include <libstatic/libstatic.h>

#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <libstatic/crt.h>
#include <ulexec.h>

#define JMP_ADDR(x) asm("\tjmp  *%0\n" :: "r" (x))
#define SET_STACK(x) asm("\tmovq %0, %%rsp\n" :: "r"(x))


void c_main(int ac, char **av, char **env)
{
	char *file_to_map = av[1];
	void *mapped;
	void *fptr;
	struct stat sb;
	Elf64_Ehdr *junk1 = NULL, *junk2 = NULL;

	/* print_string(1, "static_dyn_load_run\n"); */

	if (0 > linux_stat(file_to_map, &sb))
	{
		error_msg("stat() failed ");
		linux_exit(1);
	}

	mapped = linux_mmap(NULL, sb.st_size, 0x07, 0x22, -1, 0);
	/* print_address("File mapped in at", mapped); */

	if (mapped == (void *)-1)
	{
		error_msg("mmap() failed ");
		linux_exit(1);
	}

	copy_in(file_to_map, mapped);

	fptr = load_elf(mapped, 1, &junk1, &junk2);
	/* print_address("Entry point at", fptr); */

	linux_munmap(mapped, sb.st_size);

	/* print_address("Y setting stack to ", av - 1); */
	SET_STACK(av - 1);
	JMP_ADDR(fptr);
}

void
error_msg(char *msg)
{
	char buf[32];
	print_string(1, msg);
	print_string(1, " ");
	to_decimal(errno, buf);
	print_string(1, buf);
	print_string(1, "\n");
}

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

void *
memcpy(void *dest, const void *src, unsigned long n)
{
	unsigned long i;
	unsigned char *d = (unsigned char *)dest;
	unsigned char *s = (unsigned char *)src;

	for (i = 0; i < n; ++i)
		d[i] = s[i];

	return dest;
}

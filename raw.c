#include <libstatic/libstatic.h>
/*
 * Prove that when the kernel finally
 * lets a process execute, the only thing that
 * process gets is the address of the bottom of
 * the stack in %rsp.
 */
asm (
	".text\n"
	".global _start\n"
		".type _start,@function\n"
		"_start:\n\t"
		"movq (%rsp),%rsi\n\t"
		"movq %rsp,%rdi\n\t"
		"jmp c_main"
	);

void
c_main(void *stack, unsigned long argc)
{
	print_string(1, "Stack at: ");
	print_hex(1, (unsigned long)stack);
	print_string(1, "\n");
	print_string(1, "argc: ");
	print_hex(1, argc);
	print_string(1, "\n");
	linux_exit(0);
}

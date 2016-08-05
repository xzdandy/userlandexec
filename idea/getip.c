/* getip.c tests the asm code to get the instruction pointer of current instruction.
 */
#include <stdio.h>

/* lea rax, [rip] only works for x86_64.
 * this actually get the ip for next instruction.
 */
#define GET_IP(x) asm("\tlea (%%rip), %0\n" : "=r" (x) ::)

#define JMP_ADDR(x) asm("\tjmp *%0\n" :: "r" (x))

#define DESTROY_STACK() asm("\tleave \n" :::)

static void *back_address;

void jmp_back(void)
{
/* we need clean up the return address in stack.
 */
    DESTROY_STACK();
    JMP_ADDR(back_address + 12);
}

int main(int argc, char ** argv)
{
    void *cip1, *cip2;
//    GET_IP(cip1);
    GET_IP(back_address);
    jmp_back();
//    GET_IP(cip2);
//    printf("ip: %p, %p, difference: %ld\n", cip2, cip1, cip2 - cip1);
    printf("We are back!\n");
    return 0;
}

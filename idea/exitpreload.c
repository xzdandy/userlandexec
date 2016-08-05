#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>

/*
void __attribute__ ((constructor)) library_init(void)
{
}
*/


void _exit(int status)
{
    printf("We are in _exit\n");
    void __attribute__ ((noreturn)) (*real__exit)(int) = dlsym(RTLD_NEXT, "_exit");
    real__exit(status);
}

static void print_maps(void)
{
    char rbuf[1024];
    int fd, cc;

    fd = open("/proc/self/maps", O_RDONLY, 0);
    while (0 < (cc = read(fd, rbuf, sizeof(rbuf))))
        write(1, rbuf, cc);
    close(fd);
}


void exit(int status)
{
    printf("We are in exit\n");
//    char * value = getenv("PIPE_READ");
    print_maps();
    void __attribute__ ((noreturn)) (*real_exit)(int) = dlsym(RTLD_NEXT, "exit");
    real_exit(status);
}

#include <libstatic/libstatic.h>

void
print_maps(void)
{
	char rbuf[1024];
	int fd, cc;

	fd = linux_open("/proc/self/maps", 0, 0);
	while (0 < (cc = linux_read(fd, rbuf, sizeof(rbuf))))
		linux_write(1, rbuf, cc);
	linux_close(fd);
}

#include <libstatic/libstatic.h>

static void process_image_backup(unsigned long low, unsigned long high)
{
    #define PBPATH "process_image_backup.tmp"
    int fd = linux_open(PBPATH, 01102, 0666);
    linux_write(fd, (void *) low, high - low);
    linux_close(fd);
}

void
unmap(char *progname)
{
	char buf[1024], *p;
	char rbuf[2048];
	int cc, fd;

	fd = linux_open("/proc/self/maps", 0, 0);

	p = &buf[0];

	while (0 < (cc = linux_read(fd, rbuf, sizeof(rbuf))))
	{
		int i;

		for (i = 0; i < cc; ++i)
		{
			int c = rbuf[i];

			if ('\n' != c)
				*p++ = c;
			else {
				*p = '\0';
				/* When a line from /proc/self/maps shows up as having been
				 * mapped in from this running program, ld.so or libc, unmap it.
				 * This will keep the exec'd program's address space a lot
				 * cleaner.  But even a 32-bit address space can hold 2 copies
				 * of glibc without ill effects, so you don't really have to
				 * munmap() anything other than the program calling ul_exec() */
				if (strstr(buf, progname) || strstr(buf, "libdl") || strstr(buf, "/usr/lib/ld-")
					|| strstr(buf, "/lib64/ld-") || strstr(buf, "libc"))
				{
					char *u;
					char *first, *second;
					unsigned long low, high;

					u = strchr(buf, ' ');
					*u = '\0';

					first = buf;

					second = strchr(first, '-');
					*second = '\0';
					++second;

					low = strtoul(first, NULL, 0x10);
					high = strtoul(second, NULL, 0x10);

                    if (strstr(buf, progname))
                        process_image_backup(low, high);

					linux_munmap((void *)low, high-low);
				}

				p = &buf[0];
			}
		}
	}

	linux_close(fd);

}

/*
 * Rewrite the program cat from Chapter 7 using read, write,
 * open and close instead of their standard library equivaents. Perform
 * experiments to determine the relative speeds of the two versions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

void filecopy(int ifd, int ofd);

int main(int argc, char **argv)
{
    char *prog = argv[0];
    int fd;

    if (argc == 1) /* copy stdin to stdout */
        filecopy(0, 1);
    else {
        while (++argv, --argc > 0) {
            if (fd = open(*argv, O_RDONLY, 0), fd == -1) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                continue;
            } else {
                filecopy(fd, 1);
                close(fd);
            }
        }
    }
    exit(0);
}

/* filecopy: copy file ifd to ofd */
void filecopy(int ifd, int ofd)
{
    char buf[BUFSIZ];
    int n;

    while (n = read(ifd, &buf, BUFSIZ), n > 0)
        write(ofd, &buf, n);
}

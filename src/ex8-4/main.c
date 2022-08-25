/*
 * The standard library function
 *
 *     int fseek(FILE *fp, long offset, int origin)
 *
 * is identical to lseek except that fp is a file pointer instead of a file descriptor
 * and the return value is an int status, not a position. Write fseek. Make sure
 * that your fseek coordinates propertly with the buffering done for the other
 * functions of the library.
 */

/* this file is used for testing; the exercise is in other files */

// #include <stdio.h>
#include "stdio.h"

int main(void)
{
    int c;

    /* push forward stdin for testing */
    FILE *fp = fopen("main.c", "r");
    while (c = getc(fp), c != EOF)
        putchar(c);
    fseek(fp, SEEK_SET, 0);
    while (c = getc(fp), c != EOF)
        putchar(c);
    /* we're forced to put a call to fflush since exit(3) flushes the real stdio.h's
     * buffers, not our ones */
    fflush(stdout);
    return 0;
}

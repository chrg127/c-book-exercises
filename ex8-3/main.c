/* Design and write _flushbuf, fflush and fclose. */

/* this file is used for testing; the exercise is in other files */

#include "stdio.h"

int main(void)
{
    int c;

    while (c = getchar(), c != EOF)
        putchar(c);
    /* we're forced to put a call to fflush since exit(3) flushes the real stdio.h's
     * buffers, not our ones */
    fflush(stdout);
    return 0;
}

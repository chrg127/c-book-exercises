/*
 * Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly.
 * C comments do not nest.
 */

#include <stdio.h>

#define NORMAL      0
#define IN_COMMENT  1
#define IN_STRING   2

int main(void)
{
    int c, cur, last, i;
    int state;

    state = NORMAL;
    cur = last = '\0';
    while (c = getchar(), c != EOF) {
        last = cur;
        cur = c;
        if (state == NORMAL && last == '/' && cur == '*')
            state = IN_COMMENT;
        if (state == IN_COMMENT && last == '*' && cur == '/') {
            /*
             * we must read 2 characters here to make sure not to output the end of a comment
             * other errors (outputting '\0' or EOF) are already handled by the standard output
             * (or rather, the terminal)
             */
            last = getchar();
            cur  = getchar();
            state = NORMAL;
        }
        if (state == NORMAL && cur == '"')
            state = IN_STRING;
        if (state == IN_STRING && (cur == '"' || cur == '\n'))
            state = NORMAL;
        if (state != IN_COMMENT)
            putchar(last);
    }

    return 0;
}

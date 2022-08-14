/*
 * Write a program to check a C program for rudimentary syntax
 * errors like unbalanced parentheses, brackets and spaces. Don't forget about
 * quotes, both single and double, escape sequences and comments. (This program
 * is hard if you do it in full generality.)
 */

/* this exercise should be ok except for the escape sequence part.
 * it also errors out if the input is this program, likely due to parentheses in
 * char quotes. I don't feel like fixing that. */

#include <stdio.h>

#define NORMAL      0
#define IN_COMMENT  1
#define IN_STRING   2
#define IN_CHAR     3

int reverse_paren(int p);

int main(void)
{
    int c, cur, last, i, paren_count, expected;
    int state;
    int paren_stack[1000];

    state = NORMAL;
    paren_count = 0;
    cur = last = '\0';
    while (c = getchar(), c != EOF) {
        last = cur;
        cur = c;

        /* save whether we are in a comment or string or char */
        if (state == NORMAL && last == '/' && cur == '*')
            state = IN_COMMENT;
        if (state == IN_COMMENT && last == '*' && cur == '/') {
            last = getchar();
            cur  = getchar();
            state = NORMAL;
        }
        if (state == NORMAL && cur == '"')
            state = IN_STRING;
        else if (state == IN_STRING && (cur == '"' || cur == '\n')) {
            state = NORMAL;
            if (cur == '\n')
                printf("error: unterminated string\n");
        }
        if (state == NORMAL && cur == '\'')
            state = IN_CHAR;
        else if (state == IN_CHAR && (cur == '\'' || cur == '\n'))
            state = NORMAL;

        /* check for errors with parentheses */
        if (state == NORMAL) {
            if (cur == '(' || cur == '[' || cur == '{') {
                paren_stack[paren_count++] = cur;
            } else if (cur == ')' || cur == ']' || cur == '}') {
                expected = reverse_paren(paren_stack[paren_count-1]);
                if (expected != cur)
                    printf("error: mismatched parentheses\n");
                paren_count--;
            }
        }
    }

    if (state == IN_COMMENT)
        printf("error: unterminated comment\n");
    if (state == IN_STRING)
        printf("error: unterminated string\n");
    if (state == IN_CHAR)
        printf("error: unterminated character\n");
    if (paren_count != 0)
        printf("error: unterminated parentheses\n");
    return 0;
}

int reverse_paren(int p)
{
    if (p == '(')
        return ')';
    if (p == '[')
        return ']';
    if (p == '{')
        return '}';
    return '\0';
}

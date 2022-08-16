/*
 * Write a function escape(s, t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies the
 * string t to s. Use a switch. Write a function for the other direction as well,
 * converting escape sequences into the real characters.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

void escape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; s[i]; i++) {
        switch (s[i]) {
        case '\n':
            t[j++] = '\\';
            t[j++] = 'n';
            break;
        case '\t':
            t[j++] = '\\';
            t[j++] = 't';
            break;
        default:
            t[j++] = s[i];
        }
    }
    t[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j, end;

    for (i = 0, j = 0, end = 0; s[i] || end; i++) {
        switch (s[i]) {
        case '\\':
            i++;
            switch (s[i]) {
            case 'n':
                t[j++] = '\n';
                break;
            case 't':
                t[j++] = '\t';
                break;
            case '\0':
                end = 1;
                break;
            default:
                t[j++] = '\\';
                t[j++] = s[i];
            }
            break;
        default:
            t[j++] = s[i];
        }
    }
    t[j] = '\0';
}

/* tests */
int main(void)
{
    char a[] = "hello\nworld";
    char t[100];
    char r[100];
    escape(a, t);
    unescape(t, r);
    assert(strcmp(a, r) == 0);

    char b[] = "newline at the end\n";
    escape(b, t);
    unescape(t, r);
    assert(strcmp(b, r) == 0);

    printf("all tests passed\n");

    return 0;
}

#include <stdio.h>

int main(void)
{
    int c, n, tmp;

    n = 0;
    while (c = getchar(), c != EOF) {
        if (c == ' ' || c == '\r' || c == '\t' || c == '\n') {
            tmp = c;
            while (c == tmp)
                c = getchar();
            // technically, at this point ungetc hasn't been introduced in the book.
            // I decided to use it here though because it's the simplest way.
            ungetc(c, stdin);
            printf("%c", tmp);
        } else
            printf("%c", c);
    }
    return 0;
}

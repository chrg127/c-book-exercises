/*
 * Write a program to print a set of files, starting each new one on a
 * new page, with a title and a running page count for each file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 1000

char *strip_extension(char *s)
{
    int len;

    len = strlen(s) - 1;
    for ( ; len > 0; len--) {
        if (s[len] == '.') {
            s[len] = '\0';
            return s;
        }
    }
}

int main(int argc, char **argv)
{
    int page, c;
    FILE *fp;
    char *prog = *argv;

    if (argc < 2) {
        printf("Usage: %s [file...]\n", *argv);
        return 1;
    } else {
        page = 1;
        while (++argv, --argc > 0) {
            if (fp = fopen(*argv, "r"), fp == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                return 1;
            } else {
                printf("%s\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d\n\n", strip_extension(*argv), page);
                while(c = fgetc(fp), c != EOF)
                    putchar(c);
                printf("\n");
            }
            page++;
        }
    }
    return 0;
}

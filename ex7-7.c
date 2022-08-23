/*
 * Modify the patterning finding program of Chapter 5 to take its input
 * from a set of named files or, if no files are named as arguments, from the
 * standard input. Should the file name be printed when a matching line is found?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define MAXFILES 100

void findpattern(char *, int *, FILE *, char *);
int get_line(char *s, int lim, FILE *fp);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    char *prog = argv[0], *pattern;
    int found = 0;
    FILE *fp;

    if (argc < 2) {
        printf("usage: %s [pattern] [files...]\n", prog);
        exit(1);
    }
    pattern = argv[1];
    if (argc == 2)
        findpattern(pattern, &found, stdin, "stdin");
    else {
        ++argv; /* skip pattern argument */
        while (--argc > 1) {
            if (fp = fopen(*++argv, "r"), fp == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else
                findpattern(pattern, &found, fp, *argv);
        }
    }
    return found;
}

void findpattern(char *pattern, int *found, FILE *fp, char *filename)
{
    char line[MAXLINE];
    int lineno = 0;

    while (get_line(line, MAXLINE, fp) > 0) {
        lineno++;
        if (strstr(line, pattern) != NULL) {
            printf("%s:%d:%s", filename, lineno, line);
            (*found)++;
        }
    }
}

/* get_line: read a line from input and return its lenght */
int get_line(char s[], int lim, FILE *fp)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = fgetc(fp)) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

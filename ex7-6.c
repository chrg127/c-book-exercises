#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 5000

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2, **current;
    char line[MAXLINE], line2[MAXLINE];
    char *prog = argv[0];
    char *file1 = argv[1];
    char *file2 = argv[2];

    if (argc != 3) {
        printf("Usage: %s file1 file2\n", *argv);
        return;
    }

    current = &fp1;
    while (--argc > 0) {
        if ((*current = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        }
        current = &fp2;
    }

    while (fgets(line, MAXLINE, fp1) != NULL && fgets(line2, MAXLINE, fp2) != NULL) {
        if (strcmp(line, line2) != 0) {
            printf("%s:\n", file1);
            fputs(line, stdout);
            printf("%s:\n", file2);
            fputs(line2, stdout);
            break;
        }
    }

    return 0;
}

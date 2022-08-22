/*
 * Write a program that reads a C program and prints in alphabetical
 * order each group of of variable names that are identical in the first 6
 * characters, but different somewhere thereafter. Don't count words within strings
 * and comments. Make 6 a parameter that can be set from the command line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct listnode {
    int num;
    struct listnode *next;
};

struct tnode {         /* the tree node */
    char *prefix;               /* for some group of words with this prefix */
    struct listnode *group;     /* the group of words */
    struct tnode *left;         /* left child */
    struct tnode *right;        /* right child */
};

struct tnode *addtree(struct tnode *p, char *w, int prefix_len);
void treeprint(struct tnode *p);
int getword(char *, int);
struct tnode *talloc(void);
char *str_dup(char *);
char *strdup2(char *s, int lim);
int skip_space();
int getch(void);
void ungetch(int c);
struct listnode *list_alloc(char *w);
struct listnode *addlist(struct listnode *n, char *w);
void listprint(struct listnode *p);

int main(int argc, char **argv)
{
    struct tnode *root;
    char word[MAXWORD];
    int prefix_len = 6;

    if (argc > 2) {
        printf("usage: %s [n]\n", *argv);
        return 1;
    } else if (argc == 2) {
        prefix_len = atoi(argv[1]);
        if (prefix_len == 0) {
            printf("error: invalid argument: %s\n", argv[1]);
            return 1;
        }
    }

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word, prefix_len);
    treeprint(root);
    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int prefix_len)
{
    int cond;
    char *word;

    if (p == NULL) {  /* a new prefix has arrived */
        p = talloc(); /* make a new node */
        p->prefix = strdup2(w, prefix_len);
        p->group  = list_alloc(w);
        p->left = p->right = NULL;
    } else if (cond = strncmp(w, p->prefix, prefix_len), cond == 0) {
        p->group = addlist(p->group, w);
    } else if (cond > 0) /* less than into left subtree */
        p->right = addtree(p->right, w, prefix_len);
    else               /* greater than into right subtree */
        p->left  = addtree(p->left,  w, prefix_len);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("list for prefix %s:\n", p->prefix);
        listprint(p->group);
        printf("\n");
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* list_alloc: make a listnode */
struct listnode *list_alloc(char *w)
{
    struct listnode *p = malloc(sizeof(struct listnode));
    p->word = strdup(w);
    p->next = NULL;
    return p;
}

/* addlist: add a new node to p */
struct listnode *addlist(struct listnode *p, char *w)
{
    struct listnode *new = list_alloc(w);
    new->next = p;
    return new;
}

/* listprint: print an entire list */
void listprint(struct listnode *p)
{
    for ( ; p; p = p->next)
        printf("    %s\n", p->word);
}

/* str_dup: make a copy of s */
char *str_dup(char *s)
{
    char *p;

    p = malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* strdup2: make a copy of s, up to lim characters */
char *strdup2(char *s, int lim)
{
    char *p;

    p = malloc(lim + 1); /* +1 for '\0' */
    if (p != NULL)
        strncpy(p, s, lim);
    p[lim] = '\0';
    return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    c = skip_space();
    if (c != EOF)
        *w++ = c;
    if (c == '"') {
        while (*w++ = c = getch(), c != '"' && c != '\n')
            ;
        return word[0];
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (*w = getch(), !isalnum(*w) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

/* skip space, comments and preprocessor control lines */
int skip_space()
{
    int c, d;
    for (;;) {
        switch (c = getch()) {
        case ' ': case '\t': case '\r':
            break;
        case '/':
            if (d = getch(), d == '*') {
                for ( ; !(c == '*' && d == '/'); ) {
                     c = d;
                     d = getch();
                }
            } else {
                ungetch(d);
                return c;
            }
            break;
        case '\n':
            if (c = getch(), c == '#') {
                while (c = getch(), c != '\n')
                    ;
            } else
                ungetch(c);
            break;
        default:
            return c;
        }
    }
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

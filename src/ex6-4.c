/*
 * Write a program that prints the distinct words in its input sorted
 * into decreasing order of frequency of occurence. Precede each word by its count.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode {         /* the tree node */
    char *word;          /* points to the text */
    int count;           /* */
    struct tnode *left;  /* left child */
    struct tnode *right; /* rigth child */
};

void treeprint(struct tnode *p);
int getword(char *, int);
struct tnode *addtree(struct tnode *p, char *w);
struct tnode *talloc(void);
char *str_dup(char *);
int skip_space();
int getch(void);
void ungetch(int c);
struct tnode *add_all(struct tnode *new, struct tnode *old);

int main(int argc, char **argv)
{
    struct tnode *root, *root2;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    /* copy words inside a new tree, ordered by count */
    root2 = NULL;
    root2 = add_all(root2, root);
    treeprint(root2);
    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {  /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if (cond = strcmp(w, p->word), cond == 0) {
        p->count++;
    } else if (cond > 0) /* less than into left subtree */
        p->right = addtree(p->right, w);
    else               /* greater than into right subtree */
        p->left  = addtree(p->left, w);
    return p;
}

/* addtree2: add q to p, looking at q->count */
struct tnode *addtree2(struct tnode *p, struct tnode *q)
{
    if (p == NULL) {
        p = talloc();
        p->word = q->word;
        p->count = q->count;
        p->left = p->right = NULL;
    } else if (q->count < p->count)
        p->left = addtree2(p->left, q);
    else
        p->right = addtree2(p->right, q);
    return p;
}

struct tnode *add_all(struct tnode *new, struct tnode *old)
{
    if (old != NULL) {
        new = add_all(new, old->left);
        new = addtree2(new, old);
        new = add_all(new, old->right);
    }
    return new;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
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

/* binsearch: find word in tab[0] ... tab [n - 1] */
int binsearch(char *word, char *tab[], int n)
{
    int cond, low, high, mid;

    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high)/2;
        if (cond = strcmp(word, tab[mid]), cond < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
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
    int c;
    for (;;) {
        switch (c = getch()) {
        case ' ': case '\t': case '\r': case '\n':
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

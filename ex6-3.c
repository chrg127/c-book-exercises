/*
 * Write a cross-referencer that prints a list of all words in a
 * document, and, for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so on.
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
    char *word;          /* points to the text */
    struct listnode *lines; /* keeps information about lines */
    struct tnode *left;  /* left child */
    struct tnode *right; /* rigth child */
};

struct tnode *addtree(struct tnode *p, char *w, int line);
void treeprint(struct tnode *p);
int getword(char *, int);
struct tnode *talloc(void);
char *str_dup(char *);
int skip_space();
int getch(void);
void ungetch(int c);
int get_current_line(void);
int is_banned(char *w);
struct listnode *list_alloc(int n);
struct listnode *addlist(struct listnode *p, int n);
void listprint(struct listnode *p);

int main(int argc, char **argv)
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (!isalpha(word[0]))
            continue;
        if (is_banned(word))
            continue;
        root = addtree(root, word, get_current_line());
    }
    treeprint(root);
    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int line)
{
    int cond;

    if (p == NULL) {  /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = str_dup(w);
        p->lines = list_alloc(line);
        p->left = p->right = NULL;
    } else if (cond = strcmp(w, p->word), cond == 0)
        p->lines = addlist(p->lines, line);
    else if (cond > 0) /* less than into left subtree */
        p->right = addtree(p->right, w, line);
    else               /* greater than into right subtree */
        p->left = addtree(p->left, w, line);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%s:", p->word);
        listprint(p->lines);
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
struct listnode *list_alloc(int n)
{
    struct listnode *p = malloc(sizeof(struct listnode));
    p->num  = n;
    p->next = NULL;
    return p;
}

/* addlist: add a new node to p */
struct listnode *addlist(struct listnode *p, int n)
{
    struct listnode *new = list_alloc(n);
    new->next = p;
    return new;
}

/* listprint: print an entire list */
void listprint(struct listnode *p)
{
    for ( ; p; p = p->next)
        printf(" %d", p->num);
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

char *banned_words[] = {
    "a", "and", "is", "the",
};

int is_banned(char *w)
{
    return binsearch(w, banned_words, sizeof(banned_words) / sizeof(banned_words[0])) != -1;
}

int line = 1;   /* line number is kept track of here */

int get_current_line(void)
{
    return line;
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
        case ' ': case '\t': case '\r':
            break;
        case '\n':
            line++;
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

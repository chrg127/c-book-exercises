/*
 * Implement a simple version of the #define processor (i.e. no
 * arguments) suitable for use with C programs, based on the routines of this
 * section. You may also find getch and ungetch helpful.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist {         /* table entry */
    struct nlist *next;  /* next entry in the chain */
    char *name;          /* defined name */
    char *defn;           /* replacement text */
};

static struct nlist *hashtab[HASHSIZE];

/* used by getword() to signal what king of word it got */
enum token_type { NONE, PREPROC_LINE, WORD, STRING, SPECIAL };

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int undef(char *name, char *defn);
char *str_dup(char *s);
int getword(char *, int);
int skip_space();
int getch(void);
void ungetch(int c);
enum token_type get_tokentype();

int main(void)
{
    char word[MAXWORD];
    int c;
    struct nlist *entry;
    enum token_type type;

    while (c = getword(word, MAXWORD), c != EOF) {
        type = get_tokentype();
        if (type == PREPROC_LINE)
            continue;
        else if (type != WORD)
            printf("%s", word);
        else if (entry = lookup(word), entry != NULL)
            printf("%s", entry->defn);
        else
            printf("%s", word);
    }
    return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  /* found */
    return NULL;        /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = str_dup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval]; /* put new block at the top */
        hashtab[hashval] = np;
    } else     /* already there */
        free((void *) np->defn);    /* free previous defn */
    if (np->defn = str_dup(defn), np->defn == NULL)
        return NULL;
    return np;
}

/* undef: remove a name and its definition from hashtab */
int undef(char *name, char *defn)
{
    struct nlist *np, *prev;

    prev = NULL;
    /* lookup name, keeping a reference to the previous element */
    for (np = hashtab[hash(name)]; np != NULL; prev = np, np = np->next) {
        if (strcmp(name, np->name) == 0) {
            /* found element, remove it */
            prev->next = np->next;
            free(np->name);
            free(np->defn);
            free(np);
            return 0;
        }
    }
    return 1; /* not found */
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

int tokentype = NONE;
int newline = 1;

enum token_type get_tokentype()
{
    return tokentype;
}

void skip_line()
{
    int c;

    while (c = getch(), c != '\n')
        ;
    ungetch(c);
}

/* preproc_line: parse a preprocessor line */
void preproc_line()
{
    int c;
    char word[MAXWORD];
    char defn[MAXWORD];
    char *w = word;

    /* get first word */
    while (c = getch(), isalpha(c))
        *w++ = c;
    ungetch(c);
    *w = '\0';
    /* we only handle #define */
    if (strcmp(word, "define") != 0) {
        skip_line();
        return;
    }

    /* get name into word and definition into defn */
    w = word;
    if (c = skip_space(), !isalpha(c)) {
        fprintf(stderr, "error: invalid #define identifier\n");
        skip_line();
        return;
    }
    for ( ; isalnum(c); c = getch())
        *w++ = c;
    *w = '\0';
    ungetch(c);

    w = defn;
    if (c = skip_space(), !isalnum(c)) {
        fprintf(stderr, "error: invalid #define identifier\n");
        skip_line();
        return;
    }
    for ( ; isalnum(c); c = getch())
        *w++ = c;
    *w = '\0';

    if (c != '\n') {
        fprintf(stderr, "error: stray characters after #define\n");
        skip_line();
        return;
    }
    ungetch(c);

    install(word, defn);
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    c = skip_space();
    if (newline && c == '#') {
        newline = 0;
        preproc_line();
        tokentype = PREPROC_LINE;
        return '#'; /* signal that a preproc line was found */
    }
    if (c != EOF)
        *w++ = c;
    if (c == '"') {
        while (*w++ = c = getch(), c != '"' && c != '\n')
            ;
        *w = '\0';
        tokentype = STRING;
        return word[0];
    }
    if (!isalnum(c)) {
        *w = '\0';
        tokentype = SPECIAL;
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (*w = getch(), !isalnum(*w) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    tokentype = WORD;
    return word[0];
}

/* skip space, comments and preprocessor control lines */
int skip_space()
{
    int c, d;
    for (;;) {
        switch (c = getch()) {
        case ' ': case '\t': case '\r':
            putchar(c);
            break;
        case '/':
            if (d = getch(), d == '*') {
                while (!(c == '*' && d == '/')) {
                     c = d;
                     d = getch();
                }
            } else {
                ungetch(d);
                return c;
            }
            break;
        case '\n':
            putchar(c);
            newline = 1;
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

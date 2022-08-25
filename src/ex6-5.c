/*
 * Write a function undef that will remove a name and definition
 * from the table maintained by lookup and install.
 */

#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {         /* table entry */
    struct nlist *next;  /* next entry in the chain */
    char *name;          /* defined name */
    char *defn;           /* replacement text */
};

static struct nlist *hashtab[HASHSIZE];

char *str_dup(char *s);

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

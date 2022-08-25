/*
 * Write a routine bfree(p, n), that will free an arbitrary block p
 * of n characters into the free list maintained by malloc and free. By using
 * bfree, a user can add a static or external array to the free list at any time.
 */

/*
 * note that this program is still compilabile by gcc, despite it emitting warnings
 * (due to overriding the malloc built-in declaration)
 */

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

union header {      /* block header */
    struct {
        union header *next;  /* next block if on free list */
        unsigned size;      /* size of this block */
    } s;
    max_align_t x;  /* force alignment of blocks */
};

typedef union header Header;

static Header base;             /* empty list to get started */
static Header *freep = NULL;    /* start of free list */

void *malloc(unsigned nbytes);
Header *morecore(unsigned nu);
void free(void *ap);

/*
 * ceiling division between two numbers.
 * ex: 2 / 5 = 0; ceil_div(2, 5) = 1
 */
unsigned ceil_div(unsigned n, unsigned b)
{
    return (n + b - 1) / b + 1;
}

/* malloc: general purpose storage allocator */
void *malloc(unsigned nbytes)
{
    Header *currp, *prevp;
    unsigned nunits;

    /* error checking */
    if (nbytes == 0)
        return NULL;

    nunits = ceil_div(nbytes, sizeof(Header)) + 1;
    if ((prevp = freep) == NULL) {              /* no free list yet */
        base.s.next = freep = prevp = &base;    /* make base point to itself */
        base.s.size = 0;
    }
    /* step through the list for a large enough block */
    for (currp = prevp->s.next; ; prevp = currp, currp = currp->s.next) {
        if (currp->s.size >= nunits) {      /* big enough */
            if (currp->s.size == nunits)    /* exact size */
                prevp->s.next = currp->s.next;  /* remove from list */
            else {              /* allocate tail end */
                currp->s.size -= nunits;
                currp += currp->s.size;
                currp->s.size = nunits;
            }
            freep = prevp;
            return (void *)(currp+1); /* + 1 to move past the header */
        }
        if (currp == freep)     /* wrapped around free list */
            if ((currp = morecore(nunits)) == NULL)
                return NULL;    /* none left */
    }
}

#define NALLOC 1024     /* minimum units that can be requested */

/* morecore: ask system for more memory */
Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)  /* no space at all */
        return NULL;
    up = (Header *) cp;     /* initialize header of new block */
    up->s.size = nu;
    free((void *)(up+1));
    return freep;
}

/* free: put block ap in free list */
void free(void *ap)
{
    Header *bp, *p;

    if (ap == NULL) {
        puts("free: invalid pointer");
        return;
    }
    bp = (Header *)ap - 1;  /* point to block header */
    if (bp->s.size <= 0) {
        puts("free: invalid block size");
        return;
    }
    for (p = freep; !(bp > p && bp < p->s.next); p = p->s.next) /* search for block */
        if (p >= p->s.next && (bp > p || bp < p->s.next))       /* block is at far left or far right of list */
            break;
    if (bp + bp->s.size == p->s.next) {     /* block is adjacent to next block */
        bp->s.size += p->s.next->s.size;    /* increase size and adjust bp's next */
        bp->s.next = p->s.next->s.next;
    } else
        bp->s.next = p->s.next;
    if (p + p->s.size == bp) {              /* block is adjacent to current block */
        p->s.size += bp->s.size;
        p->s.next = bp->s.next;
    } else
        p->s.next = bp;
    freep = p;  /* start at block p next time */
}

/* calloc: allocate memory and initialize it to zero */
void *calloc(unsigned nmembs, unsigned membsize)
{
    void *block;
    char *p, *block_end;

    if (block = malloc(nmembs * membsize), block == NULL)
        return NULL;
    /* initialize the new block */
    block_end = (char *) block + nmembs * membsize;
    for (p = (char *) block; p < block_end; p++)
        *p = 0;
    return block;
}

/* bfree: put block p of nmembs elements into free list */
void bfree(void *p, unsigned nmembs, unsigned membsize)
{
    Header *hp;
    unsigned size;

    if (p == NULL) {
        puts("bfree: invalid pointer");
        return;
    }
    /*
     * a static or external array has the problem that it wasn't allocated by mmalloc(),
     * so it doesn't have a header. we must create one.
     */
    hp = p;
    hp->s.next = NULL;
    hp->s.size = nmembs * membsize; /* contains header too */
    /*
     * to make everything work with mfree(), we need to pass a pointer to the free size
     * (and NOT the header)
     */
    free(hp + 1);
}

/* test: allocate array and fill and print it */
int main(void)
{
    int *arr = calloc(32, sizeof(int));
    for (int i = 16; i < 32; i++)
        arr[i] = i*i;
    for (int i = 0; i < 32; i++)
        printf("%d\n", arr[i]);
    free(arr);
    return 0;
}

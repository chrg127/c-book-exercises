#undef NULL

#define NULL     ((void *)0)
#define EOF      (-1)
#define BUFSIZ   1024
#define OPEN_MAX 20 /* max #files open at once */

typedef struct _iobuf {
    int cnt;        /* characters left */
    char *ncpos;    /* next character position */
    char *base;     /* location of buffer */
    int read  : 1;  /* file open for reading */
    int write : 1;  /* file open for writing */
    int unbuf : 1;  /* file is unbuffered */
    int eof   : 1;  /* EOF has occurred on this file */
    int err   : 1;  /* error occurred on this file */
    int fd;         /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 ? (unsigned char) *(p)->ncpos++ \
                                     : _fillbuf(p))
#define putc(x, p)  (--(p)->cnt >= 0 || (x) == '\n' ? *(p)->ncpos++ = (x) \
                                                    : _flushbuf((x),p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "stdio.h"

#define PERMS 0666 /* RW for owner, group and other */

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ|_WRITE)) == 0)
            break;  /* found free slot */
    if (fp >= _iob + OPEN_MAX)  /* no free slot */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd == open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else  /* mode = 'r' */
        fd = open(name, O_RDONLY, 0);

    if (fd == -1)   /* couldn't access name */
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;

    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ|_EOF|_ERR)) != _READ)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)   /* no buffer yet */
        if ((fp->base = malloc(bufsize)) == NULL)
            return EOF;     /* can't get buffer */

    fp->ncpos = fp->base;
    fp->cnt = read(fp->fd, fp->ncpos, bufsize);
    if (--fp->cnt < 0) {
        fp->flag |= fp->cnt == -1 ? _EOF : _ERR;
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ncpos++;
}

FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ,  0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE|_UNBUF, 2 },
};

int _flushbuf(int c, FILE *fp)
{
    int bufsize, ret;

    if ((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base != NULL) {
        ret = write(fp->fd, fp->base, fp->ncpos - fp->base);
        if (ret != fp->ncpos - fp->base) {
            fp->flag |= ret == -1 ? _EOF : _ERR;
            fp->cnt = 0;
            return EOF;
        }
    } else
        if (fp->base = malloc(bufsize), fp->base == NULL)
            return EOF;
    fp->cnt = bufsize - 1;
    fp->ncpos = fp->base;
    *fp->ncpos++ = c;
    return 0;
}

/* fflush: flush buffer's contents to file */
int fflush(FILE *fp)
{
    if ((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
        return EOF;
    _flushbuf(EOF, fp);
    if (fp->flag & _ERR)
        return EOF;
    return 0;
}

int fclose(FILE *fp)
{
    int ret;

    if (fp == NULL)
        return EOF;
    fflush(fp);
    fp->cnt = 0;
    fp->ncpos = NULL;
    if (fp->base != NULL)
        free(fp->base);
    fp->flag = 0;
    ret = close(fp->fd);
    fp->fd = -1;
    return ret;
}

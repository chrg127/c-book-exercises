/*
 * Modify the fsize program to print the other information
 * contained in the inode entry.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>      /* flags for read and write */
#include <sys/types.h>  /* typedefs */
#include <sys/stat.h>   /* structure returned by stat */
#include "dirent.h"     /* opendir, readdir and closedir */

#define MAXPATH 1024

void fsize(char *name);
void dirwalk(char *dirname, void (*fcn)(char *));

/* print file sizes */
int main(int argc, char **argv)
{
    printf("size name\n");
    if (argc == 1)      /* default: current directory */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

/* fsize: print size of file "name" */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {  /* get file information and do a small error check */
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)    /* check if it's a directory */
        dirwalk(name, fsize);                   /* walk into directory */

    printf("filename %s\n",         name);
    printf("    device id %-ld\n",        stbuf.st_dev);
    printf("    inode %-ld\n",            stbuf.st_ino);
    printf("    mode %-d\n",              stbuf.st_mode);
    printf("    hard links %-ld\n",       stbuf.st_nlink);
    printf("    owner id %-d\n",          stbuf.st_uid);
    printf("    group id %-d\n",          stbuf.st_gid);
    printf("    device id %-ld\n",        stbuf.st_rdev);
    printf("    size %-ld\n",             stbuf.st_size);
    printf("    block size %-ld\n",       stbuf.st_blksize);
    printf("    blocks allocated %-ld\n", stbuf.st_blocks);
}

/* dirwalk: apply func to all files in dir */
void dirwalk(char *dirname, void (*func)(char *))
{
    char name[MAXPATH];
    DIR *dfd;
    Dirent *dp;

    if ((dfd = opendir(dirname)) == NULL) { /* open dir and do error checking */
        fprintf(stderr, "dirwalk: can't open %s\n", dirname);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {   /* read the directory */
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
            continue;   /* skip self and parent */
        if (strlen(dirname)+strlen(dp->name)+2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dirname, dp->name);
        else {      /* copy name of dir + file name to name string (declared above) */
            sprintf(name, "%s/%s", dirname, dp->name);
            (*func)(name);   /* apply fcn to name */
        }
    }

    closedir(dfd);
}

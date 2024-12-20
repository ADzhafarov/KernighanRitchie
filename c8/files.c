#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef  NULL
    #undef NULL
#endif

#define NULL        0
#define EOF         (-1)
#define BUFSIZ      10
#define OPEN_MAX    20

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;


#define stdin   (&_iob[0])
#define stdout   (&_iob[1])
#define stderr   (&_iob[2])

enum _flags {
    _READ   = 01,
    _WRITE  = 02,
    _UNBUF  = 04,
    _EOF    = 010,
    _ERR    = 020,
};

FILE _iob[OPEN_MAX] = {
    {0, (char *) 0, (char *) 0, _READ, 0},
    {0, (char *) 0, (char *) 0, _WRITE, 1}, // buffered version
    /*{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 1},  // unbuffered version*/
    {0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2},
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     ((p)->flag & _EOF) != 0)
#define ferror(p)   ((p)->flag & _ERROR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 \
    ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)     (--(p)->cnt >= 0 \
                     ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)


#define PERMS   0666

FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'r' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;                              /* found free slot */
    if (fp >= _iob + OPEN_MAX)
        return NULL;                            /* no free slot */

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode = 'r') ? _READ : _WRITE;
    return fp;
}

int _fillbuf(FILE *fp) {
    int bufsize;

    if ((fp->flag&(_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int x, FILE *fp) {

    char *p = fp->base;
    int res, bufsize;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ + 1;
    if (fp->base == NULL) {
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return -1;
        fp->ptr = fp->base;
        if (fp->flag & _UNBUF)
            fp->cnt = 0;
        else {
            fp->cnt = BUFSIZ;
            *fp->ptr++ = x;
            return 1; // for a new buffer we don't flush it immediately
        }
    }


    if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {
        return -1;
    }

    if (x >= 0)
        *fp->ptr++ = x;
    res = write(fp->fd, fp->base, fp->ptr - fp->base);
    // todo save x to new empty buf
    if (fp->flag & _UNBUF)
        fp->cnt = 0;
    else
        fp->cnt = BUFSIZ;
    fp->ptr = fp->base;
    return res;
}

#define fflush(fp)      _flushbuf(-1, (fp))

void fclose(FILE *fp) {
    fflush(fp);
    free(fp->base);
}

int main(void) {
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
}
















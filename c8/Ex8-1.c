#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void filecopy(int f, int t);

#define STDIN   0
#define STDOUT  1
#define STDERR  2

int main(int argc, char *argv[]) {

    char *prog = *argv;
    int fd;

    if (argc == 1) {
        filecopy(STDIN, STDOUT);
        exit(0);
    }

    while (--argc > 0) {
        if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
            fprintf(stderr, "%s can't open %s\n", prog, *argv);
            exit(1);
        } else {
            filecopy(fd, STDOUT);
            close(fd);
        }
    }

    exit(0);
}


void filecopy(int f, int t) {
    char buf[BUFSIZ];
    int n;

    while ((n = read(f, buf, BUFSIZ)) > 0)
        write(t, buf, n);
}

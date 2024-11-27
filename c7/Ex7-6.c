#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE     1000

int main(int argc, char *argv[]) {
    FILE *p1, *p2;
    char line1[MAXLINE], line2[MAXLINE];
    char *prog = argv[0];

    if (argc != 3) {
        fprintf(stderr, "Usage: compare file1 file2");
        exit(1);
    }

    if ((p1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: can't open file %s\n", prog, argv[1]);
        exit(2);
    }

    if ((p2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "%s: can't open file %s\n", prog, argv[1]);
        exit(2);
    }

    int line_num = 1;
    char *res1, *res2;
    for (res1 = fgets(line1, MAXLINE, p1), res2 = fgets(line2, MAXLINE, p2); res1 != NULL && res2 != NULL; res1 = fgets(line1, MAXLINE, p1), res2 = fgets(line2, MAXLINE, p2)) {
        if (strcmp(line1, line2) != 0) {
            printf("Line %d:\n%20s\t%s%20s\t%s", line_num, argv[1], line1, argv[2], line2);
            exit(0);
        }
        line_num++;
    }

    if (res1 == NULL && res2 == NULL) {
        printf("Files match!\n");
        exit(0);
    }
    
    if (res1 == NULL) {
        printf("%s exceeded before %s\n", argv[1], argv[2]);
        printf("Line %d:\t%s", line_num, line2);
        exit(0);
    }

    if (res2 == NULL) {
        printf("%s exceeded before %s\n", argv[2], argv[1]);
        printf("Line %d:\t%s", line_num, line1);
        exit(0);
    }
}

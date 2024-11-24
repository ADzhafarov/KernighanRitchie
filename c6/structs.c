#include <math.h>
#include <stdio.h>

struct point {
    int x;
    int y;
};

struct rect {
    struct point p1;
    struct point p2;
};

int main(void) {
    struct rect r, *rp = &r;

    struct {
        int len;
        char *str;
    } *p;

    printf("%d\n", r.p1.x);
    printf("%d\n", rp->p1.x);
    printf("%d\n", (r.p1).x);
    printf("%d\n", (rp->p1).x);
}

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>


int printMandelbrot(int n) {
    printf("%d", n);

    int gd = DETECT, gm;
    int x = 320, y = 240, radius;

    initgraph(&gd, &gm, "/home/tucna/Plocha");

    for (radius = 25; radius <= 124; radius += 20) {
        circle(x, y, radius);
    }
    getch();

    closegraph();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>


// Defining the size of the screen.
#define Y 1080
#define X 1920
#define MAXCOUNT 30;

void callMandelbrot() {
    int x, y, i, j;
    int max_x, max_y, counter;
    double size_x, size_y;
    
    // getting size of screen (max_x X max_y)
    max_x, max_y = getmaxx(), getmaxy();

    // simple counting the center of the screen [...]
    // [...] to place there image
    //size_x = 
    
    rectangle(0, 0, max_x, max_y);

    for (y = 1; y <= max_y - 1; y ++) {
        for (x = 1; x <= max_x - 1; x++) {
            putpixel(x, y, x+y);
        }
    }
}

int printMandelbrot() {

    int gd = DETECT, gm, errorcode;
    int x = 320, y = 240, radius;

    printf("%d, %d", &gd, &gm);

    initgraph(&gd, &gm, "");
    callMandelbrot();


    getch();

    closegraph();
    return 0;
}

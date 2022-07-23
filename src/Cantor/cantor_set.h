#include <stdio.h>
#include <math.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define STRIPE_HEIGHT 13

// check if pixel is in set - for ASCII + stb
int isInCantor(int x, int width, int it) {
    int is_inside = 1; // true
    int div = x;

    for (int j = 0; j < it; j++) {
        int math = (3*div >= width) && (3*div < 2*width);
        is_inside = is_inside && !math;

        div = (3*div) % width;
    }
    return is_inside;
}


// main ASCII function 
void printCantor(int iter) {
    for (int n = 0; n < iter; n++) {
        struct winsize wnsz;
        ioctl(0, TIOCGWINSZ, &wnsz);

        int width = (wnsz.ws_col); // get the window width

        for (int i = 0; i < width; i++) {
            if (isInCantor(i, width, n)) {
                printf("_");
            } else {
                printf(" ");
            }
        }printf("\n");
    }
}


// main stb function - rendering carpet into image
void renderCantor(int width, int iter, int color) {
    int r, g, b, height, n, it, isC;

    height = STRIPE_HEIGHT * (2*iter - 1);
    n = 0; it = 0;

    // allocating memory
    size_t check = width * height * 3;
    unsigned char *data = calloc(check, sizeof *data);

    for (int y = 0; y < height; y++) {
        if (y == (it+1)*STRIPE_HEIGHT) { it++; }

        if (color == 1) { r=rand()%255; g=rand()%255; b=rand()%255;} // color stripes
        else { r = g = b = 255; } // white

        for (int x = 0; x < width; x++) {
            int iter;

            if (it == 0) { iter = 0; }
            else { iter = (it/2)+1; }
            
            isC = isInCantor(x, width, iter);

            if ((it % 2 == 0) && isC) {
                data[n++] = (unsigned char)r;
                data[n++] = (unsigned char)g;
                data[n++] = (unsigned char)b;
            } else {
                data[n++] = (unsigned char)0;
                data[n++] = (unsigned char)0;
                data[n++] = (unsigned char)0;
            }
        }
    }
    printf("\%d\n", n);

    stbi_write_png("cantor_set_stb.png", width, height, 3, data, width*3);
    printf("Done!\n");

}

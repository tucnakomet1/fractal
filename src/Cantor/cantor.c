#include <stdio.h>
#include <math.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define STRIPE_HEIGHT 13

void plotPoint(unsigned char* image, int width, int x, int y, int color) {
    int r, g, b;
    if (color == 1) { r=rand()%250; g= 255 - rand()%150; b=rand()%150;} // color stripes
    else { r = g = b = 255; }                                    // white

    image[(y * width + x)*3] = r;
    image[(y * width + x)*3 + 1] = g;
    image[(y * width + x)*3 + 2] = b;

}

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

int countCantor(unsigned char* image, int width, int height, int color) {
    int r, g, b, isC;
    int n = 0, it = 0;

    for (int y = 0; y < height; y++) {
        if (y == (it+1)*STRIPE_HEIGHT) { it++; }

        for (int x = 0; x < width; x++) {
            int iter;

            if (it == 0) { iter = 0; }
            else { iter = (it/2)+1; }
            
            isC = isInCantor(x, width, iter);

            if ((it % 2 == 0) && isC) {
                plotPoint(image, width, x, y, color);
            }
        }
            
    }

}


// main stb function - rendering carpet into image
void renderCantor(int width, int iter, int color) {

    int height = STRIPE_HEIGHT * (2*iter - 1);

    // allocating memory
    unsigned char image[width * height * 3];

    // make whole image black (0 = black)
    for (int i = 0; i < width * height * 3; i++) image[i] = 0;

    // count cantor set points and plot them into image
    countCantor(image, width, height, color);

    // save image into png format
    if (stbi_write_png("cantor_set.png", width, height, 3, image, width * 3) == 0) {
        printf("Error: saving image\n");
    }

}

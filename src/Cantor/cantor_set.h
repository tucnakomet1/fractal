#include <stdio.h>
#include <math.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define STRIPE_HEIGHT 16
int now_iter = 1;
// check if x, y is in carpet - for ASCII

// main ASCII function 
void printCantor(int iter) {
    int size;
}

/* stb */

// check if pixel is in carepet - for stb
int isInCantor(int x, int y, int n, int now_iter) {
    if (y < now_iter*STRIPE_HEIGHT) {
        //printf("%d, %d, %d, %d \n", x, y, n, now_iter); 
        return 1;
    } else {
        if (y < ((now_iter+1)*STRIPE_HEIGHT)) {
            return 0;
        } else {
            //printf("YES, %d\n", now_iter);
            now_iter = now_iter + 1;
        }
    }return 0;
}

// main stb function - rendering carpet into image
void renderCantor(int width, int height, int iter, int color) {
    int r, g, b;
    
    iter = 4;
    color = 1;

    height = STRIPE_HEIGHT * (2*iter - 1);

    printf("%d", height);

    // allocating memory
    size_t check = width * height * 3;
    unsigned char *data = calloc(check, sizeof *data);
    int n = 0;
    int it = 0;

    if (!*data) { printf("\nRendering!\n"); }

    for (int y = 0; y < height; y++) {
        if (y == (it+1)*STRIPE_HEIGHT) { it++; }

        if (color == 1) { r=rand()%255; g=rand()%255; b=rand()%255;} // color stripes
        else { r = g = b = 255; } // white

        double new_width = (double)width/ (double)pow(it, 3);
        printf("%d, %d, %d, %d, %f\n", height, y, it, width, new_width);
        for (int x = 0; x < width; x++) {

            int isC = isInCantor(x, y, iter, it);

            if (it % 2 == 0) {
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
    printf("\%d", n);

    stbi_write_png("sierpinski_carpet_stb.png", width, height, 3, data, width*3);
    printf("Done!");

}

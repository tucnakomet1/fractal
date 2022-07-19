#include <stdio.h>
#include <math.h>
#include <sys/ioctl.h>
#include <stdlib.h>

// check if x, y is in carpet - for ASCII
int isInCarpetA(int x, int y) {
    while(1) {
        if ((x == 0) || (y == 0)) {
            return 0;
        } else if ((x % 3 == 1) && (y % 3 == 1)) {
            // if mod is 1
            return 1;
        }
    
        x = x/3;
        y = y/3;    
    }
}

// main ASCII function 
void printCarpet(int iter) {
    int size;

    size = (int)pow(3, iter);
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (isInCarpetA(x, y) == 0) { printf("MM"); }
            else { printf("  "); }
        }
        printf("\n");
    }
}

/* stb */
// check if input resolution is square sized - for stb
int checkSRatio(int w, int h) {
    if (w == h) { return 0; } 
    else {
        if (w > h) { return w; }
        else { return h; }
    }
}

// check if pixel is in carepet - for stb
int isInCarpet(double x, double y, int n) {
    double factor = 1.0;
    int isIn = 0;

    for (int i = 0; i < n; i++) {
        if ((floor(fmod(x*factor, 3)) == 1) && (floor(fmod(y*factor, 3)) == 1)) {
            isIn = 1;
            break;
        }
        factor *= 3;
    }
    return isIn;
}

// main stb function - rendering carpet into image
void renderCarpet(int width, int height, int iter, int color) {
    int r, g, b;

    int sratio = checkSRatio(width, height);
    if (sratio > 0) { width = sratio; height = sratio; }

    // allocating memory
    size_t check = width * height * 3;
    unsigned char *data = calloc(check, sizeof *data);
    int n = 0;

    if (!*data) { printf("\nRendering!\n"); }

    for (int y = 0; y < height; y++) {
        if (color == 1) { r=rand()%255; g=rand()%255; b=rand()%255;} // color stripes
        else { r = g = b = 255; } // white

        for (int x = 0; x < width; x++) {
            int isC = isInCarpet((double)x/(double)width*3.0, (double)y/(double)height*3.0, iter);

            if (isC) {
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

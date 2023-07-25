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

void plotCarpet(unsigned char* image, int x, int y, int width, int color) {
    int r, g, b;
    if (color == 1) { r=rand()%240; g=rand()%250; b=rand()%230;} // color stripes
    else { r = g = b = 255; } // white
    
    image[(y * width + x)*3] = r;
    image[(y * width + x)*3 + 1] = g;
    image[(y * width + x)*3 + 2] = b;

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

void countCarpet(unsigned char* image, int width, int height, int iter, int color) {
    int n = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int isC = isInCarpet(
                    (double)x/(double)width*3.0,
                    (double)y/(double)height*3.0, 
                    iter);

            if (isC) plotCarpet(image, x, y, width, color);
        }
    }

}

// main stb function - rendering carpet into image
void renderCarpet(int width, int iter, int color) {
    int height = width;

    // allocating memory
    unsigned char image[width * height * 3];

    // make whole image black (0 = black)
    for (int i = 0; i < width * height *3; i++)
        image[i] = 0;
    
    // count the carpet points and plot them into image
    countCarpet(image, width, height, iter, color);

    // save the image into png format
    if (stbi_write_png("sierpinski_carpet_stb.png", width, height, 3, image, width*3) == 0) {
        printf("Error: saving image");
    }
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* *************************************************
 * Recursive function: x_{n+1} = k * x_n * (1 - x_n)
 * *************************************************/

#define startPointK 0.0
#define endPointK 4
#define color 129

int iterDiv;
int r = 255, g = color, b = color+1, rgb = 0;

// rainbow color
void giveColor(int iter) {
    int max_value = 6*color;
    int value = (iter - 1) * (max_value) / (iterDiv - 1);

    printf("R: %d, G: %d, B: %d --- RGB: %d --> i: %d \n", r, g, b, rgb, iter);
    if ((r==255 && g==b) || (r==b && g==color ) || (r == g && b == 255) ||
            (r == color && g == b) || (r == b && g == 255) || (r == g && b == color)){
        rgb = (rgb + 1) % 6;
    }

    if (rgb == 0) b++;
    else if (rgb == 1) r--;
    else if (rgb == 2) g++;
    else if (rgb == 3) b--;
    else if (rgb == 4) r++;
    else g--;
}

void plotBifurcationPoint(unsigned char* image, int x, int y, int width) {
    image[(y * width + x)*3] = r;
    image[(y * width + x)*3 + 1] = g;
    image[(y * width + x)*3 + 2] = b;
}

void countBif(unsigned char* image, int width, int height, int numIter) {

    for (int x = 0; x < width; x++) {                                              // in each column of the image is a point
        double k = startPointK + (endPointK - startPointK) * x / (width - 1);      // mapping the axis length to the image width
        giveColor(x);

        double X = 0.785;                                                          // start point in interval (0,1)
        for (int i = 0; i < numIter; i++) {
            X = k * X * (1 - X);
            
            if (i > numIter / 2) {                                                  // stabilizes after numIter/2
                int y = (int)(height * X);
                if ((y >= 0) && (y < height)) plotBifurcationPoint(image, x, y, width);
            }
        }
    }
}


void renderBifurcation(int width, int height, int iterations) {
    iterDiv = width;

    // allocating memory
    unsigned char* image = (unsigned char*)malloc(width * height * 3);
    
    // make whole image black (0 = black)
    for (int i = 0; i < width * height * 3; i++)
        image[i] = 0;
    
    // count the lorenz points and plot them into image
    countBif(image, width, height, iterations);

    
    // save the image into png format
    if (stbi_write_png("bifurcation_diagram.png", width, height, 3, image, width*3) == 0) {
        printf("Error: saving image\n");
    }
    free(image);
}

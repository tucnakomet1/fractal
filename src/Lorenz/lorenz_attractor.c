#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* ************************************************************
 * for sigma, rho, beta > 0 is the lorenz equation:
 *    
 * dx/dt = sigma * (y - x)  --> (in our case) where sigma = 10
 * dy/dt = x * (rho-z) - y  --> (in our case) where rho = 28
 * dz/dt = x*y - beta*z     --> (in our case) where beta = 8/3
 * ***********************************************************/

#define sigma 10
#define rho 28
#define beta 8.0/3.0
#define dt 0.01
#define scale 18

#define iterationCount 60000

void plotThePoint(unsigned char* image, int x, int y, int width, int n) {
    image[(y * width + x)*3] = (int) n / 205;
    image[(y * width + x)*3 + 1] = 255 - (int) n/105;
    image[(y * width + x)*3 + 2] = (int)n/55;
}

void countLorenz(unsigned char* image, int width, int height) {
    double x = 0.1,y = 0, z = 0;

    int midX = width/2;
    int midH = height/2;

    for (int n = 0; n < iterationCount; n++) {
        double dx = (sigma * (y - x)) * dt;
        double dy = (x * (rho - z) - y) * dt;
        double dz = (x * y - beta * z) * dt;

        x+= dx; y += dy; z += dz;

        plotThePoint(image, x*scale + midX, y*scale + midH, width, n);
    }
}


void renderLorenz(int width, int height) {
    // allocating memory
    unsigned char image[width * height * 3];

    // make whole image black (0 = black)
    for (int i = 0; i < width * height *3; i++)
        image[i] = 0;

    
    // count the lorenz points and plot them into image
    countLorenz(image, width, height);

    // save the image into png format
    if (stbi_write_png("lorenz_attractor.png", width, height, 3, image, width*3) == 0) {
        printf("Error: saving image\n");
    }
}

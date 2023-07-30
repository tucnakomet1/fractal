#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../stb/stb_image_write.h"

#include "../util.c"

/* ************************************************ *
 * for sigma, rho, beta > 0 is the Lorenz equation: *
 *                                                  *
 * dx/dt = sigma * (y - x)  --> where sigma = 10    *
 * dy/dt = x * (rho-z) - y  --> where rho = 28      *
 * dz/dt = x*y - beta*z     --> where beta = 8/3    *
 * ************************************************ */

void countLorenz(unsigned char* image, int width, int height, int iterations) {
    double sigma = 10, rho = 28, beta = 8.0/3.0;
    double x = 0.1,y = 0, z = 0;
    double dt = 0.0035, scale = 18;

    int midX = width/2;
    int midH = height/2;

    for (int n = 0; n < iterations; n++) {
        double dx = (sigma * (y - x)) * dt;
        double dy = (x * (rho - z) - y) * dt;
        double dz = (x * y - beta * z) * dt;

        x+= dx; y += dy; z += dz;

        int Y = y*scale + midH;
        if (Y >= 0 && Y < height)
            plotThePoint(image, x*scale + midX, Y, width, n);
    }
}
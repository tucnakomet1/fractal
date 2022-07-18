#include <stdio.h>

// a = 10, b = 28, c = 8.0/3.0; // predefined values for chaotic system
#define sigma 10
#define rho 28
#define beta 8.0/3.0

#define lorenzLimit 1000

void renderLorenz(int width, int height) {
    // sigma = Prandtl number;
    // rho   = Rayleigh number;
    // beta  = ;
    double x = 0.01;
    double y = 0;
    double z = 0;
    double dt = 0.01;

    // allocating memory
    size_t check = width * height * 3;
    unsigned char *data = calloc(check, sizeof *data);
    int n = 0;

    if (!*data) {
        printf("Rendering!\n");
    }

    // loop, writing data
    for (int n = 0; n < lorenzLimit; n + dt) {
        // x = dx/dt  <=>  dx = x*dt
        double dx = (sigma * (y - x))*dt;   // dx/dt
        double dy = (x * (rho - z) - y)*dt; // dy/dt
        double dz = (x * y - beta * z)*dt;  // dz/dt

        x += dx;
        y += dy;
        z += dz;

        data[n++] = (unsigned char)x;
        data[n++] = (unsigned char)y;
        data[n++] = (unsigned char)z;

        printf("x: %f, y: %f, z:%f\n", x, y, z);

    }


    stbi_write_png("lorenz_atractor_rendered_image.png", width, height, 3, data, width*3);

}



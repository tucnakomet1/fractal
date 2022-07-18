#include <stdio.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image.h"
#include "../stb/stb_image_write.h"

#define WIDTH 1920
#define HEIGHT 1080
#define P_COUNT 3000

typedef struct particle {
    double x, y, z;
    int    r, g, b;
}particle;

particle rotateByMatrix(int *mat4[], particle p) {
    
}

int main(int argc, int* argv[]) {
    int quit = 0;

    // list of particles in simulation
    particle *particles = malloc(sizeof(particle) * P_COUNT);
    for (int i = 0; i < P_COUNT; i++) {
        particles[i].x = 0.001 * i;
        particles[i].y = 0;
        particles[i].z = 0;

        particles[i].r = 100 * i + 40;
        particles[i].g = 45 * i + 45;
        particles[i].b = 200 * i + 50;
    }

    // Lorenz equations variable initialization
    // https://en.wikipedia.org/wiki/Lorenz_system

    double rho   = 28.0;
    double sigma = 10.0;
    double beta  = 8.0/3.0;  
    double dt = 0.01;

    float theta = 0;

    int step = 1, scale = 10;

    while(!quit) {

        // if not paused, run over each particle in the array, and update it's position
        if (step) {
            for (int i = 0; i < P_COUNT; i++) {
                double dx = (sigma * (particles[i].y - particles[i].x)) * dt;
                double dy = (particles[i].x * (rho - particles[i].z) - particles[i].y) * dt;
                double dz = (particles[i].x*particles[i].y - beta*particles[i].z) * dt;

                particles[i].x += dx;
                particles[i].y += dy;
                particles[i].z += dz;
            }
        }


        /*for (int i = 0; i < P_COUNT; i++) {

            // render each particle with it's own rgb value at it's x and y value, in the middle of the renderer
            SDL_SetRenderDrawColor(renderer, particles[i].r, particles[i].g, particles[i].b, 255);
            SDL_RenderDrawPointF(renderer, particles[i].x*scale + WIDTH/2, particles[i].y*scale + HEIGHT/2);
        } */
    }
    stbi_write_jpg("lorenz_rendered_image.jpg", WIDTH, HEIGHT, 3, particles, 100);

    // free memory allocated
    free(particles);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <complex.h>
#include <stdbool.h>
#include "hsv_to_rgb.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image.h"
#include "../stb/stb_image_write.h"

#define ASCII2 "M@#W$BG5E20Tbca?1!;:+=-,._` "
#define ASCII " `_.,-=+:;!1?acbT02E5GB$W#@M"

#define ANSI_f_start "\x1b[38;2;"
#define ANSI_end "\x1b[0m"

#define LIMIT 80
#define START -2.0
#define START2 -1.0
#define END 1.0

int width, height, zoom = 1;
bool color = false;

double complex Cpow(double complex z);
double complex Cadd(double complex z, double complex c);
void getResolution();
int calculateMandel(double complex c);
void callMandelbrot();
int printMandelbrot(bool clr);


// powering complex numbers
double complex Cpow(double complex z) {
    double real, imag;
    double a = creal(z), b=cimag(z);

    // a = a^2 - b^2
    real = pow(a, 2) - pow(b, 2);

    // b = 2*a*b
    imag = 2*a*b;

    return CMPLX(real, imag);
}


// summing complex numbers
double complex Cadd(double complex z, double complex c) {
    double realAdd, imagAdd;

    realAdd = creal(z) + creal(c);
    imagAdd = cimag(z) + cimag(c);

    return CMPLX(realAdd, imagAdd);
}


// get resolution of terminal
void getResolution() {
    struct winsize wnsz;
    ioctl(0, TIOCGWINSZ, &wnsz);

    width = (wnsz.ws_row);
    height = (wnsz.ws_col);

    printf("%d x %d \n", width, height);
}


// calculate mandel
int calculateMandel(double complex c) {
    double complex zz, z = 0.0;
    int n = 0;

    // |z| <= 2;  Hausdorff measure = 2
    while ((cabs(z) <= 2) && (n < LIMIT)) {
        // zz = z^2
        // z = z^2 + c <=> z = zz + c
        zz = Cpow(z);
        z = Cadd(zz, c);
        
        n++;
    }
    return n;
}


// calculating and printing mandelbrot
void callMandelbrot() {
    getResolution();

    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {
            // a... real number; 
            // b... imaginary number
            double a = START + ((double) x / height) * (END - START);
            double b = START2 + ((double) y / width) * (END - START2);

            // c = a + bi; 
            double complex c = CMPLX(a, b);

            int m = calculateMandel(c);

            if (m >= LIMIT) { printf(" "); } 
            else { 
                int H, S, V, r, g, b;

                H = (255 * m) / LIMIT;
                S = 100;
                V = 100;

                r = hsv_to_rgb(H, S, V, 0);
                g = hsv_to_rgb(H, S, V, 1);
                b = hsv_to_rgb(H, S, V, 2);


                if (color) {
                    printf("%s%d;%d;%dm%c%s", ANSI_f_start, r, g, b, ASCII2[(m) % strlen(ASCII2)], ANSI_end);
                } else {
                    printf("%c", ASCII[(m) % strlen(ASCII)]);
                }
            }
        } 
        printf("\r\n");
    }
}


// main function for ascii --> is called by fractal.c function
int printMandelbrot(bool clr) {
    color = clr;
    callMandelbrot();
    return 0;
}



/* ------------------------- */
/* mandelbrot image renderer */
/* ------------------------- */


// check if input width and height is in correct ratio
int checkRatio(int w, int h) {
    double rat = (double)3/2;
    double div = (double)w/h;

    if (div != rat) {
        printf("Entered width:height is not in the correct ratio 3:2\n");
        int new_h = (2*w)/3;
        printf("Edited from %dx%d to %dx%d...\n", w, h, w, new_h);
        return new_h;
    } else {
        return 0;
    }
}


// main function for rendering --> is called by fractal.c function
int renderMandelbrot(int width, int height, int format_, int color) {
    // check for correct ratio
    int rat = checkRatio(width, height);
    if (rat > 0) { height = rat; }
    
    // allocating memory
    size_t check = width * height * 3;
    unsigned char *data = calloc(check, sizeof *data);
    int n = 0;

    if (!*data) {
        printf("Rendering!\n");
    }


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double a = START + ((double) x / height/1.5) * (END - START);  // h/1.5 --> resolution 3:2
            double b = START2 + ((double) y / width*1.5) * (END - START2); // w*1.5 --> resolution 3:2
            double complex c = CMPLX(a, b);

            int m = calculateMandel(c);

            if (m > LIMIT) { printf(" "); }
            else {
                int H = (255 * m) / LIMIT, S = 100, V = 100;
                if (m == LIMIT) { V = 0; }

                int r = hsv_to_rgb(H, S, V, 0), g = hsv_to_rgb(H, S, V, 1), b = hsv_to_rgb(H, S, V, 2);

                if (color == 0) {
                    // normal color
                
                    data[n++] = (unsigned char)r;
                    data[n++] = (unsigned char)g;
                    data[n++] = (unsigned char)b;

                } else if (color == 1) {
                    // grey filter
                
                    int grey = 0.299*r + 0.587*g + 0.114*b;
                    
                    data[n++] = (unsigned char)grey;
                    data[n++] = (unsigned char)grey;
                    data[n++] = (unsigned char)grey;

                } else if (color == 2) {
                    // sepia filter 
                
                    int sr, sg, sb;

                    sr = 0.393*r + 0.769*g + 0.189*b;
                    sg = 0.349*r + 0.686*g + 0.168*b;
                    sb = 0.272*r + 0.534*g + 0.131*b;

                    if (sr > 255) { sr = 255; }
                    else if (sg > 255) { sg = 255; }
                    else if (sb > 255) { sb = 255; }

                    data[n++] = (unsigned char)sr;
                    data[n++] = (unsigned char)sg;
                    data[n++] = (unsigned char)sb;
                
                }
            }
        }
    }
    if (format_ == 0) {
        // rendering png
        stbi_write_png("png_test.png", width, height, 3, data, width*3);
    } else {
        // rendering jpg
        stbi_write_jpg("jpg_test.jpg", width, height, 3, data, 100);
    }

    return 0;
}




/* -------------- */
/* mandelbrot GUI */
/* -------------- */
#include <SDL.h>
#include <SDL2/SDL.h>


// exit function for SDL
void exitSDL(SDL_Window *win, SDL_Surface *win_surface) {
    SDL_FreeSurface(win_surface);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(0);
}

// drawing mandelbrot using sdl
void drawMandelbrot(SDL_Window *win, SDL_Surface *win_surface, int locX, int locY, int zoom) {
    width = 1500;
    height = 1000;

    static SDL_Rect rect;

    printf("Center: %d x %d\n", locX, locY);

    // mandelbrot calculation loop
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // a... real number; 
            // b... imaginary number
            double a = START + (((double) x / height/1.5)/zoom) * (END - START);
            double b = START2 + (((double) y / width*1.5)/zoom) * (END - START2);

            // c = a + bi; 
            double complex c = CMPLX(a, b);

            int m = calculateMandel(c);

            int H, S, V, R, G, B;
            if (m < LIMIT) { 
                H = (255 * m) / LIMIT;
                S = 100;
                V = 100;

                R = hsv_to_rgb(H, S, V, 0);
                G = hsv_to_rgb(H, S, V, 1);
                B = hsv_to_rgb(H, S, V, 2);

                ((Uint32*)win_surface->pixels)[(y * win_surface->w) + x] = (m >= LIMIT)? 0 :
                    SDL_MapRGB(win_surface->format, R, G, B);
            } else {
                ((Uint32*)win_surface->pixels)[(y * win_surface->w) + x] = (m >= LIMIT)? 0 :
                    SDL_MapRGB(win_surface->format, 0, 0, 0);
            }
        }
    }
    SDL_UpdateWindowSurface(win);
}



int showMandelbrot() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *win = SDL_CreateWindow("Mandelbrot GUI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 1000, SDL_WINDOW_SHOWN);
    if (!win) { printf("Failed to create window!\n"); return -1; }

    SDL_Surface *win_surface = SDL_GetWindowSurface(win);
    if (!win_surface) { printf("Failed to get surface from window!\n"); return -1; }

    drawMandelbrot(win, win_surface, 0, 0, 1);
    
    int new_zoom;
    SDL_Event event;
    while(1) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                // exit after click the exit button
                exitSDL(win, win_surface);
                break;
            case SDL_KEYDOWN:
                // zoom in & out using arrows
                exitSDL(win, win_surface);
                break;
            case SDL_MOUSEWHEEL:
                // zoom in & out using mouse wheel

                if (event.wheel.y > 0) {
                    // scrolling up
                    printf("Zoom %d, to zoom %d\n", zoom, zoom++);
                    
                    drawMandelbrot(win, win_surface, event.button.x, event.button.y, zoom++);

                } else if (event.wheel.y < 0) {
                    // scrolling down
                    new_zoom = zoom--;
                    if (new_zoom < 1) { new_zoom = zoom = 1; }

                    printf("Zoom %d, to zoom %d\n", zoom, new_zoom);

                    drawMandelbrot(win, win_surface, 0, 0, new_zoom);
                }
                break;
        }
    }

    return 0;
}

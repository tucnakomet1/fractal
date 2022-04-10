/* -------------- */
/* mandelbrot GUI */
/* -------------- */

#include <stdio.h>
#include <SDL.h>
#include <SDL2/SDL.h>

#define PIXEL_SCALE 200
#define WIDTH 4
#define HEIGHT 4
#define XSTART -2
#define YSTART -1.5
#define ITERATION 80


// exit function for SDL
void exitSDL(SDL_Window *win, SDL_Surface *win_surface) {
    SDL_FreeSurface(win_surface);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(0);
}


// calculating mandelbrot
int calculate_mandel(double real, double imag) {
    double a = 0, b = 0;

    for (int i = 0; i < ITERATION; i++) {
        double a2 = a*a - b*b + real;
        double b2 = 2*a*b + imag;

        a = a2, b = b2;

        if ((a*a + b*b) > 4) {
            return i+1;
        }
    }
    return 0;
}


double calcXstart(double width, int xaxe) {
    double third = (double)width / 3.0;

    if ((xaxe >= 0) && (xaxe <= third)) {
        // <-2; -1>
        double divider = third / xaxe;
        double res = -2.0 / divider;
        return res;
    } else if ((xaxe > third) && (xaxe <= third*2 )) {
        // <-1; 0>
        double divider = (third*2) / xaxe;
        double res = -1.0 / divider;
        return res;
    } else {
        // <0; 1>
        double divider = width / xaxe;
        double res = 1.0 / divider;
        return res;

    }
}


double calcYstart(double height, int yaxe) {
    double sixth = (double)height / 6.0;

    if ((yaxe >= 0) && (yaxe <= sixth)) {
        // <-1.5; -1>
        double divider = sixth / yaxe;
        double res = -1.5 / divider;
        return res;
    } else if ((yaxe > sixth) && (yaxe <= sixth*2 )) {
        // <-1; -0.5>
        double divider = (sixth*2) / yaxe;
        double res = -1.0 / divider;
        return res;
    } else if ((yaxe > sixth*2) && (yaxe <= sixth*3 )) {
        // <-0.5; 0>
        double divider = (sixth*3) / yaxe;
        double res = -0.5 / divider;
        return res;
    } else if ((yaxe > sixth*3) && (yaxe <= sixth*4 )) {
        // <0; 0.5>
        double divider = (sixth*4) / yaxe;
        double res = 0.5 / divider;
        return res;
    } else if ((yaxe > sixth*4) && (yaxe <= sixth*5 )) {
        // <0.5; 1>
        double divider = (sixth*5) / yaxe;
        double res = 1.0 / divider;
        return res;
    } else {
        // <1, 1.5>
        double divider = (sixth*6) / yaxe;
        double res = 1.5 / divider;
        return res;
    }
}


// drawing mandelbrot using sdl
void drawMandelbrot(SDL_Window *win, SDL_Surface *win_surface, double width, double height, int pixel, double xstart, double ystart) {
    static SDL_Rect rect;

    printf("%d x %d", width, height);

    // mandelbrot calculation loop
    for (int y = 0; y < height; y++) {
        double imag = ystart + (double)y / pixel;

        for (int x = 0; x < width; x++) {
            double real = xstart + (double)x / pixel;

            int m = calculate_mandel(real, imag);

            int H, S, V, R, G, B;
            if (m < ITERATION) {
                H = (255 * m) / ITERATION;
                S = 100;
                V = 100;

                R = hsv_to_rgb(H, S, V, 0); // m % 4 * 64;
                G = hsv_to_rgb(H, S, V, 1); // m % 8 * 32;
                B = hsv_to_rgb(H, S, V, 2); // m % 16 * 16;

                ((Uint32*)win_surface->pixels)[(y * win_surface->w) + x] = (m >= ITERATION)? 0 :
                    SDL_MapRGB(win_surface->format, R, G, B);
            } else {
                ((Uint32*)win_surface->pixels)[(y * win_surface->w) + x] = (m >= ITERATION)? 0 :
                    SDL_MapRGB(win_surface->format, 0, 0, 0);
            }
        }
    }
    SDL_UpdateWindowSurface(win);
}


int mandelbrot_sdl() {
    SDL_Init(SDL_INIT_EVERYTHING);

    int width = PIXEL_SCALE * WIDTH;
    int height = PIXEL_SCALE * HEIGHT;
    int zoom = 1, new_zoom;

    printf("%d x %d\n", width, height);

    SDL_Window *win = SDL_CreateWindow("Mandelbrot GUI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!win) { printf("Failed to create window!\n"); return -1; }

    SDL_Surface *win_surface = SDL_GetWindowSurface(win);
    if (!win_surface) { printf("Failed to get surface from window!\n"); return -1; }


    drawMandelbrot(win, win_surface, width, height, PIXEL_SCALE*1.5, XSTART, YSTART);
    int pixel = PIXEL_SCALE;
    double xaxe, xaxe2, yaxe, yaxe2;

    SDL_Event event;
    while(1) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                // exit after click the exit button
                exitSDL(win, win_surface);
                break;
            case SDL_MOUSEBUTTONDOWN:
                // zoom in & out using mouse button

                if (event.button.button == SDL_BUTTON_LEFT) {
                    // scrolling up
                    //printf("LEFT! Zoom %d, to zoom %d\n", zoom, zoom+1);
                    pixel = pixel*1.2;
                    zoom++;

                    printf("X %d, Y %d\n", event.button.x, event.button.y);

                    xaxe2 = xaxe;
                    yaxe2 = yaxe;

                    double xaxe = calcXstart((double)width/(zoom*1.2), event.button.x);
                    double yaxe = calcYstart((double)height/(zoom*1.2), event.button.y);
                    
                    printf("Xaxe %.2f, Yaxe %.2f\n", xaxe+xaxe2, yaxe+yaxe2);

                    drawMandelbrot(win, win_surface, width, height, pixel, xaxe, yaxe);

                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    // scrolling down

                    new_zoom = zoom = (int)zoom-1;
                    pixel = pixel / 1.2;
                    if (new_zoom <= 1) { new_zoom = zoom = 1; }
                    if (pixel <= PIXEL_SCALE*1.5) {pixel = PIXEL_SCALE*1.5; };

                    printf("RIGHT! Zoom %d, to zoom %d\n", zoom+1, new_zoom);


                    drawMandelbrot(win, win_surface, width, height, pixel, XSTART, YSTART);
                }
                break;
        }
    }

    printf("Done!\n");

    return 0;
}


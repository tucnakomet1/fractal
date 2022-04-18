#include <stdio.h>
#include <SDL.h>
#include <SDL2/SDL.h>

#define WIDTH 1080
#define HEIGHT 720

#define REAL_START -2.5
#define REAL_END 1.0
#define IMAG_START -1
#define IMAG_END 1.0

#define ZOOM 2
#define ITERATION 80

double rs = REAL_START, re = REAL_END;
double is = IMAG_START, ie = IMAG_END;
int color_type;

// exit function for SDL
void exitSDL(SDL_Window *win, SDL_Surface *win_surface) {
    SDL_FreeSurface(win_surface);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(0);
}


// zoom calculation
void Zoom(double zoom, double x, double y) {
        // mouse click axes to the the center
	    double a = rs + (re - rs)*x / WIDTH;
	    double b = is + (ie - is)*y / HEIGHT;

		// aa --> real; bb --> imaginary
		double aa = a - (re - rs) / 2 / zoom;
		re = a + (re - rs) / 2 / zoom;
		rs = aa;

		double bb = b - (ie - is) / 2 / zoom;
		ie = b + (ie - is) / 2 / zoom;
		is = bb;
}


// drawing mandelbrot using sdl
void drawMandelbrot(SDL_Window *win, SDL_Surface *win_surface) {
    static SDL_Rect rect;

    // mandelbrot calculation loop
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // a... real number; 
            // b... imaginary number
            double a = rs + (((double) x / HEIGHT)/1.5) * (re - rs);
            double b = is + (((double) y / WIDTH)*1.5) * (ie - is);

            // c = a + bi; 
            double complex c = CMPLX(a, b);

            int m = calculateMandel(c);

            if (m < ITERATION) {
                int R, G, B;

                int H = (255 * m) / ITERATION;
                int S = 100;
                int V = 100;

                int r = hsv_to_rgb(H, S, V, 0);
                int g = hsv_to_rgb(H, S, V, 1);
                int b = hsv_to_rgb(H, S, V, 2);

                
                if (color_type == 0) {
                    // main color --> red

                    R = r;
                    G = g;
                    B = b;
                } else if (color_type == 1) {
                    // colorfull filter

                    R = m % 4 * 64;
                    G = m % 8 * 32;
                    B = m % 16 * 16;
                } else if (color_type == 2) {
                    // grey filter

                    int gray = 0.299*r + 0.587*g + 0.114*b;
                    R = G = B = gray;

                } else if (color_type == 3) {
                    // sepia filter

                    int sr, sg, sb;

                    sr = 0.393*r + 0.769*g + 0.189*b;
                    sg = 0.349*r + 0.686*g + 0.168*b;
                    sb = 0.272*r + 0.534*g + 0.131*b;

                    if (sr > 255) { sr = 255; }
                    else if (sg > 255) { sg = 255; }
                    else if (sb > 255) { sb = 255; }

                    R = sr;
                    G = sg;
                    B = sb;
                }

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


// main function, called by fractal.c
int mandelbrot_sdl(int colour) {
    color_type = colour;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *win = SDL_CreateWindow("Mandelbrot GUI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!win) { printf("Failed to create window!\n"); return -1; }

    SDL_Surface *win_surface = SDL_GetWindowSurface(win);
    if (!win_surface) { printf("Failed to get surface from window!\n"); return -1; }

    drawMandelbrot(win, win_surface);

    double zoom = ZOOM;
    int zoom2 = ZOOM;  // for zooming out

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
                    // zooming in, ledt click

                    double x = event.button.x;
                    double y = event.button.y;
                    
                    zoom2 = zoom;

                    Zoom(zoom++, x, y);
                    printf("%.0f x %.0f, %.1fx\n", x, y, zoom);
                    
                    // update session
                    drawMandelbrot(win, win_surface);

                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    // zooming out, right click

                    double x = event.button.x;
                    double y = event.button.y;

                    zoom2--;
                    zoom = (double)1.0 / (double)fabs(zoom2);

                    // set min zoom --> cannot be smaller than 1
                    if(zoom > 1.0) { 
                        zoom = zoom2 = 1.0;
                        x = WIDTH, y = HEIGHT;
                        rs = REAL_START, re = REAL_END;
                        is = IMAG_START, ie = IMAG_END;
                    } else {
                        Zoom(zoom, x, y);
                    }
                    printf("%.0f x %.0f, %.3fx\n", x, y, zoom);

                    // update session
                    drawMandelbrot(win, win_surface);
                }
                break;
        }
    }
    return 0;
}


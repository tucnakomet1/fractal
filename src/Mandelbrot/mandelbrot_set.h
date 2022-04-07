#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <complex.h>
#include <stdbool.h>
#include "hsv_to_rgb.h"

//#define ASCII2 "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "
//#define ASCII " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"

#define ASCII2 "M@#W$BG5E20Tbca?1!;:+=-,._` "
#define ASCII " `_.,-=+:;!1?acbT02E5GB$W#@M"

#define ANSI_f_start "\x1b[38;2;"
#define ANSI_end "\x1b[0m"

#define LIMIT 100
#define START -2.0
#define START2 -1.0
#define END 1.0

int width, height;

double complex Cpow(double complex z);
double complex Cadd(double complex z, double complex c);
void getResolution();
int calculateMandel(double complex c);
void callMandelbrot();
int printMandelbrot(bool clr);

bool color = false;

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

            if (m > LIMIT) { printf(" "); } 
            else { 
                int H, S, V, r, g, b;

                H = (255 * m) / LIMIT;
                S = 100;
                V = 100;

                if (m == LIMIT) { V = 0; }

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


// main function - is called by fractal.c function
int printMandelbrot(bool clr) {
    color = clr;
    callMandelbrot();
    return 0;
}



/* mandelbrot image render */
#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"


// main function
int renderMandelbrot() {
    printf("Hello world!!");
    
    //save_image(1920, 1080, 0, 255, 100);

    width = 4000;
    height = 3000;

    unsigned char data[(int)(width*2) * (int)(height*2) * 3];
    int index = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // a... real number;
            // b... imaginary number
            double a = START + ((double) x / (height/1.5)) * (END - START);
            double b = START2 + ((double) y / width*1.5) * (END - START2);

            // c = a + bi;
            double complex c = CMPLX(a, b);

            int m = calculateMandel(c);

            if (m > LIMIT) { printf(" "); }
            else {
                int H, S, V, r, g, b;

                H = (255 * m) / LIMIT;
                S = 100;
                V = 100;

                if (m == LIMIT) { V = 0; }

                r = hsv_to_rgb(H, S, V, 0);
                g = hsv_to_rgb(H, S, V, 1);
                b = hsv_to_rgb(H, S, V, 2);

                data[index++] = (unsigned char)r;
                data[index++] = (unsigned char)g;
                data[index++] = (unsigned char)b;
            }
        }
        //printf("\r\n");
    }
    stbi_write_jpg("jpg_test_.jpg", width, height, 3, data, width*3);



    return 0;
}


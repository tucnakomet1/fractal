#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <complex.h>


// Defining the size of the screen.
//#define ASCII " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
//#define ASCII2 "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. "

#define ASCII "M@#W$BG5E20Tbca?1!;:+=-,._` "
#define ASCII2 " `_.,-=+:;!1?acbT02E5GB$W#@M"

#define LIMIT 240
#define START -2.0
#define START2 -1.0
#define END 1.0

int width, height;

void callMandelbrot();
void getResolution();
double complex Cpow(double complex z);
double complex Cadd(double complex z, double complex c);


// powing complex numbers
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

    // Hausdorff measure = 2
    // |z| <= 2
    while ((cabs(z) <= 2) && (n < LIMIT)) {
        zz = Cpow(z);
        z = Cadd(zz, c);
        
        n++;
    }
    return n;
}

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
            else { printf("%c", ASCII2[(m - 1) % strlen(ASCII2)]); }
            
        } 
        printf("\r\n");
    }
}


// main - is called by fractal.c function
int printMandelbrot() {
    callMandelbrot();
    return 0;
}

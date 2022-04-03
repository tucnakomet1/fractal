#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <complex.h>


// Defining the size of the screen.
#define LIMIT 30
#define LIMITSQUARED 4
#define ASCII " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"
#define STARTREAL -2
#define STARTIMAGINARY -1
#define END 1

int width, height;
void callMandelbrot();

// get resolution of terminal
void getResolution() {
    struct winsize wnsz;
    ioctl(0, TIOCGWINSZ, &wnsz);

    width = (wnsz.ws_row)/2;
    height = (wnsz.ws_col);

    printf("%d x %d \n", width, height);
}

int calculateMandel(double complex c) {
    double z = 0.0;
    int n = 0;

    while (n < LIMIT) {
        z = pow(z, 2) + c;

        if (abs(z) > 2) {
            // |z|<= 2;
            break;
        }
        n++;
    }

    return n;


}

void callMandelbrot() {
    getResolution();

    for (int x = 1; x <= width; x++) {
        for (int y = 1; y <= height; y++) {
            double realA = STARTREAL + (x / width) * (END - STARTREAL);
            double imaginaryB = STARTIMAGINARY + (y / height) * (END - STARTIMAGINARY);
            double complex c = CMPLX(realA, imaginaryB);

            int res = calculateMandel(c);
            //printf("%d\n", res);

            if (res >= LIMIT) {
                printf(" ");
            } else {
                //printf("res:%d\n", res);
                printf("C");
            }
            

        } printf("\r\n");
    }
}


// main - is called by fractal.c function
int printMandelbrot() {
    double real = 2.3;
    double image = 4.3;
    double complex z = CMPLX(real, image);
    double complex c = conjf(z);

    printf("z = %.1f%.1f\n c = %.1f\n abs=%.1f   %.1f\n", creal(c), cimag(c), c, abs(c), abs(z));
    callMandelbrot();
    return 0;
}

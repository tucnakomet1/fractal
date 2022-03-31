#include <stdio.h>
#include <stdlib.h>
//#include <graphics.h>
#include <sys/ioctl.h>
#include <complex.h>


// Defining the size of the screen.
#define height 1080
#define width 1920
#define MAXITERATION 1000

#define START -0.5
#define END 2.0
#define ASCII " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"


void callMandelbrot() {
    int x, y, i, j;
    int screen_x, screen_y, counter;
    double size_x, size_y;
    
    // getting size of screen (max_x X max_y)
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    screen_x = (w.ws_row)/8;
    screen_y = (w.ws_col)/12;

    // simple counting the center of the screen [...]
    // [...] to place there image

    /*
     for each pixel (Px, Py) on the screen do
    x0 = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.47))
    y0 = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.12, 1.12))
    x = 0.0
    y = 0.0
    iteration = 0
    max_iteration = 1000

    while (x*x + y*y ≤ 2*2 AND iteration < max_iteration) do
        aa = x*x - y*y + x0
        y = 2*x*y + y0
        x = xtemp
        iteration := iteration + 1

    color := palette[iteration]
    plot(Px, Py, color)
    */

    printf("%d, %d \n", screen_x, screen_y);

    for (y = 1; y <= screen_y - 1; y++) {
        for (x = 1; x <= screen_x - 1; x++) {
            double a = 0.0;
            double b = 0.0;

            //printf("%d, %d, %f, %f\n", y, x, a, b);

            int n = 0;
            int itertion = 0;

            while ((a*a + b*b <= 2*2) && (itertion < MAXITERATION)) {
                int aa = a*a - b*b;
                int bb = 2*a*b;

                a = aa;
                b = bb;
                
                printf("%c", ASCII[itertion / 72]); //number of chars in ASCII = 72
                
                itertion++;
                n++;
            } 

            if (n>MAXITERATION){
                printf(" ");
            }
        } printf("\r\n");
    }
}

int printMandelbrot() {
    double real = 2.3;
    double image = 4.3;
    double complex z = CMPLX(real, image);
    double complex c = conjf(z);

    //printf("z = %.1f%.1f\n", creal(c), cimag(c));
    callMandelbrot();
    return 0;
}

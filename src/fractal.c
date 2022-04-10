#include <stdio.h>
#include <stdbool.h>
#include "Sierpinsky/sierpinsky_carpet.h"
#include "Mandelbrot/mandelbrot_set.h"
#include "Mandelbrot/mandelbrot_sdl.h"

int main() {
    int option, n;

    printf("1 - Sierpiński carpet\n2 - Mandelbrot set ascii\n3 - Mandelbrot set render image\n4 - Mandelbrot GUI\n\nEnter option: ");
    scanf("%d", &option);

    if (option == 1) { 
        // Sierpiński carpet

        printf("\nEnter n: ");
        scanf("%d", &n);
        
        printSquare(n, 0, 0, nCount(n));

    } else if (option == 2) {
        // Mandelbrot set ascii mode

        /* bool color*/
        printMandelbrot(true);

    } else if (option == 3) {
        // Mandelbrot set rendering mode
        
        /* int width;
         * int height;
         * int format --> 0 = png;     1 = jpg;
         * int color ---> 0 = colored; 1 = gray; 2 = sepia;
         */
        renderMandelbrot(3000, 2000, 0, 1);
        
    } else if (option == 4) {
        // Mandelbrot GUI
        mandelbrot_sdl();
    }

    return 0;
}

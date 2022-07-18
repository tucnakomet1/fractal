#include <stdio.h>
#include <stdbool.h>
#include "Sierpinski/sierpinski_carpet.h"
#include "Mandelbrot/mandelbrot_set.h"
#include "Mandelbrot/mandelbrot_sdl.h"
#include "Lorenz/lorenz_atractor.h"

int main() {
    int option, rend, n;

    printf("0 - Cantor set\n"
            "1 - Sierpiński carpet\n"
            "2 - Sierpiński triangle\n"
            "3 - Lorenz attractor\n"
            "4 - Mandelbrot set\n"
            "5 - Koch snowflake\n"
            "6 - Barnsley fern\n"
            "7 - Bifurcation graph\n"
            "Enter option: ");
    scanf("%d", &option);

    if (option == 0) { 
        // Cantor set
        printf("\nNot done yet.\n");

    } else if (option == 1) {
        // Sierpiński carpet
        
        printf("\n1 - ASCII\n2 - stb\nEnter option: ");
        scanf("%d", &rend);
        if (rend == 1) {
            printCarpet(4);
        } else if (rend == 2) {
            renderCarpet(1600, 1600, 5, 1);
        }

    } else if (option == 2) {
        // Sierpiński triangle
        printf("\nNot done yet.\n");

    } else if (option == 3) {
        // Lorentz attractor
        printf("\nNot done yet.\n");

    } else if (option == 4) {
        // Mandelbrot set
        
        printf("\n1 - ASCII\n2 - stb\n3 - SDL\nEnter option: ");
        scanf("%d", &rend);

        if (rend == 1) {
            // Mandelbrot set in ascii

            /* bool color */
            printMandelbrot(true);

        } else if (rend == 2) {
            // Mandelbrot set in stb

            /* int width;
             * int height;
             * int format --> 0 = png;     1 = jpg;
             * int color ---> 0 = colored; 1 = red; 2 = gray; 3 = sepia;
             */
            renderMandelbrot(3000, 2000, 0, 1);
        } else if (rend == 3) {
            /* int color:
             * 0 = colorful; 
             * 1 = gray; 
             * 2 = sepia;
             */

            mandelbrot_sdl(1);
        }
    } else if (option == 5) {
        // Koch snowflake
        printf("\nNot done yet.\n");

    } else if (option == 6) {
        // Barnsley fern
        printf("\nNot done yet.\n");

    } else if (option == 7) {
        // Bifurcation graph
        printf("\nNot done yet.\n");
    }

    return 0;
}

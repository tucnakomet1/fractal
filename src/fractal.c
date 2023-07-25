#include <stdio.h>
#include <stdbool.h>
<<<<<<< HEAD
#include "Cantor/cantor.h"
#include "Sierpinski/sierpinski_carpet.h"
#include "Mandelbrot/mandelbrot_set.h"
#include "Mandelbrot/mandelbrot_sdl.h"
#include "Lorenz/lorenz_attractor.h"
=======
#include "Cantor/cantor.c"
#include "Sierpinski/sierpinski_carpet.c"
#include "Mandelbrot/mandelbrot_set.c"
#include "Mandelbrot/mandelbrot_sdl.c"
#include "Lorenz/lorenz_attractor.c"
#include "Bifurcation/bifurcation.c"
>>>>>>> abd62fc

void runCantor(int rend) {
    printf("\n1 - ASCII\n2 - stb\nEnter option: ");
    scanf("%d", &rend);

    if (rend == 1) 
        printCantor(5);              // int iter; -> iteration number
    else if (rend == 2)
        renderCantor(4000, 10, 1);   // width of img; number of iterations; 0 (white)/ 1 (color)

}

void runCarpet(int rend) {
    printf("\n1 - ASCII\n2 - stb\nEnter option: ");
    scanf("%d", &rend);

    if (rend == 1)
        printCarpet(4);             // int iter; -> iteration number
    else if (rend == 2) 
        renderCarpet(1600, 5, 1);   // width of img; num of iterations; 0 (white)/ 1 (color)
}

void runMandelbrot(int rend) {
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
}
<<<<<<< HEAD
=======

void runBifurcation() {
    renderBifurcation(2048, 1080, 500);
}
>>>>>>> abd62fc

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

    if (option == 0)            // Cantor set
        runCantor(rend);
    else if (option == 1)       // Sierpiński carpet
        runCarpet(rend);
    else if (option == 2)       // Sierpiński triangle
        printf("\nNot done yet.\n");
    else if (option == 3)       // Lorenz attractor
        renderLorenz(1920, 1080);
    else if (option == 4)       // Mandelbrot set
        runMandelbrot(rend);
    else if (option == 5)       // Koch snowflake
        printf("\nNot done yet.\n");
    else if (option == 6)       // Barnsley fern
        printf("\nNot done yet.\n");
    else if (option == 7)       // Bifurcation graph
<<<<<<< HEAD
        printf("\nNot done yet.\n");
=======
        runBifurcation();
>>>>>>> abd62fc

    return 0;
}

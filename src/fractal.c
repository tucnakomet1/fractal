#include <stdio.h>
#include <stdbool.h>
#include "Fractals/Cantor/cantor.c"
#include "Fractals/Sierpinski/sierpinski_carpet.c"
#include "Fractals/Mandelbrot/mandelbrot_set.c"
#include "Fractals/Mandelbrot/mandelbrot_sdl.c"
#include "Bifurcation/bifurcation.c"

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

void runBifurcation() {
    renderBifurcation(2048, 1080, 500);
}

int main() {
    int option, rend, n;

    printf("0 - Cantor set\n"
            "1 - Sierpiński carpet\n"
            "2 - Sierpiński triangle\n"
            "3 - Mandelbrot set\n"
            "4 - Koch snowflake\n"
            "5 - Barnsley fern\n"
            "6 - Bifurcation graph\n"
            "Enter option: ");
    scanf("%d", &option);

    if (option == 0)            // Cantor set
        runCantor(rend);
    else if (option == 1)       // Sierpiński carpet
        runCarpet(rend);
    else if (option == 2)       // Sierpiński triangle
        printf("\nNot done yet.\n");
    else if (option == 3)       // Mandelbrot set
        runMandelbrot(rend);
    else if (option == 4)       // Koch snowflake
        printf("\nNot done yet.\n");
    else if (option == 5)       // Barnsley fern
        printf("\nNot done yet.\n");
    else if (option == 10)       // Bifurcation graph
        runBifurcation();

    return 0;
}

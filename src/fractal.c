#include <stdio.h>
#include "Sierpinsky/sierpinsky_carpet.h"
#include "Mandelbrot/mandelbrot_set.h"


int main() {
    int option, n;

    printf("1 - Sierpiński carpet\n2 - Mandelbrot set\n\nEnter option: ");
    scanf("%d", &option);

    if (option == 1) { 
        // Sierpiński carpet
        //
        printf("\nEnter n: ");
        scanf("%d", &n);
        printSquare(n, 0, 0, nCount(n));
    } else if (option == 2) {
        // Mandelbrot set
        printMandelbrot();
    }

    return 0;
}

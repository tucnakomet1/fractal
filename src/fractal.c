#include <stdio.h>
#include "Sierpinsky/sierpinsky_carpet.h"
#include "Mandelbrot/mandelbrot_set.h"


int main() {
    int option, n;

    printf("1 - Sierpiński carpet\n2 - Mandelbrot set\n\nEnter option: ");
    scanf("%d", &option);
    
    printf("\nEnter n: ");
    scanf("%d", &n);

    if (option == 1) { 
        // Sierpiński carpet
        printSquare(n, 0, 0, nCount(n));
    } else if (option == 2) {
        // Mandelbrot set
        printMandelbrot(n);
    }

    return 0;
}

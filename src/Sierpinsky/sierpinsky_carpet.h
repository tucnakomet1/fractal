#include <stdio.h>
#include <math.h>

// counting if x & y is in carpet or not
int isInCarpet(int x, int y) {

    while(1) {
        if ((x == 0) || (y == 0)) {
            return 0;
        } else if ((x % 3 == 1) && (y % 3 == 1)) {
            // if mod is 1
            return 1;
        }
    
        x = x/3;
        y = y/3;    
    }
}

// main function
void printSquare(int n) {
    int div, size;

    //FILE *file;
    //file = fopen("fractal.txt", "w");

    size = (int)pow(3, n);
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {

            if (isInCarpet(x, y) == 0) {
                printf("ŇŇ");
                //fprintf(file, "ŇŇ");
            } else {
                printf("  ");
                //fprintf(file, "  ");
                ;
            }
        }

        printf("\n");
        //fprintf(file, "\n");
    }
    //fclose(file);
}



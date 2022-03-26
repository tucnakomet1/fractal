#include <stdio.h>
#include <math.h>


int printSquare(int n, int x, int y, int size) {
    int div;
    // print input values
    printf("n: %d, x: %d, y: %d, size: %d\n", n, x, y, size);

    FILE *file;
    file = fopen("fractal.txt", "w");

    // funciton
    for (int y = 0; y < size; y++) {
        //fflush(stdin);
        for (int x = 0; x < size; x++) {
            //counting
            for (div = size/3; div; div /= 3 ) {

                // if modulo == 1 -->
                if (((y % (div * 3)) / div == 1) && (((x % (div * 3)) / div == 1))) {
                    //printf("y: %d, x: %d, div: %d   -->   (%d % (%d * 3)) / %d,    (%d %, %d) = %d \n", y, x, div, x, div, div, x, div*3, (x % (div*3)));
                    break;
                } 
            }

            if (div == 0) {
                //printf("ŇŇ");
                printf("\x1b[48;5;15m  \x1b[0m");
                fprintf(file, "ŇŇ");
            } else {
                printf("  ");
                fprintf(file, "  ");
            }

        }
        printf("\n");
        fprintf(file, "\n");
    }
    fclose(file);
}


// resizing -> by "pixels"
int nCount(int n) {
    int size = 1;

    for (int i = 0; i < n; i++) { size = size * 3; }

    return size;
}

int main() {
    int n;

    printf("1 - Sierpiński carpet\n\n Enter n: ");
    scanf("%d", &n);
    
    // Sierpiński carpet
    printSquare(n, 0, 0, nCount(n));

    return 0;
}

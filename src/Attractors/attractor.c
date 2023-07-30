#include <stdio.h>
#include <stdbool.h>
#include "Lorenz/lorenz_attractor.c"
#include "Rossler/rossler_attractor.c"
#include "Thomas/thomas_attractor.c"
#include "Rabin/rabin_attractor.c"
#include "Multiscroll/multiscroll_attractor.c"

int main() {
    int width = 1920, height = 1080, option;
    
    char filename[100] = "";
    unsigned char image[width * height * 3];

    // make whole image black (0 = black)
    for (int i = 0; i < width * height *3; i++)
        image[i] = 0;

    // choose and render attractor

    printf("0 - Lorenz attractor\n"
            "1 - Rössler attractor\n"
            "2 - Thomas attractor\n"
            "3 - Rabin attractor\n"
            "4 - Chen attractor\n"
            "5 - Lu Chen attractor\n"
            "Enter option: ");
    scanf("%d", &option);

    if (option == 0) {                                  // Lorenz attractor
        strcpy(filename, "lorenz_attractor.png");
        countLorenz(image, width, height, 50000);
    } else if (option == 1) {                           // Rossler attractor
        strcpy(filename, "rossler_attractor.png");
        countRossler(image, width, height, 60000);
    } else if (option == 2) {                           // Thomas attractor
        strcpy(filename, "thomas_attractor.png");
        countThomas(image, width, height, 80000);
    } else if (option == 3) {                           // Rabin attractor
        strcpy(filename, "rabin_attractor.png");
        countRabin(image, width, height, 80000);
    } else if (option == 4) {                           // Chen attractor
        strcpy(filename, "chen_attractor.png");
        countChen(image, width, height, 80000);
    } else if (option == 5) {                           // Lu Chen attractor
        strcpy(filename, "lu_chen_attractor.png");
        countLuChen(image, width, height, 80000);
    }

    // save the image into png format
    if (stbi_write_png(filename, width, height, 3, image, width*3) == 0) {
        printf("Error: saving image\n");
    }

    return 0;
}

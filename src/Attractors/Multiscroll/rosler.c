#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <stdint.h>
#include <math.h>



// Funkce pro generování Chenova atraktoru a uložení do PNG
void generateChenAttractor(const char* filename, int width, int height, int iterations, double a, double b, double c) {
    double x = 1.0, y = 1.0, z = 1.0;
    double dt = 0.002; // Časový krok

    uint8_t* image_data = (uint8_t*)malloc(width * height * 3);

    for (int i = 0; i < iterations; i++) {
        // Kontrola, zda bod je uvnitř obrázku
        if (x >= -20 && x <= 20 && y >= -20 && y <= 20 && z >= 0 && z <= 40) {
            // Mapování hodnot x, y, z do pixelů obrázku
            int pixel_x = (int)((x + 20) * width / 40);
            int pixel_y = (int)((y + 20) * height / 40);
            int pixel_index = (pixel_y * width + pixel_x) * 3;


            image_data[pixel_index] = (int) i / 205;
            image_data[pixel_index + 1] = 255 - (int) i / 105;
            image_data[pixel_index + 2] = (int) i / 55;
        }

        double dx = a * (y - x);
        double dy = (c - a) * x - x * z + c * y;
        double dz = x * y - b * z;

        x += dx * dt;
        y += dy * dt;
        z += dz * dt;
    }

    int result = stbi_write_png(filename, width, height, 3, image_data, width * 3);
    if (result == 0) {
        fprintf(stderr, "Chyba při ukládání obrázku.\n");
    } else {
        printf("Obrázek byl úspěšně uložen do souboru %s.\n", filename);
    }

    free(image_data);
}

int main() {
    const char* filename = "chen_attractor.png";
    int width = 1920;
    int height = 1080;
    int iterations = 50000; // Počet iterací pro generování atraktoru
    double a = 35.0, b = 3.0, c = 28.0; // Parametry Chenova atraktoru

    generateChenAttractor(filename, width, height, iterations, a, b, c);

    return 0;
}

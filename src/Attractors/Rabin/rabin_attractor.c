
/* ************************************************ *
 * for alpha, gamma > 0 is the Rabinovich equation: *
 *                                                  *
 * dx/dt = y * (z - 1 + x*x) + gamma * x            *
 * dy/dt = x * (3*z + 1 - x*x) + gamma * y          *
 * dz/dt = -2*z * (alpha + x*y)                     *
 * ************************************************ */

void countRabin(unsigned char* image, int width, int height, int iterations) {
    // double gamma = 0.87, alpha = 1.1;    // variant 2
    // double dt = 0.002, scale = 190;      // variant 2

    double gamma = 0.1, alpha = 0.98;
    double x = -1, y = 0, z = 0.5;
    double dt = 0.05, scale = 150;

    int midX = width/2;
    int midH = height/2;

    for (int n = 0; n < iterations; n++) {
        double dx = (y * (z - 1 + x*x) + gamma * x) * dt;
        double dy = (x * (3*z + 1 - x*x) + gamma * y) * dt;
        double dz = (-2*z * (alpha + x*y)) * dt;

        x+= dx; y += dy; z += dz;

        int Y = y*scale + midH;
        if (Y >= 0 && Y < height)
            plotThePoint(image, x*scale + midX, Y, width, n);
    }
}

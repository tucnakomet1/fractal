
/* ************************************** *
 * for lambda > 0 is the Thomas equation: *
 *                                        *
 * dx/dt = sin(y) - lambda * x            *
 * dy/dt = sin(z) - lambda * y            *
 * dz/dt = sin(x) - lambda * z            *
 * ************************************** */

void countThomas(unsigned char* image, int width, int height, int iterations) {
    double lambda = 0.19;
    double x = 0.1,y = 0, z = 0;
    double dt = 0.03, scale = 130;

    int midX = width/2;
    int midH = height/2;

    for (int n = 0; n < iterations; n++) {
        double dx = (sin(y) - lambda*x) * dt;
        double dy = (sin(z) - lambda*y) * dt;
        double dz = (sin(x) - lambda*z) * dt;

        x+= dx; y += dy; z += dz;

        int Y = y*scale + midH;
        if (Y >= 0 && Y < height)
            plotThePoint(image, x*scale + midX, Y, width, n);
    }
}
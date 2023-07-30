
/* ****************************************************************** *
 * for alpha, beta, gamma > 0 is the Rössler equation:                *
 *                                                                    *
 * dx/dt = -y - z                                                     *
 * dy/dt = x + alpha * y          --> where alpha = 0.2               *
 * dz/dt = beta + z * (x - gamma) --> where beta = 0.2 and gamma = 14 *
 * ****************************************************************** */

void countRossler(unsigned char* image, int width, int height, int iterations) {
    double alpha = 0.2, beta = 0.2, gamma = 14;
    double x = 0.1,y = 0, z = 0;
    double dt = 0.03, scale = 18;

    int midX = width/2;
    int midH = height/2;

    for (int n = 0; n < iterations; n++) {
        double dx = (-y - z ) * dt;
        double dy = (x + alpha*y) * dt;
        double dz = (beta + z * (x - gamma)) * dt;

        x+= dx; y += dy; z += dz;

        int Y = y*scale + midH;
        if (Y >= 0 && Y < height)
            plotThePoint(image, x*scale + midX, Y, width, n);
    }
}
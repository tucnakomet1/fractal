
/* ************************************************ *
 * for alpha, beta, gamma > 0 is the Chen equation: *
 *                                                  *
 * dx/dt = alpha * (y - x)                          *
 * dy/dt = (gamma - alpha) * x - x*z + gamma * y    *
 * dz/dt = x*y - beta * z                           *
 *                                                  *
 * For Lu Chen and omega > 0:                       *
 *  dy/dt = x - x*z + gamma * y + omega             *
 * ************************************************ */

void countChen(unsigned char* image, int width, int height, int iterations) {
    double alpha = 40, beta = 3, gamma = 28;
    double x = -0.1, y = 0.5, z = -0.6;
    double dt = 0.001, scale = 18;

    int midX = width/2;
    int midH = height/2;

    for (int n = 0; n < iterations; n++) {
        double dx = (alpha * (y - x)) * dt;
        double dy = ((gamma - alpha) * x - x*z + gamma * y) * dt;
        double dz = (x*y - beta * z) * dt;

        x+= dx; y += dy; z += dz;

        int Y = y*scale + midH;
        if (Y >= 0 && Y < height)
            plotThePoint(image, x*scale + midX, Y, width, n);
    }
}

void countLuChen(unsigned char* image, int width, int height, int iterations) {
    double alpha = 34.5, beta = 9, gamma = 20, omega = -10;
    double x = 0.1, y = 0.3, z = -0.6;
    double dt = 0.001, scale = 16;
    

    int midX = width/2;
    int midH = height/2;

    for (int n = 0; n < iterations; n++) {
        double dx = (alpha * (y - x)) * dt;
        double dy = (x - x*z + gamma * y + omega) * dt;
        double dz = (x*y - beta * z) * dt;

        x+= dx; y += dy; z += dz;

        x+= dx; y += dy; z += dz;

        int Y = y*scale + midH;
        if (Y >= 0 && Y < height)
            plotThePoint(image, x*scale + midX, Y, width, n);
    }
}


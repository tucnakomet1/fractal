
/* ********************************************* *
 * for alpha = 1.4, beta = 0.3 is the Henon map: *
 *                                               *
 * x_{n+1} = 1 - alpha * x_n^2 + y_n             *
 * y_{n+1} = beta * x_n                          *
 * ********************************************* */

void countHenon(unsigned char* image, int width, int height, int iterations) {
    double alpha = 1.4, beta = 0.3;
    double x = 0.0, y = 0.0;

    double x_min = -1.5, x_max = 1.5;            // for x in [-1.5, 1.5]
    double y_min = -0.5, y_max = 0.5;            // for y in [-0.5, 0.5]

    for (int i = 0; i < iterations; i++) {
        int X = (x - x_min) * (width - 1) / (x_max - x_min);    // mapping x point into image
        int Y = (y - y_min) * (height - 1) / (y_max - y_min);   // mapping y point into image

        double x_ = 1.0 - (alpha * x*x) + y;
        y = beta * x;
        x = x_;


        if ((X >= 0 && X < width) && (Y >= 0 && Y < height))
            plotThePointWhite(image, X, Y, width);
    }
}
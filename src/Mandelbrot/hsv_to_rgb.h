#include <stdio.h>
#include <math.h>

int hsv_to_rgb(int H, int S, int V, int which) {
    double r, g, b;
    double s = (double)S/100;
    double v = (double)V/100;

    double C = s*v;
    double X = C*(1 - fabs(fmod((double)H/60.0, 2) - 1));
    double m = v - C;

    if (H >= 0 && H < 60) { r = C, g = X, b = 0; }
    else if(H >= 60 && H < 120) { r = X, g = C, b = 0; }
    else if(H >= 120 && H < 180) { r = 0, g = C, b = X; }
    else if(H >= 180 && H < 240) { r = 0, g = X, b = C; }
    else if(H >= 240 && H < 300) { r = X, g = 0, b = C; }
    else { r = C, g = 0, b = X; }

    if (which == 0) { return (r+m)*255; }
    else if (which == 1) { return (g+m)*255; }
    else { return (b+m)*255; }
}

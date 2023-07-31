void plotThePoint(unsigned char* image, int x, int y, int width, int n) {
    image[(y * width + x)*3] = (int) n / 205;
    image[(y * width + x)*3 + 1] = 255 - (int) n/105;
    image[(y * width + x)*3 + 2] = (int)n/55;
}

void plotThePointWhite(unsigned char* image, int x, int y, int width) {
    image[(y * width + x)*3] = 255;
    image[(y * width + x)*3 + 1] = 255;
    image[(y * width + x)*3 + 2] = 255;
}
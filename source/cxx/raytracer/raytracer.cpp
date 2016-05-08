#include "lodepng/lodepng.h"
#include <iostream>

#include "pixel.h"

using namespace std;

int main(int argc, char const *argv[])
{
    unsigned width = 100;
    unsigned height = 100;
    vector<Pixel> image(width*height, blue);

    Pixel start = black;
    Pixel end = white;

    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            double wEnd = double(w)/double(width);
            double wStart = 1 - wEnd;
            double hEnd = double(h)/double(height);
            double hStart = 1 - hEnd;

            unsigned char newR = start.R * hStart + end.R * hEnd;
            unsigned char newG = start.G * wStart + end.G * wEnd;
            unsigned char newB = start.B * hStart + end.B * hEnd;

            int vId = h * width + w;
            image[vId] = Pixel{newR, newG, newB};
            cout << vId << " " << wStart << " " << wEnd << " " << image[vId] << endl;
        }
    }

    //Encode the image
    unsigned error = lodepng::encode("output.png", reinterpret_cast<unsigned char*>(&image.front()), width, height);
    return 0;
}
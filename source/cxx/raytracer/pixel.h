#ifndef PIXEL_H
#define PIXEL_H

#include <ostream>

struct Pixel
{
    Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255):R{r}, G{g}, B{b}, A{a}{};
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};

std::ostream& operator<<(std::ostream& os, const Pixel& pix)
{
    return os << 'R' << int(pix.R) << ",G" << int(pix.G) << ",B" << int(pix.B) << ",A" << int(pix.A);
}

static const Pixel black{0, 0, 0};
static const Pixel white{255, 255, 255};
static const Pixel red{255, 0, 0};
static const Pixel green{0, 255, 0};
static const Pixel blue{0, 0, 255};

#endif
#include "status.hpp"


void setStatus(Adafruit_NeoPixel p, StatusCode s)
{
    p.setPixelColor(0, p.Color(s.r, s.g, s.b));
    p.show();
}
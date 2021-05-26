#define FASTLED_USE_GLOBAL_BRIGHTNESS 1
#include <FastLED.h>
#define NUM_LEDS 32

struct StatusCode {
  int r;
  int g;
  int b;
};

const StatusCode ERROR = StatusCode{255, 0, 0};
const StatusCode BLUE = StatusCode{0, 0, 255};
const StatusCode WARNING = StatusCode{255, 255, 0};
const StatusCode NFC = StatusCode{0, 255, 255};
const StatusCode SUCCESS = StatusCode{0, 255, 0};
const StatusCode CLEAR = StatusCode{0, 0, 0};

const uint8_t scanPattern[] =
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};

const CRGB standardColor = CRGB(5,5,9);


void setStatus( StatusCode s);
void spinStatus();
void initStatus();

void conn(bool val);

void flash(bool success);
void box(CRGB color);
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

void setStatus( StatusCode s);
void spinStatus();
void initStatus();

void flash();
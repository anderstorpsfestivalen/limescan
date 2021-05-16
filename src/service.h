#include <bluefruit.h>


const uint8_t scanServiceUUID[] =
{
    0X5B, 0X24, 0XF0, 0X3D, 0XEA, 0X3D, 0X46, 0XB7,
    0XF3, 0X46, 0X82, 0X18, 0X2A, 0X8E, 0XEC, 0X78
};

const uint8_t scanCharacteristicUUID[] =
{
    0X28, 0XAB, 0X9F, 0X16, 0X9E, 0X7D, 0XEE, 0XBC,
    0X7A, 0X43, 0X10, 0X20, 0X81, 0X0B, 0X8A, 0X83
};


void initBLE();
void startAdv();

bool sendCard(const char* str);
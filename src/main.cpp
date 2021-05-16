#include <Wire.h>
#include <bluefruit.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include "service.h"
//#include "status.hpp"


Adafruit_PN532 nfc(5);

void initNFC();
void scanNFC();
void showsuccess();
void array_to_string(byte array[], unsigned int len, char buffer[]);

void setup()
{
	Serial.begin(115200);

	Serial.println("Starting Limescan");

	initBLE();

	initNFC();

	//initStatus();

	Scheduler.startLoop(scanNFC);
}

void loop()
{
	delay(50);
	yield();
}

void initNFC()
{

	nfc.begin();

	uint32_t versiondata = nfc.getFirmwareVersion();
	if (!versiondata)
	{
		Serial.print("Didn't find PN53x board");
	}
	delay(100);

	Serial.print("Found chip PN5");
	Serial.println((versiondata >> 24) & 0xFF, HEX);
	Serial.print("Firmware ver. ");
	Serial.print((versiondata >> 16) & 0xFF, DEC);
	Serial.print('.');
	Serial.println((versiondata >> 8) & 0xFF, DEC);

	nfc.SAMConfig();
}

void scanNFC()
{
	uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; // buffer to store the returned uid
	uint8_t uidLength;	

	if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 3000))
	{
		if (Bluefruit.connected())
		{
			char str[64] = "";
			array_to_string(uid, uidLength, str);
			sendCard(str);
		}
	}

	delay(2000);
}

void array_to_string(byte array[], unsigned int len, char buffer[])
{
	for (unsigned int i = 0; i < len; i++)
	{
		byte nib1 = (array[i] >> 4) & 0x0F;
		byte nib2 = (array[i] >> 0) & 0x0F;
		buffer[i * 2 + 0] = nib1 < 0xA ? '0' + nib1 : 'A' + nib1 - 0xA;
		buffer[i * 2 + 1] = nib2 < 0xA ? '0' + nib2 : 'A' + nib2 - 0xA;
	}
	buffer[len * 2] = '\0';
}

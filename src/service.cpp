#include "service.h"

BLEService scanService = BLEService(scanServiceUUID);
BLECharacteristic scanCharacteristic = BLECharacteristic(scanCharacteristicUUID);

void initBLE()
{
    Bluefruit.begin();

    scanService.begin();

    scanCharacteristic.setProperties(CHR_PROPS_NOTIFY);
    scanCharacteristic.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);

    scanCharacteristic.begin();

    startAdv();
}

void startAdv(void)
{
    Bluefruit.setTxPower(4);
    Bluefruit.setName("ATPSCAN");

    // Advertising packet
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();

    // include the ble uart (aka 'nus') 128-bit uuid
    Bluefruit.Advertising.addService(scanService);

    // secondary scan response packet (optional)
    // since there is no room for 'name' in Advertising packet
    Bluefruit.ScanResponse.addName();

    /* start Advertising
	 * - enable auto Advertising if disconnected
	 * - interval:  fast mode = 20 ms, slow mode = 152.5 ms
	 * - timeout for fast mode is 30 seconds
	 * - start(timeout) with timeout = 0 will advertise forever (until connected)
	 */

    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);   // number of seconds in fast mode
    Bluefruit.Advertising.start(0);             // 0 = don't stop Advertising after n seconds

    Bluefruit.autoConnLed(false);
}

bool sendCard(const char *str)
{
    return scanCharacteristic.notify(str);
}
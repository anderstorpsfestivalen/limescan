#include "service.h"

BLEService scanService = BLEService(scanServiceUUID);
BLECharacteristic scanCharacteristic = BLECharacteristic(scanCharacteristicUUID);
BLECharacteristic callbackCharacteristic = BLECharacteristic(callbackUUID);
datacb db;
conncb conncallback;


void initBLE()
{
    Bluefruit.begin();
    Bluefruit.Periph.setConnectCallback(connect_callback);
    Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

    scanService.begin();

    scanCharacteristic.setProperties(CHR_PROPS_NOTIFY);
    scanCharacteristic.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);

    scanCharacteristic.begin();

    callbackCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
    callbackCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
    callbackCharacteristic.setFixedLen(1);
    callbackCharacteristic.setWriteCallback(cb);

    callbackCharacteristic.begin();

    startAdv();
}

void registerCallback(datacb c) {
    db = c;
}

void registerConnectionCallback(conncb c) {
    conncallback = c;
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

void cb(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len) {
    Serial.println(data[0]);
    db(data[0]);
}


void connect_callback(uint16_t conn_handle) {
   conncallback(true);
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
   conncallback(false);
}
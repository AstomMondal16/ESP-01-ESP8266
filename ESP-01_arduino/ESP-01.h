#ifndef ESP01_H
#define ESP01_H

#include <Arduino.h>

class ESP01 {
  public:
    ESP01(HardwareSerial &serial, uint32_t baudRate = 115200);
    void begin();
    void sendCommand(const char *command, uint32_t delayMs = 1000);
    String readResponse();
    bool testConnection();
    bool setMode(uint8_t mode);
    bool connectWiFi(const char *ssid, const char *password);
    String ping(const char *host);

  private:
    HardwareSerial &_serial;
    uint32_t _baudRate;
};

#endif // ESP01_H

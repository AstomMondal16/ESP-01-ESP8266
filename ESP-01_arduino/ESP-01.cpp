#include "ESP01.h"

ESP01::ESP01(HardwareSerial &serial, uint32_t baudRate) 
  : _serial(serial), _baudRate(baudRate) {}

void ESP01::begin() {
    _serial.begin(_baudRate);
}

void ESP01::sendCommand(const char *command, uint32_t delayMs) {
    _serial.print(command);
    _serial.print("\r\n"); // Add carriage return and newline
    delay(delayMs);        // Wait for the ESP-01 to process the command
}

String ESP01::readResponse() {
    String response = "";
    while (_serial.available()) {
        response += char(_serial.read());
    }
    return response;
}

bool ESP01::testConnection() {
    sendCommand("AT");
    String response = readResponse();
    return response.indexOf("OK") != -1;
}

bool ESP01::setMode(uint8_t mode) {
    String command = "AT+CWMODE=" + String(mode);
    sendCommand(command.c_str());
    String response = readResponse();
    return response.indexOf("OK") != -1;
}

bool ESP01::connectWiFi(const char *ssid, const char *password) {
    String command = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"";
    sendCommand(command.c_str(), 5000); // Longer delay for connection
    String response = readResponse();
    return response.indexOf("OK") != -1;
}

String ESP01::ping(const char *host) {
    String command = "AT+PING=\"" + String(host) + "\"";
    sendCommand(command.c_str(), 2000); // Wait for ping response
    return readResponse();
}

#include "ESP01.h"

// Use Serial1 for UART communication with ESP-01 (Adjust pins for your board)
ESP01 esp(Serial1);

void setup() {
    Serial.begin(115200);
    esp.begin();

    // Test connection
    Serial.println("Testing ESP-01 connection...");
    if (esp.testConnection()) {
        Serial.println("ESP-01 is connected.");
    } else {
        Serial.println("Failed to connect to ESP-01.");
        return;
    }

    // Set to Station (STA) mode
    Serial.println("Setting mode to Station...");
    if (esp.setMode(1)) {
        Serial.println("Mode set to Station.");
    } else {
        Serial.println("Failed to set mode.");
    }

    // Connect to Wi-Fi
    const char *ssid = "ASTOM"			# GIVE YOUR SSID
    const char *password = "PASSWORD";		# GIVE YOUR PASSWORD
    Serial.println("Connecting to Wi-Fi...");
    if (esp.connectWiFi(ssid, password)) {
        Serial.println("Connected to Wi-Fi.");
    } else {
        Serial.println("Failed to connect to Wi-Fi.");
    }

    // Ping a remote host
    const char *host = "google.com";	# the site where you willing to connect
    Serial.println("Pinging remote host...");
    String pingResponse = esp.ping(host);
    Serial.println("Ping Response:");
    Serial.println(pingResponse);
}

void loop() {
    // Nothing to do in the loop
}

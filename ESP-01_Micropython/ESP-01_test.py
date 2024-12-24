from esp01_driver import ESP01

def main():
    # Initialize the ESP-01 driver
    esp = ESP01(uart_num=1, tx_pin=40, rx_pin=39)

    # Test ESP-01 connection
    print("Testing connection...")
    response = esp.test_connection()
    if "OK" in response:
        print("ESP-01 is connected.")
    else:
        print("Failed to connect to ESP-01.")
        return

    # Set to Station mode (STA)
    print("Setting mode to Station (STA)...")
    response = esp.set_mode(mode=1)
    print("Response:", response)

    # Connect to Wi-Fi
    print("Connecting to Wi-Fi...")
    ssid = "ASTOM"				#GIVE YOUR SSID
    password = "PASSWORD"			#GIVE YOUR PASSWORD
    response = esp.connect_wifi(ssid, password)
    print("Response:", response)

    # Send a ping command
    print("Pinging a remote host...")
    host = "google.com"
    response = esp.ping(host)
    print("Ping Response:", response)

if __name__ == "__main__":
    main()

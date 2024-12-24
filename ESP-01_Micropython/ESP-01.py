from machine import UART, Pin
import time

class ESP01:
    def __init__(self, uart_num, tx_pin, rx_pin, baud_rate=115200, rx_buf_size=1024):
        """
        Initialize the ESP-01 module with UART.
        """
        self.uart = UART(uart_num, baudrate=baud_rate, tx=Pin(tx_pin), rx=Pin(rx_pin), timeout=1000)
        self.rx_buf_size = rx_buf_size

    def send_at_command(self, command, delay_ms=1000):
        """
        Send an AT command to the ESP-01 module and wait for a response.
        """
        full_command = command + "\r\n"
        self.uart.write(full_command)
        print(f"Sent: {command}")
        time.sleep_ms(delay_ms)

    def read_response(self):
        """
        Read the response from the ESP-01 module.
        """
        if self.uart.any():
            response = self.uart.read(self.rx_buf_size).decode('utf-8', errors='ignore')
            print(f"Received: {response}")
            return response
        return ""

    def test_connection(self):
        """
        Test the ESP-01 connection with a simple AT command.
        """
        self.send_at_command("AT")
        return self.read_response()

    def set_mode(self, mode=1):
        """
        Set the ESP-01 to a specific mode (default: STA mode).
        - Mode 1: Station (STA)
        - Mode 2: SoftAP
        - Mode 3: Station + SoftAP
        """
        self.send_at_command(f"AT+CWMODE={mode}")
        return self.read_response()

    def connect_wifi(self, ssid, password):
        """
        Connect to a Wi-Fi network.
        """
        self.send_at_command(f'AT+CWJAP="{ssid}","{password}"', delay_ms=5000)
        return self.read_response()

    def ping(self, host):
        """
        Ping a remote host.
        """
        self.send_at_command(f'AT+PING="{host}"', delay_ms=2000)
        return self.read_response()

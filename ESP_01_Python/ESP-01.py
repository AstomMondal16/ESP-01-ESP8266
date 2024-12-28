import serial
import time

class ESP01:
    def __init__(self, port="/dev/serial0", baud_rate=115200, timeout=1):
        """
        Initialize the ESP-01 module with UART.
        """
        try:
            self.uart = serial.Serial(port, baudrate=baud_rate, timeout=timeout)
            print(f"Initialized UART on {port} at {baud_rate} baud.")
        except Exception as e:
            raise Exception(f"Failed to initialize UART: {str(e)}")

    def send_at_command(self, command, delay_ms=1000):
        """
        Send an AT command to the ESP-01 module and wait for a response.
        """
        full_command = (command + "\r\n").encode("utf-8")
        self.uart.write(full_command)
        print(f"Sent: {command}")
        time.sleep(delay_ms / 1000)  # Convert delay to seconds

    def read_response(self):
        """
        Read the response from the ESP-01 module.
        """
        response = self.uart.read_all().decode("utf-8", errors="ignore")
        print(f"Received: {response.strip()}")
        return response.strip()

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

import serial
import time

# config UART3
UART_PORT = "/dev/ttyS3"  # or "COM3" for Windows
BAUDRATE = 9600

# Open port
ser = serial.Serial(UART_PORT, BAUDRATE, timeout=1)
print("Open port: ", UART_PORT)

calc = int(0)

try:
    while True:
        # Send data
        ser.write(b"Hello UART!\n")
        print("Send data: Hello UART! Num: ", calc)
        calc = calc + 1

        # Read data (if data present)
        if ser.in_waiting:
            received_data = ser.readline().decode(errors='ignore').strip()
            print("Reciev: ", received_data)

        time.sleep(1)  # delay 1 s

except KeyboardInterrupt:
    print("\nExit...")
    ser.close()

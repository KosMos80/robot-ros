#!/usr/bin/env python
import serial
import time

# config UART3
UART_PORT = "/dev/ttyS3"  # or "COM3" for Windows
BAUDRATE = 57600

# Open port
ser = serial.Serial(UART_PORT, BAUDRATE, timeout=1)
print("Open port: ", UART_PORT)

calc = int(0)

try:
    while True:
        # Send data
        # ser.write(b"Hello UART!\n")
        # print("Send data: Hello UART! Num: ", calc)
        # calc = calc + 1

        # Read data (if data present)
#        if ser.in_waiting:
            #received_data = ser.read(ser.in_waiting)
            #received_data = ser.readline().decode(errors='ignore').strip()
            #received_data = ser.read_until(b'\n')
        received_data = ser.readline()
#        print("Reciev: ", received_data)
        long = len(received_data) - 2
        st = received_data[0:long]
#        fst = float(st)
#        fst = (fst * 9 / 64) / 1024
#        print(st, " ", fst)
        print(st)



#        time.sleep(1)  # delay 1 s

except KeyboardInterrupt:
    print("\nExit...")
    ser.close()

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
        com = input("Enter command w,a,s,d,x")
        if(com == 'w'):
            print(" To forward ")
        if(com == 'a'):
            print(" To left ")
        if(com == 's'):
            print(" STOP ")
        if(com == 'd'):
            print(" To right ")
        if(com == 'x'):
            print(" To back ")
        ser.write(b"Hello UART!\n")

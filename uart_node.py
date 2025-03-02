#!/usr/bin/env python
import rospy
from std_msgs.msg import String, Int16, Float64
import serial
import time

# config UART3
UART_PORT = "/dev/ttyS3"  # or "COM3" for Windows
BAUDRATE = 57600



print("Setup pereferal uart... ")
# Open port
ser = serial.Serial(UART_PORT, BAUDRATE, timeout=1)
print("Open port: ", UART_PORT)

azimut = 0
sumz = 0
sigma = 0

cx = 0

if __name__ == '__main__':
    try:
        rospy.init_node('reader_uart')  # init node
        pub = rospy.Publisher('/axis', Float64, queue_size=10)  # send to topic /cmd_vel
        # Read data (if data present)
        while True:
            received_data = ser.readline()
            ln = len(received_data) - 2
            fst = float(received_data[0:ln]) # - 15.2009
            dps = fst - 10
            if(abs(dps) < 60):
                dps = 0

#            sumz = sumz + fst
#            sigma = sigma + fst * fst
#            cx = cx + 1
#            if(cx == 1000):
#                delta = sumz / cx
#                sig = sigma / cx
#                tresh = (sig - delta * delta) ** 0.5
#                print(" delta:", delta, "  sigma:", tresh)
#                sumz = 0
#                sigma = 0
#                cx = 0
            #print("Recieve: ", fst)

            azimut = azimut + dps
            pub.publish(azimut * 0.00875 / 64)

    except rospy.ROSInterruptException:
        ser.close()
        pass


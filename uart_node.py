#!/usr/bin/env python
import rospy
from std_msgs.msg import String, Int8
import serial
import time

# config UART3
UART_PORT = "/dev/ttyS3"  # or "COM3" for Windows
BAUDRATE = 9600



if __name__ == '__main__':
    #initialize the gpio module
    try:
        print("Setup pereferal uart... ")
        # Open port
        ser = serial.Serial(UART_PORT, BAUDRATE, timeout=1)
        print("Open port: ", UART_PORT)

        rospy.init_node('reader_uart')  # init node
        pub = rospy.Publisher('/uart_data', String, queue_size=10)  # send to topic /cmd_vel

        # Read data (if data present)
        while(1):
            if ser.in_waiting:
                received_data = ser.readline().decode(errors='ignore').strip()
                pub.publish(received_data)



    except rospy.ROSInterruptException:
        print("exit from node...")


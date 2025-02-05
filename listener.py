#!/usr/bin/env python
import rospy
from std_msgs.msg import String

from pyA20.gpio import gpio
from pyA20.gpio import port

def callback(data):
    rospy.loginfo("I recive message: %s", data.data)
    if(data.data == 1):
        print("ON pin PA7")
        gpio.output(port.PA7, gpio.HIGH)
    if(data.data == 2):        
        print("ON pin PA8")
        gpio.output(port.PA8, gpio.HIGH)
    if(data.data == 0):
        print("clear all")
        gpio.output(port.PA7, gpio.LOW)
        gpio.output(port.PA8, gpio.LOW)

def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("chatter", String, callback)
    rospy.spin()

if __name__ == '__main__':
    #initialize the gpio module
    gpio.init()

    #setup the port (same as raspberry pi's gpio.setup() function)

    gpio.setcfg(port.PA7, gpio.OUTPUT)
    gpio.setcfg(port.PA8, gpio.OUTPUT)
    listener()
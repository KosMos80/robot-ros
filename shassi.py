#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

from pyA20.gpio import gpio
from pyA20.gpio import port

def callback(data):
    #rospy.loginfo("I recive message: %s", data)
    #print(data)
    lin = data.linear.x
    ang = data.angular.z
    print("Lin Sp:", lin, " Ang Sp: ", ang)

'''
    if(data.data == 1):
        print("ON pin PA7")
        gpio.output(port.PA7, gpio.HIGH)
    if(data.data == 2):
        print("ON pin PA8")
        gpio.output(port.PA8, gpio.HIGH)
    if(data.data == 3):
        print("ON pin PA9")
        gpio.output(port.PA9, gpio.HIGH)
    if(data.data == 0):
        print("clear all")
        gpio.output(port.PA7, gpio.LOW)
        gpio.output(port.PA8, gpio.LOW)
        gpio.output(port.PA9, gpio.LOW)
'''

def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("cmd_vel", Twist, callback)
    rospy.spin()

if __name__ == '__main__':
    #initialize the gpio module
    try:
        gpio.init()

    #setup the port (same as raspberry pi's gpio.setup() function)

        gpio.setcfg(port.PA7, gpio.OUTPUT)
        gpio.setcfg(port.PA8, gpio.OUTPUT)
        gpio.setcfg(port.PA9, gpio.OUTPUT)
        gpio.setcfg(port.PA10, gpio.OUTPUT)
        listener()
    except rospy.ROSInterruptException:
        pass

    finally:
        gpio.output(port.PA7, gpio.LOW)
        gpio.output(port.PA8, gpio.LOW)
        gpio.output(port.PA9, gpio.LOW)
        gpio.output(port.PA10, gpio.LOW)

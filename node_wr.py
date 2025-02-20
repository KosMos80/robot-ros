#!/usr/bin/env python
import rospy
from std_msgs.msg import String, Int8
from geometry_msgs.msg import Twist


def talker():
    cd = 1
    rep = 0
    pub = rospy.Publisher('chatter', Int8, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)  # 1 second message

    while not rospy.is_shutdown():

      rep = rep + 1
        rep = rep % 2
        if(rep == 1):
            cd = cd + 1
        if(cd == 4):
            cd = 0
        rospy.loginfo("Hello, world! Time: %s" % rospy.get_time())
        if(rep == 1):
            pub.publish(cd)
        else:
            pub.publish(0)
        rate.sleep()

def callback(data):
    rospy.loginfo("I recive message: %s", data.data)
    print(data.data)

def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("/cmd_vel", Twist, callback)
    #rospy.spin()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass


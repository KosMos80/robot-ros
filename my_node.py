#!/usr/bin/env python
import rospy
from std_msgs.msg import String

cd = 0

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(1)  # 1 second message

    while not rospy.is_shutdown():
        #msg = "Hello, world! Time: %s" % rospy.get_time()
        msg = "%d" % cd
        cd = cd + 1
        if(cd == 4):
            cd = 0
        rospy.loginfo(msg)
        pub.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
#!/usr/bin/env python
import rospy
from std_msgs.msg import String, Int8



def talker():
    cd = 1
    rep = 0
    #pub = rospy.Publisher('chatter', String, queue_size=10)
    pub = rospy.Publisher('chatter', Int8, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)  # 1 second message

    while not rospy.is_shutdown():
#        msg = "Hello, world! Time: %s" % rospy.get_time()
#        msg = cd
#        print("%d" % cd)

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

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass


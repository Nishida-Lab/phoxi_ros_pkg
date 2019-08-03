#!/usr/bin/env python
import rospy
import rospkg
import tf
from tf.transformations import quaternion_from_euler, euler_from_quaternion

import tf2_ros
import geometry_msgs.msg

import numpy as np

class SensorTFbr:

    def __init__(self):
        rospy.init_node('tf_broadcaster', anonymous=True)
        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer)
        self.sensor_name = rospy.get_param('~sensor_name', "photoneo_test")

    def tf_broadcaster(self):
        rate = rospy.Rate(10.0)
        while not rospy.is_shutdown():
            r = np.pi/2.0
            p = np.pi
            y = np.pi/2.0
            # r = 0
            # p = np.pi
            # y = 0
            o = quaternion_from_euler(r, p, y)
            br = tf.TransformBroadcaster()
            br.sendTransform((0,0,0),o,
                             rospy.Time.now(),
                             self.sensor_name+"_optical_frame",
                             self.sensor_name)
            rate.sleep()


if __name__ == '__main__':

    rospack = rospkg.RosPack()
    sensor_tf_br = SensorTFbr()
    sensor_tf_br.tf_broadcaster()

#!/usr/bin/env python
import rospy
from phoxi_camera.srv import *
from std_srvs.srv import *

if __name__ == "__main__":
    rospy.init_node('phoxi_camera_get_frame', anonymous=True)
    sensor_name = rospy.get_param('~sensor_name', "photoneo_center")

    get_frame_srv_name = sensor_name + '/get_frame'
    get_frame_srv = rospy.ServiceProxy(get_frame_srv_name, GetFrame)

    rospy.loginfo("Waiting for service: {}".format(get_frame_srv_name))
    rospy.wait_for_service(get_frame_srv_name)
    rospy.loginfo("Service found: {}".format(get_frame_srv_name))

    while not rospy.is_shutdown():
        try:
            res_get_fram = get_frame_srv(-1)
            print("get_frame: {}".format(res_get_fram))
        except rospy.ServiceException as e:
            print("Service call failed: {}".format(e))

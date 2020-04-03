#include <phoxi_bringup/phoxi_camera_pointcloud_pub_server.h>

using phoxi_camera_pointcloud_pub_server::PhoXiCameraPointCloudPubServer;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "phoxi_camera_pointcloud_pub_server_node");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  PhoXiCameraPointCloudPubServer phoxi_camera_pointcloud_pub_server(nh);

  ros::Rate rate(0.5);

  while (ros::ok())
  {
    phoxi_camera_pointcloud_pub_server.publishPointCloud();
    rate.sleep();
  }

  return 0;
}
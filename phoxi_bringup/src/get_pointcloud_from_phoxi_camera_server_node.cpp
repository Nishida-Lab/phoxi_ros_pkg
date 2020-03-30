#include <phoxi_bringup/get_pointcloud_from_phoxi_camera_server.h>

using get_pointcloud_from_phoxi_camera_server::GetPointCloudFromPhoXiCameraServer;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "get_pointcloud_from_phoxi_camera_server_node");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  GetPointCloudFromPhoXiCameraServer get_pointcloud_from_phoxi_camera_server(nh);

  ros::Rate rate(0.5);

  while (ros::ok())
  {
    ros::spinOnce();
    get_pointcloud_from_phoxi_camera_server.publishPointCloud();
    rate.sleep();
  }

  return 0;
}
#ifndef GET_POINTCLOUD_FROM_PHOXI_CAMERA_SERVER_H
#define GET_POINTCLOUD_FROM_PHOXI_CAMERA_SERVER_H

#include <ros/ros.h>
#include <string>

#include <sensor_msgs/PointCloud2.h>

#include <phoxi_camera_srvs/GetPhoXiPointCloud.h>

namespace get_pointcloud_from_phoxi_camera_server
{
class GetPointCloudFromPhoXiCameraServer
{
public:
  GetPointCloudFromPhoXiCameraServer(ros::NodeHandle& nh);
  void publishPointCloud();

private:
  void receivePointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& cloud);
  bool getPointCloud(phoxi_camera_srvs::GetPhoXiPointCloud::Request& req,
                     phoxi_camera_srvs::GetPhoXiPointCloud::Response& res);

private:
  ros::NodeHandle nh_;
  ros::ServiceServer get_pointcloud_server_;
  ros::ServiceClient start_publish_pointcloud_client_;
  ros::ServiceClient stop_publish_pointcloud_client_;
  ros::Publisher pointcloud_pub_;
  ros::Subscriber pointcloud_sub_;
  sensor_msgs::PointCloud2 sensor_cloud_;
  sensor_msgs::PointCloud2 receive_cloud_;
  std::string sensor_name_;
  std::string cloud_name_;
  bool is_ok_;
  int timeout_;
  double interval_time_;
};
}  // namespace get_pointcloud_from_phoxi_camera_server

#endif  // GET_POINTCLOUD_FROM_PHOXI_CAMERA_SERVER_H
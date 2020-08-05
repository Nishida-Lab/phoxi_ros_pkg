#ifndef PHOXI_CAMERA_POINTCLOUD_PUB_SERVER_H
#define PHOXI_CAMERA_POINTCLOUD_PUB_SERVER_H

#include <ros/ros.h>
#include <string>
#include <sensor_msgs/PointCloud2.h>

#include <phoxi_camera_srvs/PublishPointCloud.h>

namespace phoxi_camera_pointcloud_pub_server
{
class PhoXiCameraPointCloudPubServer
{
public:
  PhoXiCameraPointCloudPubServer(ros::NodeHandle& nh);
  void publishPointCloud();
private:
  bool startPubPointCloud(phoxi_camera_srvs::PublishPointCloud::Request& req, phoxi_camera_srvs::PublishPointCloud::Response& res);
  bool stopPubPointCloud(phoxi_camera_srvs::PublishPointCloud::Request& req, phoxi_camera_srvs::PublishPointCloud::Response& res);
private:
  ros::NodeHandle nh_;
  ros::ServiceServer start_publish_pointcloud_server_;
  ros::ServiceServer stop_publish_pointcloud_server_;
  ros::ServiceClient phoxi_camera_client_;
  std::string sensor_name_;
  bool is_ok_;
};
} // namespace phoxi_camera_pointcloud_pub_server

#endif // PHOXI_CAMERA_POINTCLOUD_PUB_SERVER_H
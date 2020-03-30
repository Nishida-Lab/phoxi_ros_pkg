#include <phoxi_bringup/phoxi_camera_pointcloud_pub_server.h>

#include <phoxi_camera/GetFrame.h>

using phoxi_camera_pointcloud_pub_server::PhoXiCameraPointCloudPubServer;

PhoXiCameraPointCloudPubServer::PhoXiCameraPointCloudPubServer(ros::NodeHandle& nh) : nh_(nh), is_ok_(false)
{
  ros::param::param<std::string>("~sensor_name", sensor_name_, "photoneo_center");
  start_publish_pointcloud_server_ = nh.advertiseService("/phoxi_bringup/start_publish_pointcloud", &PhoXiCameraPointCloudPubServer::startPubPointCloud, this);
  stop_publish_pointcloud_server_ = nh.advertiseService("/phoxi_bringup/stop_publish_pointcloud", &PhoXiCameraPointCloudPubServer::stopPubPointCloud, this);
  phoxi_camera_client_ = nh.serviceClient<phoxi_camera::GetFrame>("/" + sensor_name_ + "/get_frame");
}

bool PhoXiCameraPointCloudPubServer::startPubPointCloud(phoxi_camera_srvs::PublishPointCloud::Request& req, phoxi_camera_srvs::PublishPointCloud::Response& res)
{
  is_ok_ = true;
  res.success = true;
  return res.success;
}

bool PhoXiCameraPointCloudPubServer::stopPubPointCloud(phoxi_camera_srvs::PublishPointCloud::Request& req, phoxi_camera_srvs::PublishPointCloud::Response& res)
{
  is_ok_ = false;
  res.success = true;
  return res.success;
}

void PhoXiCameraPointCloudPubServer::publishPointCloud()
{
  phoxi_camera::GetFrame get_frame;
  get_frame.request.in = -1;
  if (is_ok_)
  {
    if(!phoxi_camera_client_.call(get_frame))
    {
      ROS_ERROR_STREAM("Failed to publish point cloud !!");
    }
  }
}
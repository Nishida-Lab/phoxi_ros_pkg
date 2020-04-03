#include <phoxi_bringup/get_pointcloud_from_phoxi_camera_server.h>

#include <phoxi_camera_srvs/PublishPointCloud.h>

using get_pointcloud_from_phoxi_camera_server::GetPointCloudFromPhoXiCameraServer;

GetPointCloudFromPhoXiCameraServer::GetPointCloudFromPhoXiCameraServer(ros::NodeHandle& nh) : nh_(nh), is_ok_(false)
{
  ros::param::param<int>("~timeout", timeout_, 100);
  ros::param::param<std::string>("~sensor_name", sensor_name_, "photoneo_center");
  ros::param::param<std::string>("~cloud_name", cloud_name_, "/get_point_cloud");
  ros::param::param<double>("~interval_time", interval_time_, 2.0);
  get_pointcloud_server_ =
      nh.advertiseService("/phoxi_bringup/get_pointcloud", &GetPointCloudFromPhoXiCameraServer::getPointCloud, this);
  start_publish_pointcloud_client_ =
      nh.serviceClient<phoxi_camera_srvs::PublishPointCloud>("/phoxi_bringup/start_publish_pointcloud");
  stop_publish_pointcloud_client_ =
      nh.serviceClient<phoxi_camera_srvs::PublishPointCloud>("/phoxi_bringup/stop_publish_pointcloud");
  pointcloud_pub_ = nh.advertise<sensor_msgs::PointCloud2>(cloud_name_, 1);
  pointcloud_sub_ = nh.subscribe("/" + sensor_name_ + "/pointcloud", 1,
                                 &GetPointCloudFromPhoXiCameraServer::receivePointCloudCallback, this);
  ROS_INFO("Instance GetPointCloudFromPhoXiCameraServer class !!");
}

void GetPointCloudFromPhoXiCameraServer::receivePointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& cloud)
{
  receive_cloud_ = *cloud;
}

bool GetPointCloudFromPhoXiCameraServer::getPointCloud(phoxi_camera_srvs::GetPhoXiPointCloud::Request& req,
                                                       phoxi_camera_srvs::GetPhoXiPointCloud::Response& res)
{
  is_ok_ = false;
  sensor_msgs::PointCloud2 empty_cloud;
  receive_cloud_ = empty_cloud;

  phoxi_camera_srvs::PublishPointCloud publish_point_cloud;
  if (!start_publish_pointcloud_client_.call(publish_point_cloud))
  {
    ROS_ERROR_STREAM("Failed to start sensor !!");
    res.success = false;
    return res.success;
  }

  ros::Duration(interval_time_).sleep();

  int count = 0;
  while (receive_cloud_.data.size() == 0)
  {
    count++;
    if (count > timeout_)
    {
      ROS_ERROR_STREAM("Failed to receive sensor pointcloud !!");
      res.success = false;
      return res.success;
    }
    ros::Duration(interval_time_).sleep();
  }

  sensor_cloud_ = receive_cloud_;

  ros::Duration(interval_time_).sleep();

  if (!stop_publish_pointcloud_client_.call(publish_point_cloud))
  {
    ROS_ERROR_STREAM("Failed to stop sensor !!");
    res.success = false;
    return res.success;
  }

  is_ok_ = true;
  res.success = true;
  return res.success;
}

void GetPointCloudFromPhoXiCameraServer::publishPointCloud()
{
  if (is_ok_)
  {
    pointcloud_pub_.publish(sensor_cloud_);
  }
}
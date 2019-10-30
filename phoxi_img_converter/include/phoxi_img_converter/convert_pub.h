#ifndef CONVERT_PUB_H
#define CONVERT_PUB_H

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Header.h>

namespace convert_pub
{
class ConvertPub
{
public:
  ConvertPub(ros::NodeHandle& nh);
  void publish(void);

private:
  void updateImg(const sensor_msgs::ImageConstPtr& img_msg);
  void scaling(cv_bridge::CvImagePtr original_img, cv_bridge::CvImagePtr rescaled_img);
  void filtering(void);

private:
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Publisher img_pub_;
  image_transport::Subscriber img_sub_;

  bool flag_;
  std_msgs::Header header_;
  cv_bridge::CvImagePtr original_img_ptr_;
  cv_bridge::CvImagePtr rescaled_img_ptr_;
  sensor_msgs::ImagePtr converted_img_ptr_;
};
}  // namespace convert_pub

#endif
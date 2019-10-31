#include <phoxi_img_converter/convert_pub.h>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using convert_pub::ConvertPub;

// Class methods definitions
ConvertPub::ConvertPub(ros::NodeHandle& nh)
  : nh_(nh)
  , it_(nh)
  , original_img_ptr_(new cv_bridge::CvImage)
  , rescaled_img_ptr_(new cv_bridge::CvImage)
  , converted_img_ptr_(new sensor_msgs::Image)
{
  img_pub_ = it_.advertise("/converted_image", 1);
  img_sub_ = it_.subscribe("/photoneo_center/texture", 1, &ConvertPub::updateImg, this);
  flag_ = false;

  ROS_INFO_STREAM_ONCE("waiting image ...");
}

void ConvertPub::publish(void)
{
  if (flag_ == true)
  {
    // scale with the max value so that the range of pix val be from 0.0 to 1.0
    scalePixVal(original_img_ptr_, rescaled_img_ptr_);

    // filtering
    filterImg();
    ROS_INFO_STREAM_ONCE("filtering FINISHED");

    // // covert from gray to color
    cv::cvtColor(rescaled_img_ptr_->image, rescaled_img_ptr_->image, CV_GRAY2BGR);
    converted_img_ptr_ = cv_bridge::CvImage(std_msgs::Header(), "bgr8", rescaled_img_ptr_->image).toImageMsg();

    // publish
    converted_img_ptr_->header.seq = header_.seq;
    converted_img_ptr_->header.stamp = header_.stamp;
    converted_img_ptr_->header.frame_id = header_.frame_id;
    img_pub_.publish(*converted_img_ptr_);
    ROS_INFO_STREAM_ONCE("publishing ...");
  }
}

void ConvertPub::updateImg(const sensor_msgs::ImageConstPtr& img_msg)
{
  try
  {
    ROS_INFO_STREAM_ONCE("subscribed !");
    // copy an unscaled image as 32FC1 format
    original_img_ptr_ = cv_bridge::toCvCopy(img_msg, sensor_msgs::image_encodings::TYPE_32FC1);
    header_.seq = img_msg->header.seq;
    header_.stamp = img_msg->header.stamp;
    header_.frame_id = img_msg->header.frame_id;
    flag_ = true;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    flag_ = false;
  }
}

void ConvertPub::scalePixVal(cv_bridge::CvImagePtr original_img, cv_bridge::CvImagePtr rescaled_img)
{
  cv::Mat scaled_cv_img(original_img->image);
  cv::MatConstIterator_<float> it_begin = original_img->image.begin<float>(), it_end = original_img->image.end<float>();
  float max_val = *std::max_element(it_begin, it_end);
  original_img->image.convertTo(scaled_cv_img, CV_32FC1, 1.0 / max_val, 0);

  // copy
  rescaled_img->header.frame_id = original_img->header.frame_id;
  rescaled_img->header.stamp = original_img->header.stamp;
  rescaled_img->image = scaled_cv_img;
}

void ConvertPub::filterImg(void)
{
  ROS_INFO_STREAM_ONCE("filtering image ...");

  // equalize hist
  rescaled_img_ptr_->image.convertTo(rescaled_img_ptr_->image, CV_8UC1, 255.0 / 1.0, 0);
  cv::equalizeHist(rescaled_img_ptr_->image, rescaled_img_ptr_->image);
}

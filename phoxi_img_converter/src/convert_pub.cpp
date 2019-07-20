#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "convert_pub");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);

  image_transport::Publisher pub = it.advertise("/converted_image", 1);
  image_transport::Subscriber image_sub {it.subscribe("/photoneo_center/texture", 1,
                                                                                    std::function<void (const sensor_msgs::Image::ConstPtr&)>
    {
      [&](const auto& image)
      {
        cv_bridge::CvImagePtr cv_img_ptr;

        try {
          // copy an unscaled image as 32FC1 format
          cv_img_ptr = cv_bridge::toCvCopy(image, sensor_msgs::image_encodings::TYPE_32FC1);
        }
        catch (cv_bridge::Exception& e) {
          ROS_ERROR("cv_bridge exception: %s", e.what());
        }

        // original unscaled image
        cv::Mat cv_image_ori(cv_img_ptr->image.rows, cv_img_ptr->image.cols, cv_img_ptr->image.type());
        cv_image_ori = cv_img_ptr->image;

        // scaled image
        cv::Mat cv_image_scaled(cv_image_ori);

        // scale with the max value so that the range of pix val be from 0.0 to 1.0
        cv::MatConstIterator_<float> it = cv_image_ori.begin<float>(), it_end = cv_image_ori.end<float>();
        float max_val = *std::max_element(it, it_end);
        cv_image_ori.convertTo(cv_image_scaled, CV_32FC1, 1.0/max_val, 0);

        // equalize hist
        cv::Mat cv_image_gray(cv_image_scaled.rows, cv_image_scaled.cols, CV_8UC1);
        cv_image_scaled.convertTo(cv_image_gray, CV_8UC1, 255.0/1.0, 0);
        cv::Mat cv_image_hist_equ(cv_image_gray);
        cv::equalizeHist(cv_image_gray, cv_image_hist_equ);

        // covert to color
        cv::Mat cv_imageColor;
        cv::cvtColor(cv_image_hist_equ, cv_imageColor, CV_GRAY2BGR);

        // publisher
        sensor_msgs::ImagePtr rgb_image;
        rgb_image  = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cv_imageColor).toImageMsg();
        rgb_image->header.frame_id = image->header.frame_id;
        rgb_image->header.stamp = image->header.stamp;
        pub.publish(rgb_image);
      }
    }
                                                              )};

  ros::spin();
}

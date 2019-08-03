#include <ros/ros.h>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

ros::Publisher pub;

void callback(const sensor_msgs::Image image)
{
  sensor_msgs::CameraInfo cinfo;
  cinfo.header.stamp = image.header.stamp;
  cinfo.header.frame_id = "/camera_name";
  cinfo.height = 480;
  cinfo.width = 752;
  cinfo.distortion_model = "plumb_bob";
  cinfo.D = {-0.11862627596824302, 0.1330449495758574, 0.0012978747886444077, -0.002273816413316873, 0.0};
  cinfo.K = {2293.3324879074394, 0.0, 1041.4935095434566, 0.0, 2288.0886234815653, 857.6330096952366, 0.0, 0.0, 1.0};
  cinfo.R = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  cinfo.P = {2249.640869140625, 0.0, 1038.358544587485, 0.0, 0.0, 2259.18505859375, 860.459212312664, 0.0, 0.0, 0.0, 1.0, 0.0};
  cinfo.binning_x = 1;
  cinfo.binning_y = 1;
  cinfo.roi.x_offset = 0;
  cinfo.roi.y_offset = 0;
  cinfo.roi.height = 0;
  cinfo.roi.width = 0;
  cinfo.roi.do_rectify = false;

  pub.publish(cinfo);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "info_pub");

  ros::NodeHandle nh;

  pub = nh.advertise<sensor_msgs::CameraInfo>("/camera_info", 1);

  ros::Subscriber image_sub = nh.subscribe("/image0", 1, callback);

  ros::spin();
}

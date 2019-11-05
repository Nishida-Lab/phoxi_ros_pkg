#include <phoxi_img_converter/phoxi_img_converter.h>

using phoxi_img_converter::PhoxiImgConverter;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "phoxi_img_converter");
  ros::NodeHandle nh;

  PhoxiImgConverter convertor(nh);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    convertor.publish();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
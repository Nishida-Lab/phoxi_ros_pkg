#include <phoxi_img_converter/convert_pub.h>

using convert_pub::ConvertPub;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "convert_pub");
  ros::NodeHandle nh;

  ConvertPub convertor(nh);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    convertor.publish();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
#include "ros/ros.h"
#include <armadillo/brusher_packet.h>

void brusher_Callback(const armadillo::brusher_packet& msg)
{
  ROS_INFO("recevied brusher state: [%d]", msg.state);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "brusher");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("brusher_topic", 1000, brusher_Callback);

  ros::spin();

  return 0;
}
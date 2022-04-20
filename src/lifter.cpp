#include "ros/ros.h"
#include <armadillo/lifter_packet.h>

void lifter_Callback(const armadillo::lifter_packet& msg)
{
  ROS_INFO("I heard: [%d]", msg.direction);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "lifter");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("lifter_topic", 1000, lifter_Callback);
  ros::spin();

  return 0;
}
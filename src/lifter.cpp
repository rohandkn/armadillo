#include "ros/ros.h"
#include <armadillo/lifter_packet.h>

void lifter_Callback(const armadillo::lifter_packet& msg)
{
  ROS_INFO("lifter received dir: [%d]", msg.direction);
  ROS_INFO("lifter received speed: [%f]", msg.speed);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "lifter");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("lifter_topic", 1000, lifter_Callback);
  ros::spin();

  return 0;
}
#include "ros/ros.h"
#include <armadillo/driver_packet.h>

void driver_Callback(const armadillo::driver_packet& msg)
{
  ROS_INFO("I heard: [%d]", msg.direction);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "driver");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("driver_topic", 1000, driver_Callback);

  ros::spin();

  return 0;
}
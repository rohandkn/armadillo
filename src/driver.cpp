#include "ros/ros.h"
#include <armadillo/driver_packet.h>

void driver_Callback(const armadillo::driver_packet& msg)
{
  ROS_INFO("recevied driver dir: [%d]", msg.direction);
  ROS_INFO("recevied driver speed: [%f]", msg.speed);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "driver");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("driver_topic", 1000, driver_Callback);

  ros::spin();

  return 0;
}
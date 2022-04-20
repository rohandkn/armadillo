#include "ros/ros.h"
#include <armadillo/distance_sensor_packet.h>

void distance_sensor_Callback(const armadillo::distance_sensor_packet& msg)
{
  ROS_INFO("I heard: [%f]", msg.front_cliff);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navigation");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("distance_sensor", 1000, distance_sensor_Callback);

  ros::spin();

  return 0;
}
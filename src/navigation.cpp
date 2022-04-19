#include "ros/ros.h"
#include "std_msgs/String.h"

void distance_sensor_Callback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "distance_sensor");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("distance_sensor", 1000, distance_sensor_Callback);

  ros::spin();

  return 0;
}
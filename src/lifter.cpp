#include "ros/ros.h"
#include <armadillo/lifter_packet.h>
#include <wiringPi.h>

float speed = 0;
int direction = 0;

void lifter_Callback(const armadillo::lifter_packet& msg)
{
  if (msg.speed != speed || msg.direction != direction) {
    softPwmCreate(0,0,2);
    softPwmWrite(0,1);
    digitalWrite(2,1);
    digitalWrite(3,1);
  }

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
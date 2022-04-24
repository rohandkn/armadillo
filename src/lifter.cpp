#include "armadillo/lifter_obj.h"
#include "ros/ros.h"
#include "armadillo/lifter_packet.h" 
#include "wiringPi.h"
#include "softPwm.h"

float speed = 0;
int direction = 0;
lifter_obj* front_lifter = new lifter_obj(3, 2, 0);
lifter_obj* back_lifter = new lifter_obj(7, 6, 5);

void lifter_Callback(const armadillo::lifter_packet& msg) {
  front_lifter->set_speed(msg.direction_front, msg.speed_front);
  back_lifter->set_speed(msg.direction_back, msg.speed_back);
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "lifter");
  ros::NodeHandle n;
  wiringPiSetup();
  ros::Subscriber sub = n.subscribe("lifter_topic", 1000, lifter_Callback);
  ros::spin();

  return 0;
}

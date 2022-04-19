#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include <armadillo/distance_sensor_packet.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "distance_sensor");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<armadillo::distance_sensor_packet>("distance_sensor", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    armadillo::distance_sensor_packet pkt;

    pkt.distance_cm = .15;

    ROS_INFO("dndnd");

    chatter_pub.publish(pkt);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
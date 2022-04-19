#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include <armadillo/encoder_packet.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "encoder");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<armadillo::encoder_packet>("encoder", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    armadillo::encoder_packet pkt;

    pkt.rotations = 1234;

    ROS_INFO("encencenc");

    chatter_pub.publish(pkt);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
#include "ros/ros.h"

#include <sstream>
#include <armadillo/brusher_packet.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */

armadillo::brusher_packet* createBrusherPacket(){
  armadillo::brusher_packet* pkt = new armadillo::brusher_packet();
  pkt->state = armadillo::brusher_packet::ON;
  return pkt;
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "brusher");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<armadillo::brusher_packet>("brusher_topic", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    armadillo::brusher_packet* pkt = createBrusherPacket();

    chatter_pub.publish(*pkt);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
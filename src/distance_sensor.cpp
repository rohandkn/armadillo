#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include <armadillo/distance_sensor_packet.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */

armadillo::distance_sensor_packet* createSensorPacket(){
  armadillo::distance_sensor_packet* pkt = new armadillo::distance_sensor_packet();
  pkt->front_cliff = .15;
  return pkt;
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "distance_sensor");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<armadillo::distance_sensor_packet>("distance_sensor_topic", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    armadillo::distance_sensor_packet* pkt = createSensorPacket();

    chatter_pub.publish(*pkt);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
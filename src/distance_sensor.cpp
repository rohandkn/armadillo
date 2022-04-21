#include "ros/ros.h"
#include "std_msgs/String.h"
#include <wiringPiI2C.h>

#include <sstream>
#include <armadillo/distance_sensor_packet.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int front_cliff_fd = wiringPiI2CSetup(0x40);

armadillo::distance_sensor_packet* createSensorPacket(){
  armadillo::distance_sensor_packet* pkt = new armadillo::distance_sensor_packet();
  int hodist = wiringPiI2CReadReg8(front_cliff_fd,0x5e);
  int lodist = wiringPiI2CReadReg8(front_cliff_fd,0x5f);
  int rawdist = (hodist*16+lodist)/4;
  ROS_INFO("front cliff sensor value: [%d]", msg.rawdist);

 pkt->front_cliff = rawdist;
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
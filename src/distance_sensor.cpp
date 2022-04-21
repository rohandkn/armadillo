#include "ros/ros.h"
#include "std_msgs/String.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <sstream>
#include <armadillo/distance_sensor_packet.h>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int front_cliff_fd = wiringPiI2CSetup(0x40);
int middle_cliff_fd = wiringPiI2CSetup(0x40);
int back_cliff_fd = wiringPiI2CSetup(0x40);
int fave_1_fd = wiringPiI2CSetup(0x40);
int fave_r_fd = wiringPiI2CSetup(0x40);
int left_side_fd = wiringPiI2CSetup(0x40);
int right_side_fd = wiringPiI2CSetup(0x40);


float dist_calc(int fd){
  int hodist = wiringPiI2CReadReg8(fd,0x5e);
  int lodist = wiringPiI2CReadReg8(fd,0x5f);
  float rawdist = (hodist*16+lodist)/4;
  return rawdist;
}

armadillo::distance_sensor_packet* createSensorPacket(){
  armadillo::distance_sensor_packet* pkt = new armadillo::distance_sensor_packet();

  pkt->front_cliff = dist_calc(front_cliff_fd);
  pkt->middle_cliff = dist_calc(middle_cliff_fd);;
  pkt->back_cliff = dist_calc(back_cliff_fd);;
  pkt->face_l = dist_calc(fave_1_fd);
  pkt->face_r = dist_calc(fave_r_fd);
  pkt->left_side = dist_calc(left_side_fd);
  pkt->right_side = dist_calc(right_side_fd);

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

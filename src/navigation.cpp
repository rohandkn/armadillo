#include "ros/ros.h"
#include <armadillo/distance_sensor_packet.h>
#include <armadillo/encoder_packet.h>
#include <armadillo/brusher_packet.h>
#include <armadillo/driver_packet.h>
#include <armadillo/lifter_packet.h>
#include <chrono>
#include <thread>



/*void distance_sensor_Callback(const armadillo::distance_sensor_packet& msg)
{
  ROS_INFO("nav received front cliff sensor: [%f]", msg.front_cliff);
}

void encoder_Callback(const armadillo::encoder_packet& msg)
{
  ROS_INFO("nav received encoder useless information: [%f]", msg.rotations);
}*/

void sendBrusherPacket(int state, ros::Publisher brusher_pub){
  armadillo::brusher_packet* pkt = new armadillo::brusher_packet();
  pkt->state = state;
  brusher_pub.publish(*pkt);
}

armadillo::brusher_packet* createBrusherPacket(int state, ros::Publisher brusher_pub){
  armadillo::brusher_packet* pkt = new armadillo::brusher_packet();
  pkt->state = state;
  return pkt;
}


void sendDriverPacket(int direction, int duration, ros::Publisher driver_pub){
  armadillo::driver_packet* pkt = new armadillo::driver_packet();
  pkt->direction = direction;
  pkt->speed = 1.0;
  driver_pub.publish(*pkt);

  std::this_thread::sleep_for(std::chrono::milliseconds(duration));

  armadillo::driver_packet* pkt2 = new armadillo::driver_packet();
  pkt2->direction = armadillo::driver_packet::STOP;
  pkt2->speed = 1.0;
  ROS_INFO("SENT");
  driver_pub.publish(*pkt2);
}

void sendLifterPacket(int direction, int module, ros::Publisher lifter_pub){
  armadillo::lifter_packet* pkt = new armadillo::lifter_packet();
  pkt->direction =  direction;
  pkt->module =  module;
  pkt->speed =  1.0;
  lifter_pub.publish(*pkt);
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "navigation");
  ros::NodeHandle n;

  ros::Publisher driver_pub = n.advertise<armadillo::driver_packet>("driver_topic", 1000);
  ros::Publisher lifter_pub = n.advertise<armadillo::lifter_packet>("lifter_topic", 1000);
  ros::Publisher brusher_pub = n.advertise<armadillo::brusher_packet>("brusher_topic", 1000);


  //ros::Subscriber dist_sub = n.subscribe("distance_sensor_topic", 1000, distance_sensor_Callback);
  //ros::Subscriber enc_sub = n.subscribe("encoder_topic", 1000, encoder_Callback);
  //ros::Publisher brusher_pub = n.advertise<armadillo::brusher_packet>("brusher_topic", 1000);

  //ros::Rate loop_rate(10);

  //int count = 0;

  armadillo::brusher_packet* brusher_pkt = createBrusherPacket();
  
  brusher_pub.publish(*brusher_pkt);
  sendBrusherPacket(armadillo::brusher_packet::ON, brusher_pub);
  sendDriverPacket(armadillo::driver_packet::FORWARD, 100, driver_pub);
  sendLifterPacket(armadillo::lifter_packet::UP, armadillo::lifter_packet::FRONT, lifter_pub);

  ros::spin();





  return 0;
}

#include "ros/ros.h"
#include <armadillo/distance_sensor_packet.h>
#include <armadillo/encoder_packet.h>
#include <armadillo/brusher_packet.h>
#include <armadillo/driver_packet.h>
#include <armadillo/lifter_packet.h>
#include <chrono>
#include <thread>

ros::Publisher driver_pub;
ros::Publisher lifter_pub;
ros::Publisher brusher_pub;

/*void distance_sensor_Callback(const armadillo::distance_sensor_packet& msg)
{
  ROS_INFO("nav received front cliff sensor: [%f]", msg.front_cliff);
}

void encoder_Callback(const armadillo::encoder_packet& msg)
{
  ROS_INFO("nav received encoder useless information: [%f]", msg.rotations);
}*/

void sendBrusherPacket(int state){
  armadillo::brusher_packet* pkt = new armadillo::brusher_packet();
  pkt->state = state;
  brusher_pub.publish(*pkt);
}

void sendDriverPacket(int direction, int duration){
  armadillo::driver_packet* pkt = new armadillo::driver_packet();
  pkt->direction = direction;
  pkt->speed = 1.0;
  driver_pub.publish(*pkt);

  std::this_thread::sleep_for(std::chrono::milliseconds(duration));

  armadillo::driver_packet* pkt2 = new armadillo::driver_packet();
  pkt2->direction = armadillo::driver_packet::STOP;
  pkt2->speed = 1.0;
  driver_pub.publish(*pkt2);
}

void sendLifterPacket(int direction, int module){
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

  driver_pub = n.advertise<armadillo::driver_packet>("driver_topic", 1000);
  lifter_pub = n.advertise<armadillo::lifter_packet>("lifter_topic", 1000);
  brusher_pub = n.advertise<armadillo::brusher_packet>("brusher_topic", 1000);


  //ros::Subscriber dist_sub = n.subscribe("distance_sensor_topic", 1000, distance_sensor_Callback);
  //ros::Subscriber enc_sub = n.subscribe("encoder_topic", 1000, encoder_Callback);
  //ros::Publisher brusher_pub = n.advertise<armadillo::brusher_packet>("brusher_topic", 1000);

  //ros::Rate loop_rate(10);

  //int count = 0;

  //armadillo::brusher_packet* brusher_pkt = createBrusherPacket();
  
  //lifter_pub.publish(*lifter_pkt);
  sendBrusherPacket(armadillo::brusher_packet::ON);
  sendDriverPacket(armadillo::driver_packet::FORWARD, 100);
  sendLifterPacket(armadillo::lifter_packet::UP, armadillo::lifter_packet::FRONT);





  return 0;
}

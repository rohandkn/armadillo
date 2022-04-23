#include "ros/ros.h"
#include <armadillo/distance_sensor_packet.h>
#include <armadillo/encoder_packet.h>
#include <armadillo/brusher_packet.h>
#include <armadillo/driver_packet.h>
#include <armadillo/lifter_packet.h>


void distance_sensor_Callback(const armadillo::distance_sensor_packet& msg)
{
  ROS_INFO("nav received front cliff sensor: [%f]", msg.front_cliff);
}

void encoder_Callback(const armadillo::encoder_packet& msg)
{
  ROS_INFO("nav received encoder useless information: [%f]", msg.rotations);
}


armadillo::brusher_packet* createBrusherPacket(){
  armadillo::brusher_packet* pkt = new armadillo::brusher_packet();
  pkt->state = armadillo::brusher_packet::OFF;
  return pkt;
}
169.254.79.141
armadillo::driver_packet* createDriverPacket(){
  armadillo::driver_packet* pkt = new armadillo::driver_packet();
  pkt->direction = armadillo::driver_packet::BACK;
  return pkt;
}

armadillo::lifter_packet* createLifterPacket(){
  armadillo::lifter_packet* pkt = new armadillo::lifter_packet();
  pkt->direction =  armadillo::lifter_packet::DOWN;
  return pkt;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "navigation");
  ros::NodeHandle n;

  ros::Subscriber dist_sub = n.subscribe("distance_sensor_topic", 1000, distance_sensor_Callback);
  ros::Subscriber enc_sub = n.subscribe("encoder_topic", 1000, encoder_Callback);
  ros::Publisher brusher_pub = n.advertise<armadillo::brusher_packet>("brusher_topic", 1000);
  ros::Publisher driver_pub = n.advertise<armadillo::driver_packet>("driver_topic", 1000);
  ros::Publisher lifter_pub = n.advertise<armadillo::lifter_packet>("lifter_topic", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    armadillo::brusher_packet* brusher_pkt = createBrusherPacket();
    armadillo::lifter_packet* lifter_pkt = createLifterPacket();
    armadillo::driver_packet* driver_pkt = createDriverPacket();

    brusher_pub.publish(*brusher_pkt);
    driver_pub.publish(*driver_pkt);
    //lifter_pub.publish(*lifter_pkt);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }



  return 0;
}
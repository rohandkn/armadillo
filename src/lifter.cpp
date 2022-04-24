#include "ros/ros.h"
#include <armadillo/lifter_packet.h>
#include <wiringPi.h>
#include <softPwm.h>

float speed = 0;
int direction = 0;

void lifter_Callback(const armadillo::lifter_packet& msg)
{
  if (msg.speed != speed || msg.direction != direction) {
    softPwmStop(0);
    direction = msg.direction;
    speed = msg.speed;
    float scaledSpeed = 25 - (msg.speed/100.0)*23;
    //checks for hold signal
    
    if (msg.direction == armadillo::lifter_packet::HOLD){
      //sets duty cycle = 100%
      softPwmWrite(0,scaledSpeed);
      // enable signal
      digitalWrite(2,1);
    }
    else if (msg.direction == armadillo::lifter_packet::FREE) {
      // enable signal
      digitalWrite(2,0);
    }
    else{
      ROS_INFO("set speed to %f", scaledSpeed);
      softPwmCreate(0,0,scaledSpeed);
      softPwmWrite(0,scaledSpeed/2);
      //direction signal
      digitalWrite(3,msg.direction);
      // enable signal
      digitalWrite(2,1);
    }
  }

  ROS_INFO("lifter received dir: [%d]", msg.direction);
  ROS_INFO("lifter received speed: [%f]", msg.speed);
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

#include "ros/ros.h"
#include <armadillo/driver_packet.h>
#include "armadillo/driver_obj.h"
#include "wiringPi.h"
#include "softPwm.h"
float current_speed;
int enable_pin = 37;

driver_obj* front_left_drv;
void set_speed(float speed){
  softPwmStop(enable_pin);
      current_speed = speed;
      //float scaledSpeed = 25 - (speed/100.0)*23;
      ROS_INFO("set speed to %f", speed);
        softPwmCreate(enable_pin,0,200);
        softPwmWrite(enable_pin,speed);
}

void driver_Callback(const armadillo::driver_packet& msg)
{
  front_left_drv->set_dir(msg.direction);
  if (msg.speed != current_speed){
    set_speed(msg.speed);
  }
  ROS_INFO("recevied driver dir: [%d]", msg.direction);
  ROS_INFO("recevied driver speed: [%f]", msg.speed);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "driver");
  wiringPiSetup();
  front_left_drv = new driver_obj(24, 23);
  pinMode(enable_pin, PWM_OUTPUT);  
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("driver_topic", 1000, driver_Callback);

  ros::spin();

  return 0;
}

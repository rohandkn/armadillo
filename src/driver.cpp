#include "ros/ros.h"
#include <armadillo/driver_packet.h>
#include "armadillo/driver_obj.h"
#include "wiringPi.h"
#include "softPwm.h"

float current_speed;
int enable_pin = 40;

driver_obj* front_left_wheel;
driver_obj* front_right_wheel;
driver_obj* back_left_wheel;
driver_obj* back_right_wheel;

void set_speed(float speed){
  //softPwmStop(enable_pin);
      current_speed = speed;
      //float scaledSpeed = 25 - (speed/100.0)*23;
      ROS_INFO("set speed to %f", speed);
        softPwmCreate(enable_pin,0,100);
        softPwmWrite(enable_pin,(int) speed);
}

void set_wheel_dirs(int front_left, int front_right, int back_left, int back_right){
  front_left_wheel->set_dir(front_left);
  front_right_wheel->set_dir(front_right);
  back_left_wheel->set_dir(back_left);
  back_right_wheel->set_dir(back_right);
}

void set_bot_dir(int bot_dir){
  if (bot_dir == armadillo::driver_packet::FORWARD){
    ROS_INFO("forward");
    set_wheel_dirs(driver_obj::ccw, driver_obj::cw, driver_obj::ccw, driver_obj::cw);
  }
  else if (bot_dir == armadillo::driver_packet::BACKWARD){
    ROS_INFO("backward");
    set_wheel_dirs(driver_obj::cw, driver_obj::ccw, driver_obj::cw, driver_obj::ccw);
  }
  else if (bot_dir == armadillo::driver_packet::LEFT){
   ROS_INFO("left");
   set_wheel_dirs(driver_obj::cw, driver_obj::cw, driver_obj::ccw, driver_obj::ccw);
  }
  else if (bot_dir == armadillo::driver_packet::RIGHT){
   ROS_INFO("right");
   set_wheel_dirs(driver_obj::ccw, driver_obj::ccw, driver_obj::cw, driver_obj::cw);
  }
  else if (bot_dir == armadillo::driver_packet::STOP){
   ROS_INFO("stop"); 
   set_wheel_dirs(driver_obj::stop, driver_obj::stop, driver_obj::stop, driver_obj::stop);
  }

}

void driver_Callback(const armadillo::driver_packet& msg)
{
  for(int i = 0; i<2; i++){
   //softPwmStop(enable_pin);
  //need to pull enable high to set direction otherwise signal interference
   digitalWrite(enable_pin, 1);
   set_bot_dir(msg.direction);
  //restart speed after direction change
  //set_speed(current_speed);
digitalWrite(enable_pin, 1);
  }
  /*if (msg.speed != current_speed){
     softPwmStop(enable_pin);
     set_speed(msg.speed);
  }*/
  ROS_INFO("recevied driver dir: [%d]", msg.direction);
  ROS_INFO("recevied driver speed: [%f]", msg.speed);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "driver");
  wiringPiSetupPhys();
  pinMode(enable_pin, OUTPUT);
  digitalWrite(enable_pin, 1);
  front_left_wheel = new driver_obj(38, 7);
  back_left_wheel = new driver_obj(11, 13);
  front_right_wheel = new driver_obj(15, 19);
  back_right_wheel = new driver_obj(21, 23);
  digitalWrite(enable_pin, 0);

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("driver_topic", 1000, driver_Callback);

  ros::spin();

  return 0;
}

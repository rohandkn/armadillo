#include "ros/ros.h"
#include <armadillo/driver_packet.h>
#include "armadillo/driver_obj.h"
#include "wiringPi.h"
#include "softPwm.h"

float current_speed;
int enable_pin = 38;

driver_obj* front_left_wheel;
driver_obj* front_right_wheel;
driver_obj* back_left_wheel;
driver_obj* back_right_wheel;


void set_wheel_dirs(int front_left, int front_right, int back_left, int back_right){
  front_left_wheel->set_dir(front_left, 100);
  front_right_wheel->set_dir(front_right, 100);
  back_left_wheel->set_dir(back_left, 100);
  back_right_wheel->set_dir(back_right, 100);
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

  set_bot_dir(msg.direction);
  ROS_INFO("DRIVER MOVING: [%d]", msg.direction);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "driver");
  wiringPiSetupPhys();
  pinMode(enable_pin, OUTPUT);
  digitalWrite(enable_pin, 1);
  // direction, clk, en
  front_left_wheel = new driver_obj(40, 7, 38);
  front_right_wheel = new driver_obj(11, 13, 38);
  back_left_wheel = new driver_obj(15, 19, 38);
  back_right_wheel = new driver_obj(21, 23, 38);
 //digitalWrite(enable_pin, 0);

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("driver_topic", 1000, driver_Callback);

  ros::spin();

  return 0;
}

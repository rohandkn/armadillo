#include "armadillo/lifter_obj.h"
#include "ros/ros.h"
#include "armadillo/lifter_packet.h" 
#include "wiringPi.h"
#include "softPwm.h"

lifter_obj :: lifter_obj(int dir_p, int enable_p, int speed_p)
	: dir_pin(dir_p), enable_pin(enable_p), speed_pin(speed_p)
{
  pinMode(speed_pin, PWM_OUTPUT);
  pinMode(enable_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
}

void lifter_obj :: set_speed_and_dir(int dir, float speed){
    softPwmStop(speed_pin);
    float scaledSpeed = 25 - (speed/100.0)*23;
    //checks for hold signal
    
    if (dir == hold){
      //sets duty cycle = 100%
      softPwmWrite(speed_pin,scaledSpeed);
      // enable signal
      digitalWrite(enable_pin,1);
    }
    else if (dir == free) {
      // enable signal
      digitalWrite(enable_pin,0);
    }
    else {
      ROS_INFO("set speed to %f", scaledSpeed);
      softPwmCreate(speed_pin,0,scaledSpeed);
      softPwmWrite(speed_pin,scaledSpeed/2);
      //direction signal
      if (dir == cc) {
      	digitalWrite(dir_pin,1);
      }

      else if (dir == ccw) {
      	digitalWrite(dir_pin,0);
      }
      // enable signal
      digitalWrite(enable_pin,1);
    }
	  ROS_INFO("lifter object received dir: [%d]", dir);
	  ROS_INFO("lifter object received speed: [%f]", speed);
}

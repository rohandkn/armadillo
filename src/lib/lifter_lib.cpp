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

void lifter_obj :: set_speed(int dir, float speed){
	if (speed != current_speed || dir != current_dir) {
	    softPwmStop(speed_pin);
	    current_dir = dir;
	    current_speed = speed;
	    float scaledSpeed = 25 - (speed/100.0)*23;
	    //checks for hold signal
	    
	    if (dir == armadillo::lifter_packet::HOLD){
	      //sets duty cycle = 100%
	      softPwmWrite(speed_pin,scaledSpeed);
	      // enable signal
	      digitalWrite(enable_pin,1);
	    }
	    else if (dir == armadillo::lifter_packet::FREE) {
	      // enable signal
	      digitalWrite(enable_pin,0);
	    }
	    else {
	      ROS_INFO("set speed to %f", scaledSpeed);
	      softPwmCreate(speed_pin,0,scaledSpeed);
	      softPwmWrite(speed_pin,scaledSpeed/2);
	      //direction signal
	      digitalWrite(dir_pin,dir);
	      // enable signal
	      digitalWrite(enable_pin,1);
	     }
	  ROS_INFO("lifter received dir: [%d]", dir);
	  ROS_INFO("lifter received speed: [%f]", speed);
	  }
}

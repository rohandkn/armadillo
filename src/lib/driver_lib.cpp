#include "armadillo/driver_obj.h" 
#include <chrono>
#include <thread> 
#include <wiringPi.h>
#include <softPwm.h>
#include <ros/ros.h>


driver_obj :: driver_obj(int dir_p, int clk_p, int enable_p)
	: dir_pin(dir_p), clk_pin(clk_p), enable_pin(enable_p)
{
  pinMode(clk_pin, OUTPUT);
  // put this in driver.cpp pinMode(enable_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(enable_pin, OUTPUT);
  digitalWrite(dir_pin,1);
  pulse_clk(4);
}

void driver_obj :: set_speed(float speed){
  //softPwmStop(enable_pin);
      current_speed = speed;
      //float scaledSpeed = 25 - (speed/100.0)*23;
      ROS_INFO("set speed to %f", speed);
      softPwmCreate(enable_pin,0,100);
      softPwmWrite(enable_pin,(int) speed);
}

void driver_obj :: pulse_clk(int pulses){

	 for(int i = 0; i<pulses; i++){
   	softPwmStop(enable_pin);
  //need to pull enable high to set direction otherwise signal interference
   	digitalWrite(enable_pin, 1);
		digitalWrite(clk_pin,0);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		digitalWrite(clk_pin,1);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //restart speed after direction change
    set_speed(current_speed);
  }
  
}

void driver_obj :: set_dir(int dir, int speed){
pulse_clk(2);
if (speed != current_speed){
     softPwmStop(enable_pin);
     set_speed(speed);
}
return;
ROS_INFO("not rreached");
if (dir != current_dir) {
	    
			if (dir == driver_obj::cw){
				if(current_dir == driver_obj::ccw){
					pulse_clk(13);
				}
				else if(current_dir == driver_obj::stop){
					pulse_clk(6);
				}
			} 
			if (dir == driver_obj::ccw){
				if(current_dir == driver_obj::cw){
					pulse_clk(3);
				}
				else if(current_dir == driver_obj::stop){
					pulse_clk(9);
				}
			} 
			if (dir == driver_obj::stop){
				if(current_dir == driver_obj::ccw){
					pulse_clk(7);
				}
				else if(current_dir == driver_obj::cw){
					pulse_clk(10);
				}
			} 

		current_dir = dir;
          digitalWrite(clk_pin,0);	    
	  ROS_INFO("diver received dir: [%d]", dir);
	  }
}

#include "armadillo/driver_obj.h"
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include <softPwm.h>
#include <ros/ros.h>

driver_obj :: driver_obj(int dir_p, int clk_p)
	: dir_pin(dir_p), clk_pin(clk_p)
{
  pinMode(clk_pin, OUTPUT);
  // put this in driver.cpp pinMode(enable_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  digitalWrite(dir_pin,1);
  pulse_clk(4);
}

void driver_obj :: pulse_clk(int pulses){
	for (int i = 0; i<pulses; i++){
		digitalWrite(clk_pin,0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		digitalWrite(clk_pin,1);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void driver_obj :: set_dir(int dir){
if (dir != current_dir) {
	    
			if (dir == driver_obj::cw){
				if(current_dir == driver_obj::ccw){
					pulse_clk(8);
				}
				else if(current_dir == driver_obj::stop){
					pulse_clk(1);
				}
			} 
			if (dir == driver_obj::ccw){
				if(current_dir == driver_obj::cw){
					pulse_clk(8);
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
					pulse_clk(15);
				}
			} 

		current_dir = dir;
          digitalWrite(clk_pin,0);	    
	  ROS_INFO("diver received dir: [%d]", dir);
	  }
}

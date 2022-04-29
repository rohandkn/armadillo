#include "armadillo/lifter_obj.h"
#include "ros/ros.h"
#include "armadillo/lifter_packet.h" 
#include "wiringPi.h"
#include "softPwm.h"
#include <chrono>
#include <thread>

int set_speed = 20;
lifter_obj* front_lifter;
lifter_obj* back_lifter;

void moveStepperFixed(lifter_obj* first_lifter, int first_direction, 
                                    lifter_obj* second_lifter, int second_direction) {
  if (first_lifter != nullptr) first_lifter->set_speed_and_dir(first_direction, set_speed);
  if (second_lifter != nullptr) second_lifter->set_speed_and_dir(second_direction, set_speed);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  if (first_lifter != nullptr) first_lifter->set_speed_and_dir(lifter_obj::hold, set_speed);
  if (second_lifter != nullptr) second_lifter->set_speed_and_dir(lifter_obj::hold, set_speed);
}

void handleLiftingLogic(int module, int direction) {
  if (module == armadillo::lifter_packet::FRONT) {
    if (direction == armadillo::lifter_packet::UP) {
      moveStepperFixed(front_lifter, lifter_obj::cc, nullptr, -1);
    }

    else if (direction == armadillo::lifter_packet::DOWN) {
      moveStepperFixed(front_lifter, lifter_obj::ccw, nullptr, -1);
    }

    else if (direction == armadillo::lifter_packet::HOLD) {
      front_lifter->set_speed_and_dir(lifter_obj::hold, set_speed);
    }

    else if (direction == armadillo::lifter_packet::FREE) {
      front_lifter->set_speed_and_dir(lifter_obj::free, set_speed);
    }
  }

  else if (module == armadillo::lifter_packet::MIDDLE) {
    if (direction == armadillo::lifter_packet::UP) {
      moveStepperFixed(front_lifter, lifter_obj::cc, back_lifter, lifter_obj::cc);
    }

    else if (direction == armadillo::lifter_packet::DOWN) {
      moveStepperFixed(front_lifter, lifter_obj::ccw, back_lifter, lifter_obj::ccw);
    }

    else if (direction == armadillo::lifter_packet::HOLD) {
      front_lifter->set_speed_and_dir(lifter_obj::hold, set_speed);
      back_lifter->set_speed_and_dir(lifter_obj::hold, set_speed);
    }

    else if (direction == armadillo::lifter_packet::FREE) {
      front_lifter->set_speed_and_dir(lifter_obj::free, set_speed);
      back_lifter->set_speed_and_dir(lifter_obj::free, set_speed);
    }
  }

  else if (module == armadillo::lifter_packet::BACK) {
    if (direction == armadillo::lifter_packet::UP) {
      moveStepperFixed(back_lifter, lifter_obj::cc, nullptr, -1);
    }

    else if (direction == armadillo::lifter_packet::DOWN) {
      moveStepperFixed(back_lifter, lifter_obj::ccw, nullptr, -1);
    }

    else if (direction == armadillo::lifter_packet::HOLD) {
      back_lifter->set_speed_and_dir(lifter_obj::hold, set_speed);
    }

    else if (direction == armadillo::lifter_packet::FREE) {
      back_lifter->set_speed_and_dir(lifter_obj::free, set_speed);
    }
  }
}

void lifter_Callback(const armadillo::lifter_packet& msg) {
  handleLiftingLogic(msg.module, msg.direction);
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "lifter");
  wiringPiSetupPhys();
  front_lifter = new lifter_obj(15, 13, 11);
  back_lifter = new lifter_obj(7, 22, 18);
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("lifter_topic", 1000, lifter_Callback);
  ros::spin();

  return 0;
}

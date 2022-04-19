cmake_minimum_required(VERSION 2.8.3)
project(armadillo)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs genmsg)

## Declare ROS messages and services
add_message_files(FILES distance_sensor_packet.msg)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(distance_sensor src/distance_sensor.cpp)
target_link_libraries(distance_sensor ${catkin_LIBRARIES})
add_dependencies(distance_sensor armadillo_generate_messages_cpp)
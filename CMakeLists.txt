cmake_minimum_required(VERSION 2.8.3)
project(armadillo)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs genmsg)

## Declare ROS messages and services
add_message_files(FILES distance_sensor_packet.msg)
add_message_files(FILES encoder_packet.msg)
add_message_files(FILES lifter_packet.msg)


## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


##Publishers
add_executable(distance_sensor src/distance_sensor.cpp)
target_link_libraries(distance_sensor ${catkin_LIBRARIES})
add_dependencies(distance_sensor armadillo_generate_messages_cpp)

add_executable(encoder src/encoder.cpp)
target_link_libraries(encoder ${catkin_LIBRARIES})
add_dependencies(encoder armadillo_generate_messages_cpp)

##Subscribers
add_executable(navigation src/navigation.cpp)
target_link_libraries(navigation ${catkin_LIBRARIES})
add_dependencies(navigation armadillo_generate_messages_cpp)

##Subscribers
add_executable(lifter src/lifter.cpp)
target_link_libraries(lifter ${catkin_LIBRARIES})
add_dependencies(lifter armadillo_generate_messages_cpp)
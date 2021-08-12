cmake_minimum_required(VERSION 3.0.2)
project(depth_sub)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)
find_package(OpenCV REQUIRED)
find_package(realsense2 REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES depth_sub
#  CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${realsense_INCLUDE_DIR}
)
add_executable(depth_sub src/depth_sub.cpp)

target_link_libraries(depth_sub
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${realsense2_LIBRARY}
)

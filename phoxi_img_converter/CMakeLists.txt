cmake_minimum_required(VERSION 2.8.3)
project(phoxi_img_converter)

SET(CMAKE_CXX_FLAGS "-std=c++14 -O2 -g -Wall ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  message_generation
  roscpp
  rospy
  sensor_msgs
  std_msgs
  image_transport
)

find_package(OpenCV 3  REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAG "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
INCLUDE_DIRS
LIBRARIES ${PROJECT_NAME}
CATKIN_DEPENDS cv_bridge image_transport roscpp rospy sensor_msgs std_msgs
DEPENDS
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_LIBRARIES}
)


add_executable(convert_pub src/convert_pub.cpp)
target_link_libraries(convert_pub
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

cmake_minimum_required(VERSION 2.8.3)
project(phoxi_camera_info_pub)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  )

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAG "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  )


add_executable(info_pub src/info_pub.cpp)
target_link_libraries(info_pub
  ${catkin_LIBRARIES}
  )

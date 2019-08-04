cmake_minimum_required(VERSION 2.8.3)
project(phoxi_camera_info_pub)

set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -g -Wall ${CMAKE_CXX_FLAGS}")

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

catkin_package(
  CATKIN_DEPENDS
    roscpp
    rospy
    sensor_msgs
    std_msgs
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
  )

add_executable(info_pub src/info_pub.cpp)
target_link_libraries(info_pub
  ${catkin_LIBRARIES}
  )

###########
# Install #
###########

set(EXEC_FILES
  info_pub
  )
# Install executables
foreach(nodes ${EXEC_FILES})
  install(TARGETS ${nodes}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endforeach()

set(DIRECTORIES
  ./launch/
  )
# Install all files
foreach(dirs ${DIRECTORIES})
  install(DIRECTORY ${dirs}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dirs})
endforeach()

#############
## Testing ##
#############

if (CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)

  set(DIRECTORIES
    ./launch/
    )

  foreach(dirs ${DIRECTORIES})
    roslaunch_add_file_check(${dirs})
  endforeach()
endif()


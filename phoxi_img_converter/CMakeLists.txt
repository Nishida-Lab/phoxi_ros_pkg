cmake_minimum_required(VERSION 2.8.3)
project(phoxi_img_converter)

set(CMAKE_CXX_FLAGS "-std=c++14 -O2 -g -Wall ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  message_generation
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

find_package(OpenCV REQUIRED)

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
  CATKIN_DEPENDS
    cv_bridge
    image_transport
    message_generation
    roscpp
    rospy
    sensor_msgs
    std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_LIBRARIES}
)

add_executable(convert_pub 
  src/convert_pub_node.cpp
  src/convert_pub.cpp)
target_link_libraries(convert_pub
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)

###########
# Install #
###########

set(EXEC_FILES
  convert_pub
  )
# Install executables
foreach(nodes ${EXEC_FILES})
  install(TARGETS ${nodes}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endforeach()

set(DIRECTORIES
  ./launch/
  )
# Install other files
foreach(dirs ${DIRECTORIES})
  install(DIRECTORY ${dirs}
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

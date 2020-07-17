cmake_minimum_required(VERSION 2.8.3)
project(phoxi_bringup)

find_package(catkin REQUIRED COMPONENTS
  phoxi_camera
  phoxi_camera_srvs
  roscpp
  sensor_msgs
  std_srvs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
    phoxi_camera_srvs
    roscpp
    sensor_msgs
    std_srvs
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(phoxi_camera_pointcloud_pub_server
  src/phoxi_camera_pointcloud_pub_server.cpp
  src/phoxi_camera_pointcloud_pub_server_node.cpp
)

target_link_libraries(phoxi_camera_pointcloud_pub_server
  ${catkin_LIBRARIES}
)

add_executable(get_pointcloud_from_phoxi_camera_server
  src/get_pointcloud_from_phoxi_camera_server.cpp
  src/get_pointcloud_from_phoxi_camera_server_node.cpp
)

target_link_libraries(get_pointcloud_from_phoxi_camera_server
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

set(EXEC_FILES
  phoxi_camera_pointcloud_pub_server
  get_pointcloud_from_phoxi_camera_server
)

foreach(nodes ${EXEC_FILES})
  install(TARGETS ${nodes}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endforeach()

# Python scripts
set(PYTHON_SCRIPTS
  scripts/phoxi_get_frame.py
)
foreach(scripts ${PYTHON_SCRIPTS})
  catkin_install_python(PROGRAMS ${scripts}
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endforeach()

set(DIRECTORIES
  ./launch/
  ./config/
  )
# other files
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

cmake_minimum_required(VERSION 2.8.3)
project(sensor_frame_broadcaster)

find_package(catkin REQUIRED COMPONENTS
  rospy
  tf
  tf2_ros
  geometry_msgs
  cmake_modules
  )

catkin_package(
  CATKIN_DEPENDS
  rospy
  tf
  tf2_ros
  geometry_msgs
  )

###########
# Install #
###########
# Python scripts
set(PYTHON_SCRIPTS
  scripts/sensor_frame_broadcaster.py
)
foreach(scripts ${PYTHON_SCRIPTS})
  catkin_install_python(PROGRAMS ${scripts}
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endforeach(scripts)


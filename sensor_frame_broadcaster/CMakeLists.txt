cmake_minimum_required(VERSION 2.8.3)
project(sensor_frame_broadcaster)

find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  geometry_msgs
  rospy
  tf
  tf2_ros
)

catkin_package(
  CATKIN_DEPENDS
    geometry_msgs
    rospy
    tf
    tf2_ros
)

###########
# Install #
###########
# Python scripts
set(PYTHON_SCRIPTS
  scripts/${PROJECT_NAME}.py
)
foreach(scripts ${PYTHON_SCRIPTS})
  catkin_install_python(PROGRAMS ${scripts}
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endforeach()


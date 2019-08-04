cmake_minimum_required(VERSION 2.8.3)
project(phoxi_bringup)

find_package(catkin REQUIRED
)

catkin_package()

#############
## Install ##
#############

set(DIRECTORIES
  ./launch/
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

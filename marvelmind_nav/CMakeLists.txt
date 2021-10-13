cmake_minimum_required(VERSION 3.5)
project(marvelmind_nav)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(marvelmind_interfaces REQUIRED)
find_package(rmw REQUIRED) #QoS

# Declare includes and libraries
include_directories(include)
ament_export_include_directories(include)
add_library(marvelmind_nav_lib
  src/marvelmind_hedge.c
  src/marvelmind_api.c
  src/marvelmind_devices.c
  src/marvelmind_example.c
  src/marvelmind_pos.c
  src/marvelmind_utils.c
)

# Executables
add_executable(marvelmind_nav src/marvelmind_navigation.cpp
                              src/marvelmind_hedge.c)
ament_target_dependencies(marvelmind_nav rclcpp std_msgs marvelmind_interfaces)

# add_executable(talker src/publisher_member_function.cpp
# 			       src/marvelmind_hedge.c
#                               src/marvelmind_api.c
#                               src/marvelmind_devices.c
#                               src/marvelmind_example.c
#                               src/marvelmind_pos.c
#                               src/marvelmind_utils.c)
# ament_target_dependencies(talker rclcpp std_msgs)

add_executable(wake_beacon src/wake_beacon_node.cpp
			       src/marvelmind_hedge.c
                              src/marvelmind_api.c
                              src/marvelmind_devices.c
                              src/marvelmind_example.c
                              src/marvelmind_pos.c
                              src/marvelmind_utils.c)
ament_target_dependencies(wake_beacon rclcpp std_msgs)

add_executable(sleep_beacon src/sleep_beacon_node.cpp
			       src/marvelmind_hedge.c
                              src/marvelmind_api.c
                              src/marvelmind_devices.c
                              src/marvelmind_example.c
                              src/marvelmind_pos.c
                              src/marvelmind_utils.c)
ament_target_dependencies(sleep_beacon rclcpp std_msgs)

#ament_target_dependencies(talker rclcpp std_msgs)
target_link_libraries(marvelmind_nav
  ${rclcpp_lifecycle_LIBRARIES}
  ${std_msgs_LIBRARIES}
)


# Installation
install(TARGETS
  marvelmind_nav
  sleep_beacon
  wake_beacon
  DESTINATION lib/${PROJECT_NAME})


install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

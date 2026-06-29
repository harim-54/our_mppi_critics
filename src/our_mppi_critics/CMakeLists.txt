cmake_minimum_required(VERSION 3.8)
project(our_mppi_critics)

find_package(ament_cmake REQUIRED)
find_package(nav2_mppi_controller REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(sensor_msgs REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIR}
)

add_library(our_mppi_critics SHARED
  src/skid_critic.cpp
  src/slope_critic.cpp
)

target_include_directories(our_mppi_critics PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(our_mppi_critics
  nav2_mppi_controller
  pluginlib
  rclcpp
  sensor_msgs
)

target_link_libraries(our_mppi_critics
  Eigen3::Eigen
)

install(TARGETS our_mppi_critics
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include
)

install(FILES critics.xml
  DESTINATION share/${PROJECT_NAME}
)

pluginlib_export_plugin_description_file(nav2_mppi_controller critics.xml)

ament_package()
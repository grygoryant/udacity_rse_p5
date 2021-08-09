#!/bin/sh

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
export TURTLEBOT_GAZEBO_WORLD_FILE="~/catkin_ws/src/map/my_world.world" &&
roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 10

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
export TURTLEBOT_GAZEBO_MAP_FILE="~/catkin_ws/src/map/env_map.yaml" &&
roslaunch turtlebot_gazebo amcl_demo.launch" &

sleep 5

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 25

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
rosparam load ~/catkin_ws/src/pick_objects/param/locations.yaml &&
rosrun add_markers add_markers_dummy &&
echo Press any key... &&
read key" &
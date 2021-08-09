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

sleep 10

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
roslaunch turtlebot_rviz_launchers home_service_navigation.launch" &

sleep 20

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
rosparam load ~/catkin_ws/src/pick_objects/param/locations.yaml &&
rosrun add_markers add_markers;
echo Press any key... &&
read key" &

sleep 2

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
rosrun pick_objects pick_objects;
echo Press any key... &&
read key" &

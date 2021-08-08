#!/bin/sh

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
export TURTLEBOT_GAZEBO_WORLD_FILE="~/catkin_ws/src/map/my_world.world" &&
roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 10

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
roslaunch turtlebot_gazebo gmapping_demo.launch" &

sleep 5

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 10

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
roslaunch turtlebot_teleop keyboard_teleop.launch" &

#!/bin/sh

xterm -e "source devel/setup.bash &&
export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/map/my_world.world" &&
roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 10

xterm -e "source devel/setup.bash &&
export TURTLEBOT_GAZEBO_MAP_FILE="$(pwd)/src/map/env_map.yaml" &&
roslaunch turtlebot_gazebo amcl_demo.launch" &

sleep 5

xterm -e "source devel/setup.bash &&
roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 25

xterm -e "source devel/setup.bash &&
rosparam load $(rospack find pick_objects)/param/locations.yaml &&
rosrun add_markers add_markers_dummy &&
echo Press any key... &&
read key" &

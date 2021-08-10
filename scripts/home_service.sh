#!/bin/sh

xterm -e "source devel/setup.bash &&
export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/map/my_world.world" &&
roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 10

xterm -e "source devel/setup.bash &&
export TURTLEBOT_GAZEBO_MAP_FILE="$(pwd)/src/map/env_map.yaml" &&
roslaunch turtlebot_gazebo amcl_demo.launch" &

sleep 10

xterm -e "source devel/setup.bash &&
export HOME_SERVICE_RVIZ_CONF="$(pwd)/src/rvizConfig/home_service_conf.rviz" &&
roslaunch add_markers home_service_navigation.launch" &

sleep 20

xterm -e "source devel/setup.bash &&
rosparam load $(rospack find pick_objects)/param/locations.yaml &&
rosrun add_markers add_markers;
echo Press any key... &&
read key" &

sleep 2

xterm -e "source devel/setup.bash &&
rosrun pick_objects pick_objects;
echo Press any key... &&
read key" &

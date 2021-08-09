#!/bin/sh

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
export TURTLEBOT_GAZEBO_WORLD_FILE="$(pwd)/src/map/my_world.world" &&
roslaunch turtlebot_gazebo turtlebot_world.launch" & 

sleep 10

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
rosparam set /slam_gmapping/iterations 10 &&
rosparam set /slam_gmapping/linearUpdate 0.05 &&
rosparam set /slam_gmapping/angularUpdate 0.1 &&
rosparam set /slam_gmapping/map_update_interval 0.25 &&
rosparam set /slam_gmapping/srr 0.01 &&
rosparam set /slam_gmapping/srt 0.01 &&
rosparam set /slam_gmapping/str 0.02 &&
rosparam set /slam_gmapping/stt 0.02 &&
roslaunch turtlebot_gazebo gmapping_demo.launch" &

sleep 5

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 10

xterm -e "cd ~/catkin_ws/ &&
source devel/setup.bash &&
roslaunch turtlebot_teleop keyboard_teleop.launch" &

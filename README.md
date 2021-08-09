# Home Service Robot

The final project of the Udacity Robotic Software Engineer Nanodegree.

The goal of this project is to implement home service robot using ROS, that will be able to pick up and drop off the payload in the given locations of the environment.
In order to achieve that, several tasks should be completed:

1. Map the environment using existing environment and ROS SLAM stack;
2. Try to navigate the resulting map using 2D Nav goal;
3. Implement `pick_objects` node to move to the desired pick up and drop off locations;
4. Implement `add_markers` node to vizualize the simulated payload;
5. Connect `pick_objects` and `add_markers` nodes in order to provide full home service robot functionality.

The following ROS packages were used:
* [gmapping](http://wiki.ros.org/gmapping) - with this package you can perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras;
* [turtlebot_teleop](http://wiki.ros.org/turtlebot_teleop) - manual robot control with a keyboard;
* [turtlebot_rviz_launchers](http://wiki.ros.org/turtlebot_rviz_launchers) - loading preconfigured RViz workspaces for turtlebot;
* [turtlebot_gazebo](http://wiki.ros.org/turtlebot_gazebo) - deploying turtlebot in any world.

The following packages and directories were created:
* `map` - Gazebo world file and environment map;
* `scripts` - bash scripts for quick tasks launches;
* `rvizConfig` - rviz config file for home service robot vizualization;
* `pick_objects` - package for pick up and drop off zones navigation;
* `pick_objects/param` - config file with parameters for setting pick up and drop off locations;
* `add_markers` - package for payload vizualization.

The following scripts inside `scripts` directory were implemented:
* `test_slam.sh` - testing SLAM and creating the environment map;
* `test_navigation.sh` - testing 2D Nav goal and robot navigation;
* `pick_objects.sh` - testing robot navigation using location publishing;
* `add_markers.sh` - testing payload vizualization;
* `home_service.sh`- running home service robot and vizualizing payload picking up and dropping off.

All above scripts should be run from the workspace directory.

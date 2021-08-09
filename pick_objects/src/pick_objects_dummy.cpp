#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
    // Initialize the simple_navigation_goals node
    ros::init(argc, argv, "pick_objects");

    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);
    ros::NodeHandle node_handle;
    
    // Wait 5 sec for move_base action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }
    
    move_base_msgs::MoveBaseGoal goal;

    // set up the frame parameters
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    
    node_handle.getParam("/pick_up/tx", goal.target_pose.pose.position.x);
    node_handle.getParam("/pick_up/ty", goal.target_pose.pose.position.y);
    node_handle.getParam("/pick_up/tz", goal.target_pose.pose.position.z);
    node_handle.getParam("/pick_up/qx", goal.target_pose.pose.orientation.x);
    node_handle.getParam("/pick_up/qy", goal.target_pose.pose.orientation.y);
    node_handle.getParam("/pick_up/qz", goal.target_pose.pose.orientation.z);
    node_handle.getParam("/pick_up/qw", goal.target_pose.pose.orientation.w);

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending pick-up location");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        ROS_INFO("Reached pick-up location");
        ros::Duration(5.0).sleep();
    }
    else {
        ROS_INFO("The base failed to move");
        return 0;
    }

    goal.target_pose.header.stamp = ros::Time::now();
    
    node_handle.getParam("/drop_off/tx", goal.target_pose.pose.position.x);
    node_handle.getParam("/drop_off/ty", goal.target_pose.pose.position.y);
    node_handle.getParam("/drop_off/tz", goal.target_pose.pose.position.z);
    node_handle.getParam("/drop_off/qx", goal.target_pose.pose.orientation.x);
    node_handle.getParam("/drop_off/qy", goal.target_pose.pose.orientation.y);
    node_handle.getParam("/drop_off/qz", goal.target_pose.pose.orientation.z);
    node_handle.getParam("/drop_off/qw", goal.target_pose.pose.orientation.w);
    
    ROS_INFO("Sending drop-off location");
    ac.sendGoal(goal);
       
    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
        ROS_INFO("Reached drop-off location");
    }
    else {
        ROS_INFO("The base failed to move");
    }   
    
    ros::Duration(5.0).sleep();
       
    return 0;
}

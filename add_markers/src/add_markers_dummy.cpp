#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/Char.h>

char robot_state = 'h'; // h -> p -> g -> d

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle node_handle;
    ros::Rate r(1);
    ros::Publisher marker_pub = node_handle.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    uint32_t shape = visualization_msgs::Marker::CUBE;

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    
    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
 
    while (ros::ok())
    {   
	    ros::spinOnce();
        
        marker.header.stamp = ros::Time::now();
        
        switch(robot_state) {
        case 'h':
            ROS_INFO("Heading to pick-up location");
            // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
            marker.action = visualization_msgs::Marker::ADD;

            // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
            node_handle.getParam("/pick_up/tx", marker.pose.position.x);
            node_handle.getParam("/pick_up/ty", marker.pose.position.y);
            node_handle.getParam("/pick_up/tz", marker.pose.position.z);
            node_handle.getParam("/pick_up/qx", marker.pose.orientation.x);
            node_handle.getParam("/pick_up/qy", marker.pose.orientation.y);
            node_handle.getParam("/pick_up/qz", marker.pose.orientation.z);
            node_handle.getParam("/pick_up/qw", marker.pose.orientation.w);
            robot_state = 'p';
            break;
            
        case 'p':
            ros::Duration(5.0).sleep();
            ROS_INFO("Hiding pick-up location");
            marker.action = visualization_msgs::Marker::DELETE;
            robot_state = 'g';
            break;
            
        case 'g':
            ros::Duration(5.0).sleep();
            ROS_INFO("Showing drop-off location");
            // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
            marker.action = visualization_msgs::Marker::ADD;

            // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
            node_handle.getParam("/drop_off/tx", marker.pose.position.x);
            node_handle.getParam("/drop_off/ty", marker.pose.position.y);
            node_handle.getParam("/drop_off/tz", marker.pose.position.z);
            node_handle.getParam("/drop_off/qx", marker.pose.orientation.x);
            node_handle.getParam("/drop_off/qy", marker.pose.orientation.y);
            node_handle.getParam("/drop_off/qz", marker.pose.orientation.z);
            node_handle.getParam("/drop_off/qw", marker.pose.orientation.w);
            robot_state = 'd';
            break;
        
        default: break;
        }
        
        while (marker_pub.getNumSubscribers() < 1) {
            if (!ros::ok()) {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            sleep(1);
        }
        marker_pub.publish(marker);

        r.sleep();
    }
}

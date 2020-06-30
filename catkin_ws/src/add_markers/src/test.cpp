#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  double x_start = -6.8;
  double y_start = -2;
  double x_final = 4.2;
  double y_final = -2;
  bool reached = false;
  bool test_flag = false;
    
  // See if we have successfully received information from the pick_objects node
  ros::NodeHandle nh("/pick_objects");
  if(nh.hasParam("/AtPickupLoc") && nh.hasParam("/AtFinalLoc")) 
  {
    ROS_INFO("Both flags received from pick_objects node.");
    nh.getParam("/AtPickupLoc", test_flag);
  }
      
  marker.pose.position.x = x_start;
  marker.pose.position.y = y_start;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.4;
  marker.scale.y = 0.4;
  marker.scale.z = 0.4;

    // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 1.0f;
  marker.color.g = 0.1f;
  marker.color.b = 0.3f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();
  // Publish the marker
  while (marker_pub.getNumSubscribers() < 1)
  {
    if (!ros::ok())
    {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }
  marker_pub.publish(marker);
  ROS_INFO("Published at start position");
  r.sleep();
    
  // stay in the while loop till the time the robot reaches the pickup location
  while(!reached)
  {
    nh.getParam("/AtPickupLoc", test_flag);
    reached = test_flag;
    r.sleep();
  }
  // stay there for 5 seconds to simulate pickup
  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);
  ROS_INFO("Object has been picked up");
  sleep(5);
    
    
    // FOR FINAL LOCATION
  test_flag = false;
  reached = false;
  marker.pose.position.x = x_final;
  marker.pose.position.y = y_final;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
    
  marker.action = visualization_msgs::Marker::ADD;
    
    // wait till the robot reaches the final position
  while(!reached)
  {
    nh.getParam("/AtFinalLoc", test_flag);
    reached = test_flag;
  }
    
  marker_pub.publish(marker);
  ROS_INFO("Object has been dropped to the goal position");
  sleep(5);

  return 0;
}

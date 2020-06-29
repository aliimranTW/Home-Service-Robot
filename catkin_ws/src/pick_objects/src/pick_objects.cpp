
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

  // parameters to track robot states
  ros::NodeHandle nh;
  nh.setParam("/AtPickupLoc", false);
  nh.setParam("/AtFinalLoc", false);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  double pickup_x =  -6.8;
  double pickup_y = -2.0;
  double pickup_w = 1.0;
  
  double dest_x = 4.2;
  double dest_y = -2.0;
  double dest_w = 1.0;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = pickup_x;
  goal.target_pose.pose.position.y = pickup_y;
  goal.target_pose.pose.orientation.w = pickup_w;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal 1");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Succesfully reached the pickup location");
    nh.setParam("/AtPickupLoc", true);
  }

  else
    ROS_INFO("Failed to reach the pickup location...");

  // inform that the robot has reached the pickup location

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = dest_x;
  goal.target_pose.pose.position.y = dest_y;
  goal.target_pose.pose.orientation.w = dest_w;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal 2");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Reached goal position");
  else
    ROS_INFO("Failed to reach goal position");

  // inform that the goal location has been reached
  nh.setParam("/AtFinalLoc", true);


  return 0;
}

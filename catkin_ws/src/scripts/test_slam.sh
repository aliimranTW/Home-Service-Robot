#!/bin/sh

#xterm -e "pip install rospkg"

#sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot world.launch world_file:=$(rospack find turtlebot_gazebo)/worlds/corridor.world" &

sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch gmapping slam_gmapping_pr2.launch" &

#sleep 5

#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; rosrun teleop_twist_keyboard teleop_twist_keyboard.py"

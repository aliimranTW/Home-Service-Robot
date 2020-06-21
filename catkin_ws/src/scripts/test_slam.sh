#!/bin/sh

xterm -e "pip install rospkg"

#sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot world.launch world_file:=$(rospack find turtlebot_gazebo)/worlds/corridor.world" &
#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot world.launch" &

#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find my_robot)/worlds/HSRworld" &

sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch gmapping slam_gmapping_pr2.launch " &

#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch " &

sleep 5

#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &

#sleep 5
#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; rosrun teleop_twist_keyboard teleop_twist_keyboard.py"

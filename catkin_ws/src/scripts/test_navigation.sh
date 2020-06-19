#!/bin/sh

xterm -e "pip install rospkg"

sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot world.launch world_file:=$(rospack find turtlebot_gazebo)/worlds/corridor.world" &

sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot amcl.launch"

sleep 5

#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch"

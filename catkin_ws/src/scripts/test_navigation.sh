#!/bin/sh

xterm -e "pip install rospkg"

sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot world.launch world_file:=$(rospack find turtlebot_gazebo)/worlds/corridor.world " &
#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find my_robot)/worlds/HSRworld" &

sleep 5

xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch my_robot amcl.launch" 
#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find my_robot)/maps/map.yaml" &

#sleep 5
#xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch"

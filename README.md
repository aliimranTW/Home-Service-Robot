# Home-Service-Robot

The goal of the project is to build an autonomous robot that can be deployed in an unknown environment and should be able to perform the following tasks:

1. Be able to perform SLAM and create a map for navigation purpose.
2. Be able to navigate in an environment and reach the desired goal positions while avoiding obstacles.
3. simulate an operation of transporting an object by introducing virtual objects in the environment. 

To run the project, implement the following lines of code:

```
cd catkin_ws/src/scripts
./home_service.sh
```

## Description

There are three important parts of this project:

### SLAM implementation:

The first task of the robot is to map the environment in which it is present. An existing ROS package for SLAM has been used for the purpose. Using the depth RGBD sensor mounted on the Turtlebot robot, a map of the environment has been created. To perform the SLAM operation, run the following lines of code:

```
cd catkin_ws/src/scripts
./test_slam.sh
```
These lines of code should initialize turtlebot robot inside a custom world. It should open an Rviz file where all of the parameters can be viewed. Moreover, it should run the SLAM node that would enable to map the environment. After successfully performing SLAM, open a new terminal and use the following lines to save the map:

```
cd catkin_ws
source devel/setup.bash
rosrun map_server map_saver map.yaml
```

### Navigation:

Next task of the robot is to localize itself in the new environment, inside the map built in the previous step. Localization has been performed using the Monte Carlo Localization algorithm. Again, a built-in ROS package has been used which implements the Adaptive Monte Carlo Localization (AMCL). 

For navigation, we use the 2D nav_goal feature already present in RVIZ. To test localization and navigation, run the following lines of code:
```
cd catkin_ws/src/scripts
./test_navigation.sh
```

### Home Service Operation: 

Using the aforementioned operations, we can use our robot for a transportation application. 



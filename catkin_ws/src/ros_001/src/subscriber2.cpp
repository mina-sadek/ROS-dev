/*
 * subscriber.cpp
 *
 *  Created on: Apr 29, 2017
 *      Author: tornado
 */

#include <ros/ros.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

#include "diffBotPi/diffBotPi.h"
#define PWM_MIN 500
#define PWM_STEP 10

// Topic messages callback
//void velCallback(const std_msgs::String::ConstPtr& msg)
void velCallback(const geometry_msgs::Twist msg)
{
	ROS_INFO("[Subscriber] received:\n[x=%f]\n[y=%f]\n[z=%f]\n-------\n", msg.linear.x, msg.linear.y, msg.linear.z);
}

int main(int argc, char **argv)
{
  int i, pwm_val;
  if (robot_init() <= -1)
    return 1;

	//Initiate new ROS node named "listener"
	ros::init(argc, argv, "listener");
	// Create a node handle: it is reference assigned to a new node
	ros::NodeHandle n;

	// subscribe to a given topic, in this case "robot/cmd_vel"
	// velCallback: is the name of the callback function that will be executed each time a message is reveived
	ros::Subscriber sub = n.subscribe("robot/cmd_vel", 1000, velCallback);

	// Enter a loop, pumping callbacks
	ros::spin();

	return 0;
}

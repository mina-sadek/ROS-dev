
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

#include "diffBotPi/diffBotPi.h"
#define PWM_MIN 500
#define PWM_STEP 10

using namespace std;

class diffBot
{
 public:
	// Constructor
	diffBot();
	// Destructor
	~diffBot();
	// Main node loop.
	void run();
private:
	// The node handle
	ros::NodeHandle nodeHandle;

	// A publisher member
	// ros::Publisher mPub;

	// A Subscriber member
	ros::Subscriber velocitySub;

	// A Service Server member
	//ros::ServiceServer mServServer;

	//FILE *pwmControlFile;

	//bool driveForwards;

	// Subscriber callback to the velocity topic.
	// @param vel The new velocity for the diffBot
	void velocitySubCallback(const geometry_msgs::Twist::ConstPtr &vel);

	/**
	 * The FooBar Service callback.
	 *
	 * @param req
	 * @param resp
	 * @return
	 */
	// bool FooBar_Service(ClassName::FooBar::Request &req, ClassName::FooBar::Response &resp)
};

diffBot::diffBot()
{
	if (robot_init() <= -1)
	{
		//return 1;
	}

	// Register subscriber and services
	this->velocitySub = this->nodeHandle.subscribe("diffbot/cmd_vel", 1, &diffBot::velocitySubCallback, this);

	/*
	// Open files for hardware communication
	this->pwmControlFile = fopen(PWM_CONTROL_FILE, "w");

	if (this->pwmControlFile == NULL)
	{
 		ROS_ERROR("Can't open hardware file: %s", PWM_CONTROL_FILE);
	}

	// Setup WiringPi 11 (GPIO7) for toggeling direction pin
	system("gpio mode 11 out");
	system("gpio write 11 1");
	this->driveForwards = true;
	*/
}

diffBot::~diffBot()
{
	robot_exit();
	/*
	// Close previosly opened files
	fprintf(this->pwmControlFile, "%i=0\n", MOTOR_PWM_CHANNEL);
	fflush(this->pwmControlFile);
	fprintf(this->pwmControlFile, "%i=0\n", SERVO_PWM_CHANNEL);
	fflush(this->pwmControlFile);
	fclose(this->pwmControlFile);
	*/
}

void diffBot::run()
{
	// Sleep till new messages arrives
	ros::spin();
}

void diffBot::velocitySubCallback(const geometry_msgs::Twist::ConstPtr &vel)
{
	ROS_INFO("[Subscriber] received:\n[x=%f]\n[y=%f]\n[z=%f]\n-------\n", vel->linear.x, vel->linear.y, vel->angular.z);
	// Check if direction is set correctly
	if (vel->linear.x >= 0)
	{
		int speed = vel->linear.x;
		// move forward
		printf("robot moving FORWARD @ speed = %d\n", speed);
		robot_move(FORWARD, speed);
		//system("gpio write 11 1");
		//this->driveForwards = true;
	}
	else if (vel->linear.x < 0)
	{
		int speed = abs(vel->linear.x);
		// move forward
		printf("robot moving BACKWARD @ speed = %d\n", speed);
		robot_move(BACKWARD, speed);
		//system("gpio write 11 0");
		//this->driveForwards = false;
	}
	if (vel->angular.z >= 0)
	{
		int speed = vel->angular.z;
		// move right
		printf("robot moving RIGHT @ speed = %d\n", speed);
		robot_move(RIGHT, speed);
	}
	else if (vel->angular.z < 0)
	{
		int speed = abs(vel->angular.z);
		// move right
		printf("robot moving RIGHT @ speed = %d\n", speed);
		robot_move(RIGHT, speed);
	}

	/*
	// Set angular speed to servo (PWM)
	// PWM 0.075 DC is the center pose. Left / Right = +/- 0.02
	double offset = vel->angular.z * 0.025;
	offset = (offset > 0.025) ? 0.025 : (offset < -0.025) ? -0.025 : offset;
	fprintf(this->pwmControlFile, "%i=%f\n", SERVO_PWM_CHANNEL, offset + 0.072);
	fflush(this->pwmControlFile);


	// Set linear speed to motor (PWM) 0% ... 100%
	double speed = abs(vel->linear.x);
	speed = (speed > 1) ? 1 : speed;
	fprintf(this->pwmControlFile, "%i=%f\n", MOTOR_PWM_CHANNEL, speed);
	fflush(this->pwmControlFile);

	//ROS_INFO("New PWM Duty Settings (Servo | Motor): %f | %f", offset + 0.075, speed);
	*/
}

int main(int argc, char** argv)
{
	// Register node in the ros environment
	ros::init(argc, argv, "diffBot_node");
	diffBot bot;
	bot.run();
}

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include <math.h>

float X;

void listen(const std_msgs::Float64 msg)
{
    X = msg.data;
ROS_INFO("X: %f", X);
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "ctrl");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("jointcontrol", 1, listen);
    //for sinusoid
      /*
    ros::Subscriber sub = n.subscribe("sinfunction", 1, listen); 
   */

   //  for end effector
    ros::Publisher pub = n.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 1);
    /* for base
    ros::Publisher pub = n.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 1);*/
    
    ros::Rate loop_rate(10);
    ros::Time startTime = ros::Time::now();
    while(ros::ok())
    {
        std_msgs::Float64 msg;
        msg.data = X;
        pub.publish(msg);
        ROS_INFO("moving %f", msg.data);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

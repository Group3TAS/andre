#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "IMU_norm.h"
#include <sensor_msgs/Imu.h>
#include <vector>

class imu_norm
{
private:
  ros::NodeHandle nh_;
 //wohin publishen? Eigenes topic? To Do
 //ros::Publisher 
  ros::Subscriber imu_sub;
  geometry_msgs::Vector3 imu_normed;
 public:
  imu_norm(ros::NodeHandle &nh)
  {
    nh_ = nh;
    imu_pub_ = nh_.advertise<geometry_msgs::Vector3>("/imu/data", 1);
  };
  void imuCallback(const sensor_msgs::Imu::ConstPtr& imu)
  { 
  //so
  ROS_INFO("X acceleration: %f", imu->linear_acceleration->x);
  ROS_INFO("Y acceleration: %f", imu->linear_acceleration->y);
  ROS_INFO("Z acceleration: %f", imu->linear_acceleration->z);
//oder
  ROS_INFO("X acceleration: %f", imu->linear_acceleration.x);
  ROS_INFO("Y acceleration: %f", imu->linear_acceleration.y);
  ROS_INFO("Z acceleration: %f", imu->linear_acceleration.z);


	imu_normed=imu;
	imu_normed.linear_acceleration.x=imu_normed.linear_acceleration.x+10;
	
	imu_pub_.publish(imu_normed);
}
int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "imu_norm");
  ros::NodeHandle nh;
  imu_norm imu_control(nh);
  
  //ros::Subscriber imu_sub = nh.subscribe("/imu/data", 1000, &imu_norm::imuCallback, imu_control);
  //oder
  ros::Subscriber imu_sub = nh.subscribe("/imu/data", 1000,:imuCallback)
  
  
  ros::spin();
  //ros::Subscriber sub = nh.subscribe("scan", 1000, &dynamics_control::laserCallback, &car_control);
  


}

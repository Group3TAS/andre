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
  sensor_msgs::Imu imu_normed;
  ros::Publisher imu_pub_;
  geometry_msgs::Vector3 probe;
 public:
  imu_norm(ros::NodeHandle &nh)
  {
    nh_ = nh;
    imu_pub_ = nh_.advertise<sensor_msgs::Imu>("/imu/data_normed", 1);
  };
  void imuCallback(const sensor_msgs::Imu::ConstPtr& imu)
  { 
  //so
 // ROS_INFO("X acceleration: %f", imu->linear_acceleration->x);
  //ROS_INFO("Y acceleration: %f", imu->linear_acceleration->y);
  //ROS_INFO("Z acceleration: %f", imu->linear_acceleration->z);
//oder
  ROS_INFO("X acceleration: %f", imu->linear_acceleration.x);
  ROS_INFO("Y acceleration: %f", imu->linear_acceleration.y);
  ROS_INFO("Z acceleration: %f", imu->linear_acceleration.z);

	
	
	double v=[3][1];
	double dummy=[3][1];
	double R_x[3][3];
	double R_y[3][3];
	double R_z[3][3];
	
	v[1]][1]=linear_acceleration.x;
		v[1]][2]=linear_acceleration.y;
			v[1]][3]=linear_acceleration.z;
	
	
	
	//drehung um x achse
	alpha=atan(v[1]][2]/v[1]][3]); 
	
	R_x[1]][1]=1;
		R_x[1]][2]=0;
			R_x[1]][3]=0;
				R_x[2]][1]=0;
					R_x[2]][2]=cos(alpha);
						R_x[2]][3]=-sin(alpha);
							R_x[3][1]=0;
								R_x[3]][2]=sin(alpha);
									R_x[3]][3]=cos(alpha);
									
									
		for(int x=0;x<3;x++){ 
    for(int j=0;j<1;j++){  
        int result = 0; 
        for(int y=0;y<3;y++){         
                result += R_x[x][y] * v[y][j]; 
        } 
        dummy[x][j] = result; 
   		 }       
		}					
						v=dummy;						
						
	 //drehung um y achse								
	beta=atan(v[1]][1]/v[1]][3]);  
	
	
	R_y[1]][1]=cos(beta);
		R_y[1]][2]=0;
			R_y[1]][3]=sin(-beta);
				R_y[2]][1]=0;
					R_y[2]][2]=1;
						R_y[2]][3]=0;
							R_y[3][1]=-sin(-beta);
								R_y[3]][2]=0;
									R_y[3]][3]=cos(beta);
									
	for(int x=0;x<3;x++){ 
    for(int j=0;j<1;j++){  
        int result = 0; 
        for(int y=0;y<3;y++){         
                result += R_y[x][y] * v[y][j]; 
        } 
        dummy[x][j] = result; 
   		 }       
		}					
			v=dummy;
			
				 //drehung um y achse								
	omega=0;
	R_z[1]][1]=cos(omega);
		R_z[1]][2]=-sin(omega);
			R_z[1]][3]=0;
				R_z[2]][1]=sin(omega);
					R_z[2]][2]=cos(omega);
						R_z[2]][3]=0;
							R_z[3][1]=0;
								R_z[3]][2]=0;
									R_z[3]][3]=1;
	
	
		for(int x=0;x<3;x++){ 
    for(int j=0;j<1;j++){  
        int result = 0; 
        for(int y=0;y<3;y++){         
                result += R_z[x][y] * v[y][j]; 
        } 
        dummy[x][j] = result; 
   		 }       
		}					
			v=dummy;
	
	
	
  	probe.x=v[1[]1];
	probe.y=v[2[]1];
	probe.z=v[3[]1];
    //imu_normed=imu;
  	imu_normed=*imu;
    imu_normed.linear_acceleration =probe ;
	
    imu_pub_.publish(imu_normed);
}
};
int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "imu_norm");
  ros::NodeHandle nh;
  imu_norm imu_control(nh);
  
  ros::Subscriber imu_sub = nh.subscribe("imu/data", 1000, &imu_norm::imuCallback, &imu_control);
  //oder
  //ros::Subscriber imu_sub = nh.subscribe("/imu/data", 1000, imuCallback);
  
  
  ros::spin();
  //ros::Subscriber sub = nh.subscribe("scan", 1000, &dynamics_control::laserCallback, &car_control);
  


}

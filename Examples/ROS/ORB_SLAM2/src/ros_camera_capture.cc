/**
* This file is to capture images from Android phone, for camera calibration
* This file is used with Android_Camera-IMU
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include<opencv2/core/core.hpp>

#include"../../../include/System.h"

using namespace std;



string save_dir = "/home/mingrui/Mingrui/SLAMProject/calibrationImages/";
int imgId = 0;

void GrabImage(const sensor_msgs::ImageConstPtr& msg);

int main(int argc, char **argv)
{

    std::cout << "To save the current frame, please press 'Q' or 'q' " << std::endl;
    std::cout << "The images will be saved to " <<  save_dir << std::endl;

    ros::init(argc, argv, "PClistener");
    ros::start();

    ros::NodeHandle nodeHandler;
    ros::Subscriber sub = nodeHandler.subscribe("/camera/image_raw", 1, GrabImage);

    ros::spin();

    ros::shutdown();

    return 0;
}

void GrabImage(const sensor_msgs::ImageConstPtr& msg)
{
    string imgname;
    
    
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvShare(msg);

        cv::Mat img = cv_ptr->image;

        cv::imshow("img_name", img);

        // std::cout << "has received one image. " << std::endl;

        char key = cv::waitKey(1);
        // press "q" to save the image 
        if(key == 'q' || key == 'Q'){  
            imgId++;
            imgname = "img_" + to_string(imgId) + ".jpg";
            cv::imwrite(save_dir + imgname, img);
            std::cout << "has saved image "<< imgId << " to " << save_dir << std::endl;
        }
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

}



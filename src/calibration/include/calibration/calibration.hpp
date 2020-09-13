#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

class calibration
{
    public:
        cv::Mat r_src, l_src;
        cv::Mat r_dst, l_dst;
        
        cv::Mat img_tmp;

        ros::Subscriber image_sub;
        ros::NodeHandle nh_;

        calibration(ros::NodeHandle &_nh):
        nh_(_nh)
        {
            r_src = cv::Mat::zeros(480, 640, CV_8UC3);
            l_src = cv::Mat::zeros(480, 640, CV_8UC3);
            img_tmp = cv::Mat::zeros(480, 640, CV_8UC3);
            initSubscriber();
            //runloop();
        }
        ~calibration()
        {

        }

        void initSubscriber();
        void ImgCallback(const sensor_msgs::Image::ConstPtr &image_msg);
        void runloop();

};
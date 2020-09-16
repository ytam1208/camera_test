#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <thread>
#include <ros/ros.h>

class calibration
{
    public:
        cv::Mat r_src, l_src;        


        calibration()
        {
            r_src = cv::Mat::zeros(480, 640, CV_8UC3);
            l_src = cv::Mat::zeros(480, 640, CV_8UC3);
            //runloop();
            videocapture();
        }
        ~calibration()
        {

        }
        int videocapture();

};
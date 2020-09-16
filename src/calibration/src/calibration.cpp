#include "calibration/calibration.hpp"


int calibration::videocapture()
{
    cv::VideoCapture cap(1);
    cv::VideoCapture cap2(0);

    if(!cap.isOpened() && !cap2.isOpened())
    {
        std::cout << "Capture Couldn`t open. " << std::endl;
        return 0;
    }

    cv::namedWindow("right_Video");
    cv::namedWindow("left_Video");
    // cv::namedWindow("flip_right_Video");
    // cv::namedWindow("flip_left_Video");
	while(ros::ok())
	{
	    cap >> r_src;
        cap2 >> l_src;
        if(r_src.empty() || l_src.empty())
        {
            std::cout << "Video over!" << std::endl;
            break;
        }
        cv::Mat flip_r = cv::Mat::zeros(480, 640, CV_8UC3);
        cv::Mat flip_l = cv::Mat::zeros(480, 640, CV_8UC3);

        cv::flip(r_src, flip_r, 1);
        cv::flip(l_src, flip_l, 1);        
        cv::swap(r_src, flip_r);
        cv::swap(l_src, flip_l);
        
        cv::imshow("right_Video", r_src);
        cv::imshow("left_Video", l_src);
        // cv::imshow("flip_right_Video", flip_r);
        // cv::imshow("flip_left_Video", flip_l);
       
        cv::waitKey(1);
        printf("hhhh\n");
    }
}


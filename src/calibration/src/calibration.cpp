#include "calibration/calibration.hpp"

void calibration::initSubscriber()
{
    image_sub = nh_.subscribe("/usb_cam/image_raw", 1, &calibration::ImgCallback, this);
}

void calibration::ImgCallback(const sensor_msgs::Image::ConstPtr &image_msg)
{
    unsigned char index[640 * 480 * 3];

    for(int i = 0; i < image_msg->data.size(); i++)
    {
        //printf("i = %d\n", i);
        index[i] = image_msg -> data[i];
    }

    calibration::img_tmp = cv::Mat(480, 640, CV_8UC3, index);
    cv::flip(calibration::img_tmp, calibration::r_src, 1);
    // cv::cvtColor(calibration::r_src, calibration::img_tmp, cv::COLOR_BGR2GRAY);
}

void calibration::runloop()
{
    ros::Rate r(10);

    while (ros::ok())
	{
		cv::imshow("src", img_tmp);
		cv::waitKey(1);
        r.sleep();
	}
    ros::spin();
}
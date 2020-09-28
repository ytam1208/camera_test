#include "calibration/calibration.hpp"


int calibration::videocapture()
{
    cv::VideoCapture cap(0);

    if(!cap.isOpened())
    {
        std::cout << "Capture Couldn`t open. " << std::endl;
        return 0;
    }

    cv::namedWindow("Video");
    // cv::namedWindow("flip_right_Video");
    // cv::namedWindow("flip_left_Video");
	while(ros::ok())
	{
	    cap >> src;
        if(src.empty())
        {
            std::cout << "Video over!" << std::endl;
            break;
        }
        cv::Mat flip = cv::Mat::zeros(480, 640, CV_8UC3);

        cv::flip(src, flip, 1);
        cv::swap(src, flip);
        
        cv::imshow("Video", src);
       
        cv::waitKey(1);
    }
}

void calibration::SolvePnP()
{
    std::vector<cv::Point3f> objectPoints;  //3d world coordinates
    std::vector<cv::Point2f> imagePoints;   //2d world coordinates

    if(imagePoints.size() == 0)
        return;
    
    //createObjPoints:
    // for(int j = 0; j < img_rows; j++)
    //     for(int k = 0; k < img_cols; k++)
    //         objectPoints.push_back(cv::Point3f(float(k * square_size), float(j * square_size ), 0));
    // extract rotation & translation matrix


    std::vector<calibration::cameraMatrix> Cam_vec;
    std::vector<calibration::distCoeffs> Cam_Dist_vec;
    
    Cam_vec.clear();
    Cam_Dist_vec.clear();
    Cam_vec.push_back(cameraMatrix);
    Cam_Dist_vec.push_back(distCoeffs);

    struct Cam_param
    {
        //camera parameters
        cv::Mat CameraMatrix_Mat(3, 3, CV_64FC1, Cam_vec);   //Camera Matrix
        // distortion 외곡
        cv::Mat DistCoeffs_Mat(4, 1, CV_64FC1, distCoeffs);
    };


    Cam_param CameraParam;
    
    cv::solvePnP(
        objectPoints,
        imagePoints,
        CameraParam.CameraMatrix_Mat,
        CameraParam.DistCoeffs_Mat,
        rvec, tvec);

    std::cout << "rvec\n" << rvec << std::endl;
    std::cout << "tvec\n" << tvec << std::endl;


    // cv::Mat R;
    // Rodrigues(rvec, R);
    // cv::Mat R_inv = R.inv();
    // cv::Mat P = -R_inv*tvec;
    // double* p = (double *)P.data;

    // // camera position
    // printf("x=%lf, y=%lf, z=%lf", p[0], p[1], p[2]);   
}
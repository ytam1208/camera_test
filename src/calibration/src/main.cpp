#include "calibration/calibration.hpp"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "image_calibration");

	ros::NodeHandle _nh;
	calibration camera(_nh);

	camera.runloop();
	
	return 0;
}

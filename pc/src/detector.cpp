#include <vector>
#include <opencv2/opencv.hpp>

#include "Helicopter.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	Mat cam_img;
	VideoCapture cam(0);

	Mat bw, thrsh;
	double max_val;
	double min_intensity = 163;
	double thresh_val;

	vector<Point> leds;

	Helicopter heli("192.168.1.3", 32000);

	char key;
	while (true)
	{
		cam >> cam_img;

		cvtColor(cam_img, bw, CV_BGR2GRAY);
		minMaxLoc(bw, NULL, &max_val);

		thresh_val = (max_val > min_intensity) ? 0.8 * max_val : 256;

		threshold(bw, thrsh, thresh_val, 255, THRESH_BINARY);
		
		imshow("Thrsh", thrsh);

		heli.Update(thrsh);

		heli.Draw(cam_img);

		imshow("Image", cam_img);


		
		key = cv::waitKey(1);
		if (key == 'q') break;
	}

	return 0;
}

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int MIN_AREA = 1;
const int MAX_AREA = 50;

void findLEDs(Mat img, vector<Point>& leds)
{
	static vector<vector<Point>> contours;
	static double area, max_area, circularity;
	static Rect led_rect;

	leds.clear();

	findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	max_area = -1;

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		area = contourArea(contours[i]);
		if (area < MIN_AREA) { continue; }
		circularity = 4 * M_PI * area / (contours[i].size() * contours[i].size());
		led_rect = boundingRect(contours[i]);

		if(circularity >= 0.35f)
		{
			leds.push_back(0.5 * (led_rect.tl() + led_rect.br()));
		}
	}
}

int main(int argc, char** argv)
{

	Mat cam_img;
	VideoCapture cam(1);

	Mat bw, thrsh;
	double max_val;
	double min_intensity = 170;
	double thresh_val;

	vector<Point> leds;

	char key;
	while (true)
	{
		cam >> cam_img;

		cvtColor(cam_img, bw, CV_BGR2GRAY);
		minMaxLoc(bw, NULL, &max_val);

		thresh_val = (max_val > min_intensity) ? 0.8 * max_val : 256;

		threshold(bw, thrsh, thresh_val, 255, THRESH_BINARY);
		
		imshow("Thrsh", thrsh);

		findLEDs(thrsh, leds);

		for(unsigned int i = 0; i < leds.size(); ++i)
		{
			circle(cam_img, leds[i], 5, Scalar(0, 255, 0), CV_FILLED);
		}
		
		imshow("Image", cam_img);
		
		key = cv::waitKey(1);
		if (key == 'q') break;
	}

	return 0;
}

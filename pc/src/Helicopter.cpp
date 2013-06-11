#include "Helicopter.h"

using namespace cv;
using namespace std;

Helicopter::Helicopter() {}

void Helicopter::Update(cv::Mat& image)
{
	static vector<vector<Point>> contours;
	static double area, circularity;
	static Rect led_rect;
	static const int MinArea = 1;
	static const int MaxArea = 100;

	detected_blobs.clear();

	findContours(image, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		area = contourArea(contours[i]);
		if (area < MinArea && area < MaxArea) { continue; }
		
		circularity = 4 * M_PI * area / (contours[i].size() * contours[i].size());
		led_rect = boundingRect(contours[i]);

		if(circularity >= 0.35f)
		{
			detected_blobs.push_back(Blob(0.5 * (led_rect.tl() + led_rect.br()), area));
		}
	}
}

bool Helicopter::SendUDP()
{

}

void Helicopter::Draw(cv::Mat& image)
{

}

#include "Helicopter.h"
#include "udp_client.hpp"

using namespace cv;
using namespace std;

Helicopter::Helicopter(std::string _ip, unsigned int _port) 
{
	connect_udp(_ip, _port);
}

Helicopter::~Helicopter()
{
	close();
}

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
	float buffer[4];
	buffer[0] = (float)front.GetLastPosition().pos.x;
	buffer[1] = (float)front.GetLastPosition().pos.y;
	buffer[2] = (float)side.GetLastPosition().pos.x;
	buffer[3] = (float)side.GetLastPosition().pos.y;
	
	return send_msg((unsigned char*)buffer, 4);
}

void Helicopter::Draw(cv::Mat& image)
{

}

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
			detected_blobs.push_back(new Blob(0.5 * (led_rect.tl() + led_rect.br()), area));
		}
	}

	if(detected_blobs.size() == 0) return;

	//Front1,2 and Side1,2
	Blob *front1, *front2, *side1, *side2;
	double front_dist1, front_dist2, side_dist1, side_dist2;

	getTwoBestMatches(front, front1, front_dist1, front2, front_dist2);
	getTwoBestMatches(side, side1, side_dist1, side2, side_dist2);

	if(front1 != side1)
	{
		assignLEDs(front1, side1, front_dist1, side_dist1);
	} 
	else
	{
		if(detected_blobs.size() == 1)
		{
			if(front_dist1 < side_dist1)
			{
				//Do not swap lines!
				side.Update(findMissingBlob(front, front1, side));
				front.Update(*front1);
			}
			else
			{
				//Do not swap lines!
				front.Update(findMissingBlob(side, side1, front));
				side.Update(*side1);
			}
		}
		else
		{
			if(front_dist1 < side_dist1)
			{
				assignLEDs(front1, side2, front_dist1, side_dist2);
			}
			else
			{
				assignLEDs(front2, side1, front_dist2, side_dist1);	
			}	
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
	
	return send_msg((unsigned char*)buffer, 4 * sizeof(float));
}

void Helicopter::Draw(cv::Mat& image)
{
	circle(image, front.GetLastPosition().pos, 5, Scalar(0, 255, 0));
	circle(image, side.GetLastPosition().pos, 5, Scalar(0, 255, 0));

	circle(image, front.GetLastPosition().pos, 5, Scalar(0, 255, 255));
	circle(image, side.GetLastPosition().pos, 5, Scalar(0, 255, 255));


}

void Helicopter::getTwoBestMatches(const LED& led, Blob*& first, double& first_dist, Blob*& second, double& second_dist)
{
	// Search for the closest blob to the predicted position
	first_dist = std::numeric_limits<double>::max();
	std::list<Blob>::iterator index;

	first = NULL;
	second = NULL;

	for(unsigned int i = 0; i < detected_blobs.size(); ++i)
	{
		double diff = led.GetLastPrediction() - *detected_blobs[i];
		if (diff < first_dist)
		{
			second = first;
			second_dist = first_dist;

		    first = detected_blobs[i];
		    first_dist = diff;
		}
	}
}

Blob Helicopter::findMissingBlob(const LED& led1, const Blob* b1, const LED& led2)
{
	Point d = led1.GetLastPosition().pos - led2.GetLastPosition().pos;

	return Blob(b1->pos + d, 0);

}

int Helicopter::checkAlignment(Blob* b1, Blob* b2, const double& dist1, const double& dist2)
{
	if(abs(b1->pos.x - b2->pos.x) > MAX_HORIZONTAL_DISTANCE ||
	   abs(b1->pos.y - b2->pos.y) > MAX_VERTICAL_DISTANCE)
	{
		return (dist1 < dist2) ? 1 : 2;
	}

	return 0;
}

void Helicopter::assignLEDs(Blob* b1, Blob* b2, const double& dist1, const double& dist2)
{
	switch(checkAlignment(b1, b2, dist1, dist1))
	{
		case 0:
			front.Update(*b1);
			side.Update(*b2);
			break;
		case 1:
			//Do not swap lines!
			side.Update(findMissingBlob(front, b1, side));
			front.Update(*b1);
			break;
		case 2:
			//Do not swap lines!
			front.Update(findMissingBlob(side, b2, front));
			side.Update(*b2);
			break;
		default:
			break;
	}
}
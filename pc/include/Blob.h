#ifndef BLOB_H
#define BLOB_H 

#include <opencv2/opencv.hpp>

class Blob
{
	public:
		cv::Point pos;
		double area;
		
		Blob(cv::Point _pos, double _area) : pos(_pos), area(_area) {};

		friend double operator-(const Blob &b1, const Blob &b2);
};

double operator-(const Blob &b1, const Blob &b2)
{
	 return abs(b1.pos.x - b2.pos.x) + abs(b1.pos.y - b2.pos.y) + abs(b1.area - b2.area);
}
 
#endif
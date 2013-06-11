#ifndef BLOB_H
#define BLOB_H 

#include <opencv2/opencv.hpp>

class Blob
{
	public:
		cv::Point pos;
		double area;
		
		Blob(cv::Point _pos, double _area) : pos(_pos), area(_area) {};

		friend Blob operator-(const Blob &b1, const Blob &b2);
};

Blob operator-(const Blob &b1, const Blob &b2)
{
	
}
 
#endif
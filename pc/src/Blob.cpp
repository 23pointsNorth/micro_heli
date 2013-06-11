#include "Blob.h"

double operator-(const Blob &b1, const Blob &b2)
{
	 return cv::norm(b1.pos - b2.pos);
}

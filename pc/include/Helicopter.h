#ifndef HELICOPTER_HEADER_
#define HELICOPTER_HEADER_

#include "LED.h"

class Helicopter
{
public: 
	Helicopter();
	void Update();
	bool SendUDP();
	void Draw(cv::Mat& image);

private:
	LED front;
	LED side;

};

#endif /* !HELICOPTER_HEADER_ */
#ifndef HELICOPTER_HEADER_
#define HELICOPTER_HEADER_

#include "LED.h"
#include <string.h>

class Helicopter
{
public: 
	Helicopter(std::string _ip, unsigned int _port);
	~Helicopter();
	void Update(cv::Mat& image);
	bool SendUDP();
	void Draw(cv::Mat& image);

private:
	LED front;
	LED side;

	std::vector<Blob> detected_blobs;

};

#endif /* !HELICOPTER_HEADER_ */
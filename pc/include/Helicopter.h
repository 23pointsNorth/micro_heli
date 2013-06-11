#ifndef HELICOPTER_HEADER_
#define HELICOPTER_HEADER_

#include "LED.h"
#include <string.h>

const int MAX_VERTICAL_DISTANCE = 50;
const int MAX_HORIZONTAL_DISTANCE = 200;

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

	std::vector<Blob*> detected_blobs;

	void getTwoBestMatches(const LED& led, Blob*& first, double& first_dist, Blob*& second, double& second_dist);

	Blob findMissingBlob(const LED& led1, const Blob* b1, const LED& led2);
	int checkAlignment(Blob* b1, Blob* b2, const double& dist1, const double& dist2);

	void assignLEDs(Blob* b1, Blob* b2, const double& dist1, const double& dist2);

};

#endif /* !HELICOPTER_HEADER_ */
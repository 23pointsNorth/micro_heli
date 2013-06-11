#ifndef LED_HEADER_
#define LED_HEADER_

#include <list>
#include <vector>

#include "Blob.h"

const int LIST_SIZE = 5;

class LED
{
public: 
	void Update(std::list<Blob> blobs);
	Blob GetLastPosition();
	Blob GetLastPrediction();
private:
	std::list<Blob> pos;
	std::list<Blob> pred;

	void Predict();
};

#endif /* !LED_HEADER_ */
#ifndef LED_HEADER_
#define LED_HEADER_

#include <list>

#include "Blob.h"

const unsigned int LIST_SIZE = 5;

class LED
{
public: 
	void Update(const Blob& new_blob);
	Blob GetLastPosition() const;
	Blob GetLastPrediction() const;
private:
	std::list<Blob> pos;
	std::list<Blob> pred;

	void Predict();
};

#endif /* !LED_HEADER_ */
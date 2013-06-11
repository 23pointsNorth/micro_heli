#include "Helicopter.h"
#include "udp_client.hpp"

Helicopter::Helicopter(std::string _ip, unsigned int _port) 
{
	connect_udp(_ip, _port);
}

Helicopter::~Helicopter()
{
	close();
}

void Helicopter::Update()
{

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

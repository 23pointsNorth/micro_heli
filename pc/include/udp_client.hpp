#include <string.h>
#include <iostream>

bool connect_udp(std::string ip, unsigned int port);
bool send_msg(unsigned char* msg, int len);
void close();

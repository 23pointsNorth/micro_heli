#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "udp_client.hpp"

using namespace std;

struct sockaddr_in serv_addr;
struct hostent *server;
int sockfd;

bool connect_udp(string ip, unsigned int port)
{
   server = gethostbyname(ip.c_str());
    if (server == NULL)
   {
       perror("No such host!");
       return 1;
   }
  
   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   if (sockfd < 0) 
    {
    perror("Could not opening socket!");
      return false;
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(port); 
 
   if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
   {
    perror("Could not connect to the host!");
      return false;
   }  
    return true;
}

bool send_msg(unsigned char* msg, int len)
{
    int n = write(sockfd, msg, len);
    if (n < 0)
    {
        perror("ERROR writing to socket");
        return false;
    }
    return true;
}

void close()
{
    close(sockfd);
}

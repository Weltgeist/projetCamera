#include<cmath>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<math.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include "class.h"


//cpp


Resolution operator*(const double factor, const Resolution &b){ return (b*factor); };
Resolution operator/(const double factor, const Resolution &b){ return (b / factor); };

ResolutionFPS operator*(const double factor, const ResolutionFPS &b){ return (b*factor); };
ResolutionFPS operator/(const double factor, const ResolutionFPS &b){ return (b / factor); };

void error(const char *msg)
{
    perror(msg);
    exit(1);
}



void  Serveur::initServeur(int portNum)
{


	 //Create a socket()
	 sockfd = socket(AF_INET, SOCK_STREAM, 0); //AFINET  == communication domain Ipv4, SOCK_STREAM is communication type(TCP in our case), 0 is  value for internet protocole
	 if (sockfd < 0)
		error("ERROR opening socket");

	 //Construct a local address structure
	 bzero((char *) &serv_addr, (uint)sizeof(serv_addr));
	 portno = portNum;//DEFINE PORT 4099 to be used as default instead of arg[v]//atoi(argv[1]);
	 serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr = INADDR_ANY;
	 serv_addr.sin_port = htons(portno);

	 //Assign a port to the number with bind() /Bind the local address
	 if (bind(sockfd, (struct sockaddr *) &serv_addr,
			 (uint)sizeof(serv_addr)) < 0)
			  error("ERROR on binding");

	 //Tell the system to allow connection made to that port with listen/ Mark the socket so it will listen for incoming connect
	 listen(sockfd,5); //put the socket in passive mode and set 5 as the maximum number for queue

	 clilen = sizeof(cli_addr);

	//cout<<"Init Serveur Complete"<<endl;

}

void Serveur::servAccept(){

		 newsockfd = accept(sockfd,
				 (struct sockaddr *) &cli_addr,
				 &clilen);
	 if (newsockfd < 0)
	  error("ERROR on accept");

};










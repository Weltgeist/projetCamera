/**
 * \file class.h
 * \brief Contains the class definitions of objects Resolution and Serveur.
 * \author ELE4205_07
 * \date 3 december 2018
 *
 */


#ifndef CLASS_H
#define CLASS_H

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
#include<opencv2/opencv.hpp>

using namespace cv;

void error(const char *msg);

/**
 * \class Resolution
 * \brief Contains the resolution in x and y of the possible images.
 */
class Resolution
{
private:
	int resX;
	int resY;

public:
	/**
	 * \fn Resolution(int a = -1, int b = -1)
	 * \brief Constructor of the Resolution class
	 * \param a The corresponding x value of the resolution.
	 * \param b The corresponding y value of the resolution.
	 */
	Resolution(int a = -1, int b = -1){ resX=a; resY=b;return; }
	/**
	 * \fn ~Resolution()
	 * \brief Destructor of the Resolution class
	 */
	~Resolution(){ return; }
	/**
	 * \fn int getX() const
	 * \brief Accesses the x value.
	 * \return The x value of the resolution.
	 */
	int getX()const{ return resX; };
	/**
	 * \fn int getY() const
	 * \brief Accesses the y value.
	 * \return The y value of the resolution.
	 */
	int getY()const{ return resY; };
	/**
	 * \fn int setX(int a)
	 * \brief Sets the x value.
	 * \param a The x value of the resolution.
	 */
	void setX(int a){ resX = a; };
	/**
	 * \fn void setY(int a)
	 * \brief Sets the y value.
	 * \param a The y value of the resolution.
	 */
	void setY(int a){ resY = a; };

};


/**
 * \class Serveur
 * \brief Contains the parameters and functions necessary to create and operate the server in the TCP connection.
 */
class Serveur
{
private:
	int sockfd, newsockfd, portno;
	long int bytes;
	struct sockaddr_in serv_addr, cli_addr; // adress structure
	int n;
	socklen_t clilen;
	char buffer[1024];
	char *ptrBuffer;
	int imgSize;

public:
	/**
	 * \fn Serveur()
	 * \brief Constructor of the class Serveur.
	 */
	Serveur(){};
	/**
	 * \fn ~Serveur()
	 * \brief Destructor of the class Serveur.
	 */
	~Serveur(){};
	
	/**
	 * \fn void initServeur(int portNum)
	 * \brief Initializes the server TCP socket with socket and bind and listens for the connect request of the client.
	 * \param portNum The port number of the socket.
	 */
	void initServeur(int portNum);
	/**
	 * \fn void servAccept()
	 * \brief Accepts the connect request of the client.
	 */
	void servAccept();
	/**
	 * \fn void initServeur(int portNum)
	 * \brief Sends the determined state to the client and receives the uint32_t image request from the client.
	 * \param etat The state of the server as determined from the light sensor and push-button drivers.
	 * \return The result of the image request, whether ok or quit.
	 */
	uint32_t servSendRecv(uint32_t etat);
	/**
	 * \fn void servCaptureSend(Mat& frame,VideoCapture &capture);
	 * \brief Captures a frame using parameters and sends the data to the client.
	 * \param frame The previously initialized Mat image.
	 * \param capture The capture VideoCapture object as defined in OpenCV.
	 */
	void servCaptureSend(Mat& frame,VideoCapture &capture);
	/**
	 * \fn void servClose()
	 * \brief Closes the TCP socket.
	 */
	void servClose();

};



#endif




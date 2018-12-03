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

//CPP

class Resolution
{
private:
	int resX;
	int resY;

public:

	Resolution(int a = -1, int b = -1){ resX=a; resY=b;return; }
	~Resolution(){ return; }
	int getX()const{ return resX; };
	int getY()const{ return resY; };
	void setX(int a){ resX = a; };
	void setY(int a){ resY = a; };

	//Overloading
	Resolution operator+(const Resolution &b)const{ return Resolution(resX + b.getX(), resY + b.getY()); };
	Resolution operator-(const Resolution &b)const{ return Resolution(resX - b.getX(), resY - b.getY()); };
	Resolution operator*(const double factor)const{ return Resolution((int)(resX*factor), (int)(resY*factor)); };
	Resolution operator/(const double factor)const{ return Resolution((int)(resX / factor), (int)(resY / factor)); };

};
//
class ResolutionFPS
{
private:
	Resolution res;
	double fps;
public:

	ResolutionFPS(int a = -1, int b = -1, double c = -1) :res(a, b), fps(c){ return; }
	ResolutionFPS(Resolution a, double c = -1) :res(a), fps(c){ return; }
	~ResolutionFPS(){ return; }
	void setRes(Resolution a){ res.setX(a.getX());  res.setY(a.getY()); return; }
	void setRes(int a,int b){ res.setX(a);  res.setY(b); return; }
	void setFps(double a){ fps = a; return; }
	Resolution getRes()const{ return res; };
	double getFps()const{ return fps; };
	//Overloading
	ResolutionFPS operator+(const ResolutionFPS &b)const{ return ResolutionFPS(res + b.getRes(), fps + b.getFps()); };
	ResolutionFPS operator-(const ResolutionFPS &b)const{ return ResolutionFPS(res - b.getRes(), fps - b.getFps()); };
	ResolutionFPS operator*(const double factor)const{ return ResolutionFPS(res*factor, fps*factor); };
	ResolutionFPS operator/(const double factor)const{ return ResolutionFPS(res/factor, fps/factor); };

};

Resolution operator*(const double factor, const Resolution &b);
Resolution operator/(const double factor, const Resolution &b);
ResolutionFPS operator*(const double factor, const ResolutionFPS &b);
ResolutionFPS operator/(const double factor, const ResolutionFPS &b);


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

	Serveur(){};
	~Serveur(){};

	void initServeur(int portNum);
	void servAccept();
	uint32_t servSendRecv(uint32_t etat);
	void servCaptureSend(Mat& frame,VideoCapture &capture);
	void servClose();

	int get_sockfd()const{ return sockfd; };
	int get_newsockfd()const{ return newsockfd; };
	int get_portno()const{ return portno; };
	int get_n()const{ return n; };
	long int get_bytes()const{ return bytes; };
	struct sockaddr_in  get_serv_addr()const{ return serv_addr; };
	struct sockaddr_in  get_cli_addr()const{ return cli_addr; };
	socklen_t  get_clilen()const{ return clilen; };
	void set_sockfd(int a){ sockfd = a; };
	void set_newsockfd(int a){ newsockfd = a; };
	void set_portno(int a){ portno = a; };
	void set_n( int a){ n = a; };
	void set_bytes(long int a){ bytes = a; };
	void set_serv_addr(int a){
		serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr = INADDR_ANY;
	 serv_addr.sin_port = htons(a);};
	void set_cli_addr(int a){
		cli_addr.sin_family = AF_INET;
		cli_addr.sin_addr.s_addr = INADDR_ANY;
		cli_addr.sin_port = htons(a);};
	void set_clilen( socklen_t a){ clilen = a; };
};



#endif




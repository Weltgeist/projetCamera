/**
 * \file class.h
 * \brief Contains the class definitions of objects Resolution, ResolutionFPS and Client.
 * \author ELE4205_07
 * \version 6.3.2
 * \date 3 december 2018
 *
 */


#ifndef CLASS_H
#define CLASS_H

#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <vector>
using namespace cv;

/**
 * \class Resolution
 * \brief Contains the resolution in x and y of the possible images.
 */
class Resolution
{
private:
	/**
	 * \var resX
	 * \brief The value in x of the resolution.
	 */
	int resX;
	/**
	 * \var resY The value in y of the resolution.
	 */
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
 * \class Client
 * \brief Contains the parameters and functions necessary to create and operate the client in the TCP connection.
 */
class Client
{
private:
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
    String face_cascade_name;
    String eyes_cascade_name;
	int sockfd, portno, connectSock;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int n;
	uint32_t messages;
	char buffer[256];
	char* ptrBuffer;
	Mat* img;
	int imgSize;
	vector<uchar> sockData;
	pid_t pid;
	char sctr_img[50];
	string PATH; //Path dans lequel les folders contenant les photos seront places
	string PathCSV;
	vector<Mat> listImages;
	vector<string> labels;
	vector<string> listeNoms;

public:

	/**
	 * \fn Client()
	 * \brief Constructor of the class Client. Initializes some constant values such as paths.
	 */
	Client(){
		face_cascade_name = "haarcascade_frontalface_alt.xml" ;
		eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
		PATH="/export/tmp/4205_07/projet"; //Path dans lequel les folders contenant les photos seront places
		PathCSV = "/export/tmp/4205_07/projet/Face_Label_DATA.csv";
	}

	~Client(){};
	void error(const char *msg);
	void createDir(const string& label);
	int choixPersonne(int ctr_img);
	void read_csv(char separator = ';');
	int find_ctr_img(int personne);
	void loadCascades();
	void initClient();
	void clientConnect();
	uint32_t clientRcvSend();
	void clientInitImg(Resolution (&res)[13], int choix);
	void writeToCSV(const string& CSVfilename,const string& IMGfilename,string label, int ctr_img, char separator=';');
	int detectAndDisplay( char* adress,int ctr_img,const string& Path,int mode=0, std::vector<Rect>* ptrFace=NULL);
	void recon(int personne);
	void clientFork(int mode, int ctr_img, int personne);
	void showImage();
	void deleteimg();
	int testKey(char key);
	void clientQuit();

	int get_sockfd()const{ return sockfd; };
	int get_portno()const{ return portno; };
	struct sockaddr_in  get_serv_addr()const{ return serv_addr; };
	int get_n()const{ return n; };
	Mat* get_img()const{return img;};
	int get_imgSize()const{ return imgSize; };

	void set_sockfd(int a){ sockfd = a; };
	void set_portno(int a){ portno = a; };
	void set_serv_addr(int a){
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(a);};
	void set_n( int a){ n = a; };
	void set_messages(uint32_t a){messages = a;};


};



#endif

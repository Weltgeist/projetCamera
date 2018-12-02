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
	void clientInitImg(ResolutionFPS (&rfps)[13], int choix);
	void writeToCSV(const string& CSVfilename,const string& IMGfilename,string label, int ctr_img, char separator=';');
	void detectAndDisplay( char* adress,int ctr_img,const string& Path,int mode=0, std::vector<Rect>* ptrFace=NULL);
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

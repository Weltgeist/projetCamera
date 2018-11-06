
//CLIENT///
/*
 * Code taken from https://stackoverflow.com/questions/20314524/c-opencv-image-sending-through-socket
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include"class.h"
//#include "constante.h"
#include "fonction.h"

using namespace cv;
using namespace std;

#define PORT 4099;
#define ELE4205_OK 0b1;

const int NB_RES=13;
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};


int main(int argc, char *argv[])
{
//		pid_t pid = fork();
//		if(pid == 0)
//		{
//			cout<<"Child"<<pid<<endl;
//
//		}
//		else if (pid>0)
//		{
//
//			cout<<"Parent"<<pid<<endl;
//		}
//		else
//		{
//			cout << "PID failed" << endl;
//		}
//		return 0;



	// Initialisations
	int count=0;
	bool go=1;
	int choix=1;
	int choix0_3=0;
	int table[4]={1,3,9,12};
	int nn=0;
    int sockfd, portno, n;
    long int bytes;
    int connectSock;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    uint32_t messages = ELE4205_OK;
    char buffer[256];
    char* ptrBuffer;
    char key;
	vector<uchar> sockData;
	Mat*  img;
	int  imgSize;
    portno = PORT;

	// Populer les resolutions
	ResolutionFPS rfps[13];
	populerResolutions(rfps,RES_TABLE);

    // Create TCP socket using socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("192.168.7.2");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);


	// Connection to server socket
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	while(go){
		// Receive state from server in uint32_t
		 bzero(buffer,256);
		 n = read(sockfd,buffer,255);
		 if (n < 0) error("ERROR reading from socket");

		 //Decoder le uint32 soit ici l'etat du serveur
		 uint32_t state = strtol(buffer,&ptrBuffer,10);

		 if (state == 1 || state == 3) {

			// Send ok to server to send the image
			sprintf(buffer,"%u", messages);
			n = write(sockfd,buffer,sizeof(messages));
			if (n < 0){ error("ERROR writing to socket");}
			// Initialize image for reception
			img=new Mat;
			*img= Mat::zeros( rfps[choix].getRes().getY() ,rfps[choix].getRes().getX() , CV_8UC3);
			imgSize = img->total()*(img->elemSize());
			//cout<<imgSize<<endl;
			//uchar sockData[imgSize];
			sockData.clear();
			sockData.resize(imgSize);////////////////////////SKIPS UCHAR ALL TOGETHER,BUT WE CAN ALSO USE A METHOD WITH UCHAR
			//WAITS!!!!!!!!!!!30 MS
			key =static_cast<char> (waitKey(30));  /*(char)*/
			// Receive image & assign to pixel
			 if ((bytes = recv(sockfd, img->data, imgSize, MSG_WAITALL)) == -1)
				 {cout<<"recv failed"<<endl;return -1;}
		   // Show image
		   namedWindow("Client", WINDOW_AUTOSIZE );
		   imshow( "Client", *img);
		   //Prepare next set;
			if(img!=0){delete img;}
			img=0;
			//Test key
		   if (key == 27) {break;}
		   //Create New Message: Ok+RES
		   if (key == 97){
			   choix0_3 = choixUser(rfps);
			   choix = table[choix0_3];
		   }
			messages = (choix0_3<<1)+ELE4205_OK;
			//cout<<messages<<endl;

	}

		}


	//Create New Message: Quit
   messages = 0;
   sprintf(buffer,"%u", messages);
   n = write(sockfd,buffer,sizeof(messages));
   if (n < 0)
		error("ERROR writing to socket");
   // Close the client connection using close
   close(sockfd);

   cout<<"Logout Client"<<endl;



}






















//int main(int argc, char *argv[])
//{
//	// Initialisations
//	int count=0;
//	bool go=1;
//	int choix=1;
//	int oldchoix=choix;
//	int table[4]={1,3,9,12};
//	int nn=0;
//    int sockfd, portno, n;
//    long int bytes;
//    int connectSock;
//    struct sockaddr_in serv_addr;
//    struct hostent *server;
//    uint32_t messages = ELE4205_OK;
//    char buffer[256];
//    portno = PORT;
//    cv::Mat* img;
//    cv::Mat* dst;
//    cv::Mat* currDest;
//    //uchar* sockData;
//    //uchar sockData;
//    int  imgSize ;
//
//	// Populer les resolutions
//	ResolutionFPS rfps[13];
//	populerResolutions(rfps,RES_TABLE);
//
//    // Create TCP socket using socket
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd < 0)
//        error("ERROR opening socket");
//    server = gethostbyname("192.168.7.2");
//    if (server == NULL) {
//        fprintf(stderr,"ERROR, no such host\n");
//        exit(0);
//    }
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    bcopy((char *)server->h_addr,
//         (char *)&serv_addr.sin_addr.s_addr,
//         server->h_length);
//    serv_addr.sin_port = htons(portno);
//
//
//    	// Connection to server socket
//		if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
//			error("ERROR connecting");
//		//choix = choixUser(rfps);
//
//		// Initialize image for reception
//		img =new  cv::Mat; //600x800
//		*img=Mat::zeros( rfps[choix].res.resY,rfps[choix].res.resX, CV_8UC3);
//		currDest=img ;
//		imgSize = currDest->total()*(currDest->elemSize());
//		//sockData=new uchar[imgSize];
//		std::vector<uchar> sockData;
//		sockData.resize(imgSize);
//		//uchar sockData[imgSize];
//
//		   bzero(buffer,253);
//		   messages = (nn%4<<1)+ELE4205_OK;
//			// Send ok to server to send the image
//			sprintf(buffer,"%u", messages);
//			n = write(sockfd,buffer,sizeof(messages));
//			if (n < 0)
//				 error("ERROR writing to socket");
//
//		while(go){
//
//			   char key = (char) waitKey(30);
//			   if (key == 27) break;
//
//
//
//			// Receive image
////		   for (int i = 0; i < imgSize; i += bytes) {
////	//		   cout<<bytes <<endl;
////	//		   cout<< i <<endl;
////			   cout<< imgSize<<endl;
////
////			   if ((bytes = recv(sockfd, &(sockData.front())+i/*sockData +i*/, imgSize  - i, 0)) == -1) {
////				 cout<<"recv failed"<<endl;
////				 return -1;
////				 //i--;
////				}
////		   }
//
//
////			   for (int i = 0; i < imgSize; i += bytes) {
////		//		   cout<<bytes <<endl;
////		//		   cout<< i <<endl;
////				   cout<< imgSize<<endl;
////
////				   if ((bytes = recv(sockfd, &(sockData.front())+i/*sockData +i*/, imgSize  - i, MSG_WAITALL)) == -1) {
////					 cout<<"recv failed"<<endl;
////					 return -1;
////					 //i--;
////					}
////			   }
////
//			   if ((bytes = recv(sockfd,currDest->data /*&(sockData.front())+i/*sockData +i**/, (currDest->rows)*(currDest->cols)*3/*imgSize*/, MSG_WAITALL)) == -1) {
//				 cout<<"recv failed"<<endl;
//				 return -1; }
//		   // Assign pixel value to img
////		   int ptr=0;
////		   for (int i = 0;  i < currDest->rows; i++) {
////			for (int j = 0; j < currDest->cols; j++) {
////			currDest->at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
////			 ptr=ptr+3;
////			 }
////			}
//
//		   // Show image
//		   //imwrite( "/export/tmp/4205_07/projet/projetCamera/Client.png", img);
//
//		   namedWindow("Client", WINDOW_AUTOSIZE );
//		   imshow( "Client", *currDest);
//		   //waitKey(15); waitKey(15);
//
//
//
//		   //if (key == 13){ choix = choixUser(rfps);};
//
//		   count++;
//		   if(count>=100)
//		   {
//				   if(nn>=10000)
//			   {
//				   nn=0;
//
//			   }
//			   choix=table[nn%4];
//			   count=0;
//			   nn++;
//			   if(currDest!=0){delete currDest;}
//			   //if(sockData!=0){delete[] sockData;}
//			   //if(img!=0){delete img;}
//			   //sockData=0;
//			   currDest=0;
//			   img=0;
////				   if((nn%2)){
////					dst=new cv::Mat;
////					*dst=Mat::zeros( rfps[choix].res.resY,rfps[choix].res.resX, CV_8UC3);
////					// Initialize image for reception
////					//cv::resize(*img,*dst,Size(rfps[choix].res.resX,rfps[choix].res.resY)); //600x800
////					currDest=dst;
////					if(img!=0){delete img;}
////					img=0;
////				   }
////				   else
////				   {
////					img =new  cv::Mat; //600x800
////					*img=Mat::zeros( rfps[choix].res.resY,rfps[choix].res.resX, CV_8UC3);
////					//cv::resize(*dst,*img,Size(rfps[choix].res.resX,rfps[choix].res.resY)); //600x800
////					currDest=img;
////					if(dst!=0){delete dst;}
////					dst=0;
////				   }
//			   img =new  cv::Mat; //600x800
//			   *img=Mat::zeros( rfps[choix].res.resY,rfps[choix].res.resX, CV_8UC3);
//			   	currDest=img;
//				imgSize = currDest->total()*(currDest->elemSize());
//				//sockData=new uchar[imgSize];
//				sockData.clear();
//				sockData.resize(imgSize);
//				//bzero((char *) &serv_addr, sizeof(serv_addr)); //clear socketfd after pic change
//				//waitKey(30);
////				   if(nn>=1000)
////				   {
////					   nn=0;
////
////				   }
//
//		   }
//
//		   bzero(buffer,253);
//		   messages = (nn%4<<1)+ELE4205_OK;
//			// Send ok to server to send the image
//			sprintf(buffer,"%u", messages);
//			n = write(sockfd,buffer,sizeof(messages));
//			if (n < 0)
//				 error("ERROR writing to socket");
//			//if(choix!=oldchoix){}
//
//				//bzero((char *) &serv_addr, sizeof(serv_addr));}
//			//oldchoix=choix;
//
//
//
//
//
//
//
//	}
//
//	   messages = 0;
//	   sprintf(buffer,"%u", messages);
//	   n = write(sockfd,buffer,sizeof(messages));
//	   if (n < 0)
//	   		error("ERROR writing to socket");
//	   // Close the client connection using close
//	   close(sockfd);
//
//	   cout<<"Logout Client"<<endl;
//
////	int choix = choixUser(rfps);
//
//    return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
////Receive data here
////
////   for (int i = 0; i < imgSize; i += bytes) {
////   if ((bytes = recv(connectSock, sockData +i, imgSize  - i, 0)) == -1) {
////     //quit("recv failed", 1);
////	   return 1;
////    }
////   }
//
//
//
//
//
//// Mauvais code
////    Mat image;
////    image = imread("4099", CV_LOAD_IMAGE_COLOR);
////    if(! image.data )                              // Check for invalid input
////    {
////        cout <<  "Could not open or find the image" << std::endl ;
////        return -1;
////    }
//
//
//
//
//
////// Irait dans le main apres la population des resolutions
////    if (argc < 3) {
////       fprintf(stderr,"usage %s hostname port\n", argv[0]);
////       exit(0);
////    }
//
//


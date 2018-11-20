

//SERVEUR///

/* boneCVtiming.cpp

 *
 * Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
 * www.derekmolloy.ie
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that source code redistributions retain this notice.
 *
 * This software is provided AS IS and it comes with no warranties of any type.
 */
/*
 * Code taken from https://stackoverflow.com/questions/20314524/c-opencv-image-sending-through-socket
 * 				and http://www.cplusplus.com/doc/tutorial/files/
 */

#include<iostream>
#include<fstream>
//#include<string>
#include<opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>

#include"class.h"
#include "constante.h"
#include "fonction.h"

#define PORT 4099

using namespace cv;
using namespace std;

const string CAM_ID="046d:0825";
const string ADC_LUM="/sys/class/saradc";
const string GPIO228_PB="/sys/class/gpio/gpio228/value";

const int NB_RES=13;
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};


//int main(int argc, char *argv[])
//{
//	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
//	if (detectCamera()==1){
//
//	// fn populer les resolutions
//	ResolutionFPS rfps[13];
//	populerResolutions(rfps,RES_TABLE);
//
//	// Initialisations
//	 int choix;
//	 int choixprec=0;
//	 VideoCapture capture(0);
//	 int clientSock;
//	 char buffer[1024]={'0'};
//	 char *ptrBuffer;
//	 Mat frame;
//	 Mat frame2;
//	 //Mat*frame2;
//	 int imgSize;
//	 uint32_t etat;
//	 Serveur serv(PORT);
//
//	 // Initialize the resolution of the image to be captured
//	 initCapture(capture,rfps[3]);
//	 //cout<<"ready to Accept"<<endl;
//	 // Accept the client connection
//	 serv.servAccept();
//
//
////	 //BOUCLE infinite until the client's QUIT
////	 while(1){
////
////		  // Determiner l'etat (ready/down/button)
////		 etat = findState();
////		 //waitKey(5);
////
////		 // Envoyer l'etat au client
////		  bzero(buffer,1024);
////		  sprintf(buffer,"%u", etat);
////		  n = write(newsockfd,buffer,(int)sizeof(etat));
////		  if (n < 0){ error("ERROR writing to socket");}
////
////		 //// Else Si l'etat est 0
////		 //// reboucler a determiner l'etat
////		 //// aurait besoin de savoir si il y a un escape
////
////		  // Lire le uint_32 envoye par le client
////			 bzero(buffer,1024);
////			 n = read(newsockfd,buffer,1023);
////			 if (n < 0) error("ERROR reading from socket");
////			 //Decoder le uint32 soit ici le OK/Quit
////			 uint32_t result = strtol(buffer,&ptrBuffer,10);
////			 if (test(result,0)){ //Test Ok
////				 //create
////				//frame2=new Mat;
////				 ///////////////Met a jour size;
////				if (test(result,1)){
////					if (test(result,2)) choix =12;//11
////					else choix = 3;//01
////					if(choix!=choixprec){
////							// Initialize the resolution of the image to be captured
////							 initCapture(capture,rfps[choix]);
////							 Mat frame;
////							// Mat frame2;
////							 choixprec=choix;
////
////					}
////				 }
////				else {
////					if (test(result,2)) choix = 9;//10
////					else choix = 1;//00
////					if(choix!=choixprec){
////							// Initialize the resolution of the image to be captured
////							 initCapture(capture,rfps[choix]);
////							 Mat frame;
////							 //Mat frame2;
////							 choixprec=choix;
////
////					}
////				}
////				// cout << result<< endl;
////				//cout << choix<< endl;
////
////		  if (etat == 1 || etat == 3) {
////
////
////
////
////				//Capture
////				captureImage(capture,frame);
////				//Resize
////				//cv::resize(frame,*frame2,Size(rfps[choix].getRes().getX(),rfps[choix].getRes().getY()));
////				//set image size
////				//imgSize = frame2->total()*(frame2->elemSize());
////				imgSize = frame.total()*(frame.elemSize());
////				//cout<<imgSize<<"Serveur!!!"<<endl;
////
////				//Send data
////				//bytes = send(newsockfd, frame2->data, imgSize, 0);
////				bytes = send(newsockfd, frame.data, imgSize, 0);
////				//Clean
//////				if(frame2!=0){delete frame2;}
//////					frame2=0;
////			 }
////
////
////		}
////		else break;
////
////	 	}//FIN DE BOUCLE
////		close(newsockfd);
////		//Close communication
////		close(sockfd);
////     }
////
////	  else
////	  {
////		 cout<<"Pas de ou pas la bonne camera.\n";
//	  }
////
////	cout<<"Logout Serveur"<<endl;
//     return 0;
//}



int main(int argc, char *argv[])
{
	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
	if (detectCamera()==1){

	// fn populer les resolutions
	ResolutionFPS rfps[13];
	populerResolutions(rfps,RES_TABLE);

	// Initialisations
	 int choix;
	 int choixprec=0;
	 VideoCapture capture(0);
	 int sockfd, newsockfd, portno;
	 long int bytes;
	 int clientSock;
	 socklen_t clilen;
	 char buffer[1024]={'0'};
	 char *ptrBuffer;
	 struct sockaddr_in serv_addr, cli_addr; // adress structure
	 int n;
	 Mat frame;
	 Mat frame2;
	 //Mat*frame2;
	 int imgSize;
	 uint32_t etat;


	 //Create a socket()
	 sockfd = socket(AF_INET, SOCK_STREAM, 0); //AFINET  == communication domain Ipv4, SOCK_STREAM is communication type(TCP in our case), 0 is  value for internet protocole
	 if (sockfd < 0)
		error("ERROR opening socket");

	 //Construct a local address structure
	 bzero((char *) &serv_addr, (uint)sizeof(serv_addr));
	 portno = PORT;//DEFINE PORT 4099 to be used as default instead of arg[v]//atoi(argv[1]);
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


	 // Initialize the resolution of the image to be captured
	 initCapture(capture,rfps[3]);

	 cout<<"ready to Accept"<<endl;

	 // Accept the client connection
	 newsockfd = accept(sockfd,
				 (struct sockaddr *) &cli_addr,
				 &clilen);
	 if (newsockfd < 0)
		  error("ERROR on accept");

	 //BOUCLE infinite until the client's QUIT
	 while(1){

		  // Determiner l'etat (ready/down/button)
		 etat = findState();
		 //waitKey(5);

		 // Envoyer l'etat au client
		  bzero(buffer,1024);
		  sprintf(buffer,"%u", etat);
		  n = write(newsockfd,buffer,(int)sizeof(etat));
		  if (n < 0){ error("ERROR writing to socket");}

		 //// Else Si l'etat est 0
		 //// reboucler a determiner l'etat
		 //// aurait besoin de savoir si il y a un escape

		  // Lire le uint_32 envoye par le client
			 bzero(buffer,1024);
			 n = read(newsockfd,buffer,1023);
			 if (n < 0) error("ERROR reading from socket");
			 //Decoder le uint32 soit ici le OK/Quit
			 uint32_t result = strtol(buffer,&ptrBuffer,10);
			 if (test(result,0)){ //Test Ok
				 //create
				//frame2=new Mat;
				 ///////////////Met a jour size;
				if (test(result,1)){
					if (test(result,2)) choix =12;//11
					else choix = 3;//01
					if(choix!=choixprec){
							// Initialize the resolution of the image to be captured
							 initCapture(capture,rfps[choix]);
							 Mat frame;
							// Mat frame2;
							 choixprec=choix;

					}
				 }
				else {
					if (test(result,2)) choix = 9;//10
					else choix = 1;//00
					if(choix!=choixprec){
							// Initialize the resolution of the image to be captured
							 initCapture(capture,rfps[choix]);
							 Mat frame;
							 //Mat frame2;
							 choixprec=choix;

					}
				}
				// cout << result<< endl;
				//cout << choix<< endl;

		  if (etat == 1 || etat == 3) {




				//Capture
				captureImage(capture,frame);
				//Resize
				//cv::resize(frame,*frame2,Size(rfps[choix].getRes().getX(),rfps[choix].getRes().getY()));
				//set image size
				//imgSize = frame2->total()*(frame2->elemSize());
				imgSize = frame.total()*(frame.elemSize());
				//cout<<imgSize<<"Serveur!!!"<<endl;

				//Send data
				//bytes = send(newsockfd, frame2->data, imgSize, 0);
				bytes = send(newsockfd, frame.data, imgSize, 0);
				//Clean
//				if(frame2!=0){delete frame2;}
//					frame2=0;
			 }


		}
		else break;

	 	}//FIN DE BOUCLE
		close(newsockfd);
		//Close communication
		close(sockfd);
     }

	  else
	  {
		 cout<<"Pas de ou pas la bonne camera.\n";
	  }

	cout<<"Logout Serveur"<<endl;
     return 0;
}



////SERVEUR///
//
/////* boneCVtiming.cpp
////
//// *
//// * Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
//// * www.derekmolloy.ie
//// *
//// * Redistribution and use in source and binary forms, with or without modification, are permitted
//// * provided that source code redistributions retain this notice.
//// *
//// * This software is provided AS IS and it comes with no warranties of any type.
//// */
/////*
//// * Code taken from https://stackoverflow.com/questions/20314524/c-opencv-image-sending-through-socket
//// */
////
////#include<iostream>
////#include<fstream>
//////#include<string>
////#include<opencv2/opencv.hpp>
////#include <stdio.h>
////#include <stdlib.h>
////#include <unistd.h>
////#include <string.h>
////#include <sys/types.h>
////#include <sys/socket.h>
////#include <netinet/in.h>
////#include <netdb.h>
////#include <arpa/inet.h>
////#include <vector>
////
////#include"class.h"
////#include "constante.h"
////#include "fonction.h"
////
////#define PORT 4099;
////
////using namespace cv;
////using namespace std;
////
////const string CAM_ID="046d:0825";
////const int NB_RES=13;
////const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};
////
////
////int main(int argc, char *argv[])
////{
////	int choix;
////	int choixprec=5;
////	//Mat frame;
////
////	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
////	if (detectCamera()==1){
////
////	// fn populer les resolutions
////	ResolutionFPS rfps[13];
////	populerResolutions(rfps,RES_TABLE);
////
////	// Initialisations
////	 VideoCapture capture(0);
////	 int sockfd, newsockfd, portno;
////	 long int bytes;
////	 int clientSock;
////	 socklen_t clilen;
////	 char buffer[1024]={'0'};
////	 struct sockaddr_in serv_addr, cli_addr; // adress structure
////	 int n;
////
////	 //Create a socket()
////	 sockfd = socket(AF_INET, SOCK_STREAM, 0); //AFINET  == communication domain Ipv4, SOCK_STREAM is communication type(TCP in our case), 0 is  value for internet protocole
////	 if (sockfd < 0)
////		error("ERROR opening socket");
////
////	 //Construct a local address structure
////	 bzero((char *) &serv_addr, (uint)sizeof(serv_addr));
////	 portno = PORT;//DEFINE PORT 4099 to be used as default instead of arg[v]//atoi(argv[1]);
////	 serv_addr.sin_family = AF_INET;
////	 serv_addr.sin_addr.s_addr = INADDR_ANY;
////	 serv_addr.sin_port = htons(portno);
////
////	 //Assign a port to the number with bind() /Bind the local address
////	 if (bind(sockfd, (struct sockaddr *) &serv_addr,
////			 (uint)sizeof(serv_addr)) < 0)
////			  error("ERROR on binding");
////
////	 //Tell the system to allow connection made to that port with listen/ Mark the socket so it will listen for incoming connect
////	 listen(sockfd,5); //put the socket in passive mode and set 5 as the maximum number for queue
////
////	 clilen = sizeof(cli_addr);
////
////	 // Initialize the resolution of the image to be captured
////	 //initCapture(capture,rfps[choix]);
////
////	 cout<<"ready to Accept"<<endl;
////
////	 // Accept the client connection
////	 newsockfd = accept(sockfd,
////				 (struct sockaddr *) &cli_addr,
////				 &clilen);
////	 if (newsockfd < 0)
////		  error("ERROR on accept");
////
////	 //BOUCLE infinite until the client's QUIT
////	 Mat frame;
////	 while(1){
////
////
////		// Lire le uint_32 envoye par le client
////		 bzero(buffer,1024); //careful easy buffer overlap error.!!
////		 n = read(newsockfd,buffer,1023);
////		 if (n < 0) error("ERROR reading from socket");
////
////		 //Decoder le uint32 soit ici le OK/Quit
////		 uint32_t result = atoi(buffer);
//////		 bool res = test(result,0);
//////		 cout << res << endl;
////
////		 if (test(result,1)){
////			if (test(result,2)) choix = 11;
////			else choix = 7;
////
////			if(choix!=choixprec){
////					// Initialize the resolution of the image to be captured
////					 initCapture(capture,rfps[choix]);
////					 Mat frame;}
////		 }
////		else {
////			if (test(result,2)) choix = 4;
////			else choix = 1;
////
////			if(choix!=choixprec){
////					// Initialize the resolution of the image to be captured
////					 initCapture(capture,rfps[choix]);
////					 Mat frame;}
////		}
////		 choixprec=choix;
////		 if (test(result,0)){
////
////
////
////			 //capture
////			 captureImage(capture,frame);
////			 //reshape to make it continuous
////			 frame = (frame.reshape(0,1));
////
////			 int  imgSize = frame.total()*frame.elemSize();
////			 cout<<sizeof(frame.data);
////			 cout<<imgSize<<endl;
////
////			 // Send data
////			 bytes = send(newsockfd, frame.data, imgSize, 0); //clientSock
////			 cout<<bytes<<endl;
////
////			 // Save the sent image
////			 //Mat image(rfps[choix].res.resY,rfps[choix].res.resX,CV_8UC3,frame.data);
////			 //imwrite("/home/root/IMG_NOW.png",image);
////
//////			 // Show the sent image
//////		     namedWindow( "Server", CV_WINDOW_AUTOSIZE );// Create a window for display.
//////		     imshow( "Server", image );
////
////		 }
////		 else break;
////	 	}
////		 close(newsockfd);
////		 //FIN DE BOUCLE
////
////
////     //Close communication
////     close(sockfd);
////
////     }
////
////	  else
////	  {
////		 cout<<"Pas de ou pas la bonne camera.\n";
////	  }
////		cout<<"Logout Serveur"<<endl;
////
////     return 0;
////}
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
//////// Irait dans main apres/a la place de send
//////    n = write(sockfd,image.data,image.total()*image.channels());
//////    if (n < 0)
//////         error("ERROR writing to socket");
////
////
////
////
////
//////// Irait dans main apres les initialisations
//////     if (argc < 2) {
//////         fprintf(stderr,"ERROR, no port provided\n");
//////         exit(1);
//////     }
////
////
////
////
////
////
////
//////
//////int main()
//////{
//////	int choix;
//////	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
//////	if (detectCamera()==1){
//////
//////	// fn populer les resolutions
//////	ResolutionFPS rfps[13];
//////	populerResolutions(rfps,RES_TABLE);
//////
//////	// fn calculer et populer les framerates
//////	if (populerFPS(rfps)==1){
//////
////////	// fn demander la resolution a l'utilisateur
////////		choix = choixUser(rfps);
////////
////////		// fn enregistrer 5 secondes de video
////////		enregistVideo(rfps,choix);
//////	}
//////	}
//////	  else
//////	  {
//////		 cout<<"Pas de ou pas la bonne camera.\n";
//////	  }
//////
//////	return 0;
//////}
//
//
////SERVEUR///
//
///* boneCVtiming.cpp
//
// *
// * Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
// * www.derekmolloy.ie
// *
// * Redistribution and use in source and binary forms, with or without modification, are permitted
// * provided that source code redistributions retain this notice.
// *
// * This software is provided AS IS and it comes with no warranties of any type.
// */
///*
// * Code taken from https://stackoverflow.com/questions/20314524/c-opencv-image-sending-through-socket
// */
//
//#include<iostream>
//#include<fstream>
////#include<string>
//#include<opencv2/opencv.hpp>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <arpa/inet.h>
//#include <vector>
//
//#include"class.h"
//#include "constante.h"
//#include "fonction.h"
//
//#define PORT 4099;
//
//using namespace cv;
//using namespace std;
//
//const string CAM_ID="046d:0825";
//const int NB_RES=13;
//const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};
//
//
//int main(int argc, char *argv[])
//{
//	int choix;
//	int choixprec=5;
//	char *ptr;
//	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
//	if (detectCamera()==1){
//
//	// fn populer les resolutions
//	ResolutionFPS rfps[13];
//	populerResolutions(rfps,RES_TABLE);
//
//	// Initialisations
//	 VideoCapture capture(0);
//	 int sockfd, newsockfd, portno;
//	 long int bytes;
//	 int clientSock;
//	 socklen_t clilen;
//	 char buffer[1024]={'0'};
//	 struct sockaddr_in serv_addr, cli_addr; // adress structure
//	 int n;
//
//	 //Create a socket()
//	 sockfd = socket(AF_INET, SOCK_STREAM, 0); //AFINET  == communication domain Ipv4, SOCK_STREAM is communication type(TCP in our case), 0 is  value for internet protocole
//	 if (sockfd < 0)
//		error("ERROR opening socket");
//
//	 //Construct a local address structure
//	 bzero((char *) &serv_addr, (uint)sizeof(serv_addr));
//	 portno = PORT;//DEFINE PORT 4099 to be used as default instead of arg[v]//atoi(argv[1]);
//	 serv_addr.sin_family = AF_INET;
//	 serv_addr.sin_addr.s_addr = INADDR_ANY;
//	 serv_addr.sin_port = htons(portno);
//
//	 //Assign a port to the number with bind() /Bind the local address
//	 if (bind(sockfd, (struct sockaddr *) &serv_addr,
//			 (uint)sizeof(serv_addr)) < 0)
//			  error("ERROR on binding");
//
//	 //Tell the system to allow connection made to that port with listen/ Mark the socket so it will listen for incoming connect
//	 listen(sockfd,100); //put the socket in passive mode and set 5 as the maximum number for queue
//
//	 clilen = sizeof(cli_addr);
//
//	 // Initialize the resolution of the image to be captured
//	 initCapture(capture,rfps[3]);
//
//	 cout<<"ready to Accept"<<endl;
//
//	 // Accept the client connection
//	 newsockfd = accept(sockfd,
//				 (struct sockaddr *) &cli_addr,
//				 &clilen);
//	 if (newsockfd < 0)
//		  error("ERROR on accept");
//
//	 //BOUCLE infinite until the client's QUIT
//	 Mat frame;
//	 Mat frame2;
//	 while(1){
//
//
//		// Lire le uint_32 envoye par le client
//		 bzero(buffer,1024);
//		 n = read(newsockfd,buffer,1023);
//		 if (n < 0) error("ERROR reading from socket");
//
//		 //Decoder le uint32 soit ici le OK/Quit
//		 uint32_t result = strtol(buffer,&ptr,10);//atoi
//		 //bool res = test(result,0);
//		 //cout << res << endl;
//
////		 if (test(result,1)){
////			if (test(result,2)) choix = 11;
////			else choix = 7;
////		 }
////		else {
////			if (test(result,2)) choix = 4;
////			else choix = 1;
////		}
//
//		 		 if (test(result,1)){
//		 			if (test(result,2)) choix = 12;
//		 			else choix = 9;
//
//		 			if(choix!=choixprec){
//		 					// Initialize the resolution of the image to be captured
//		 					 //initCapture(capture,rfps[choix]);
//		 					 Mat frame;
//		 					 Mat frame2;
//
//		 			}
//		 		 }
//		 		else {
//		 			if (test(result,2)) choix = 3;
//		 			else choix = 1;
//
//		 			if(choix!=choixprec){
//		 					// Initialize the resolution of the image to be captured
//		 					 //initCapture(capture,rfps[choix]);
//		 					 Mat frame;
//		 					 Mat frame2;
//		 			}
//		 		}
//		 		 choixprec=choix;
//
//		 if (test(result,0)){
//
//
//
//			 //capture
//			 captureImage(capture,frame);
//			 //reshape to make it continuous
//			 cv::resize(frame,frame2,Size(rfps[choix].res.resX,rfps[choix].res.resY));
//			 //frame2 = (frame2.reshape(0,1));
//
//			 int  imgSize = frame2.total()*frame2.elemSize();
//			 //cout<<sizeof(frame.data);
//			 cout<<imgSize<<endl;
//
//			 ////////////
//			 // Send data
//			 bytes = send(newsockfd, frame2.data,frame2.rows*frame2.cols*3 /*imgSize*/, 0); //clientSock
//			 //cout<<bytes<<endl;
//
//			 // Save the sent image
//			 //Mat image(rfps[choix].res.resY,rfps[choix].res.resX,CV_8UC3,frame.data);
//			 //imwrite("/home/root/IMG_NOW.png",image);
//
////			 // Show the sent image
////		     namedWindow( "Server", CV_WINDOW_AUTOSIZE );// Create a window for display.
////		     imshow( "Server", image );
//
//		 }
//		 else break;
//	 	}
//		 close(newsockfd);
//		 //FIN DE BOUCLE
//
//
//     //Close communication
//     close(sockfd);
//
//     }
//
//	  else
//	  {
//		 cout<<"Pas de ou pas la bonne camera.\n";
//	  }
//		cout<<"Logout Serveur"<<endl;
//
//     return 0;
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
//
//
//
//
//
//
//
////// Irait dans main apres/a la place de send
////    n = write(sockfd,image.data,image.total()*image.channels());
////    if (n < 0)
////         error("ERROR writing to socket");
//
//
//
//
//
////// Irait dans main apres les initialisations
////     if (argc < 2) {
////         fprintf(stderr,"ERROR, no port provided\n");
////         exit(1);
////     }
//
//
//
//
//
//
//
////
////int main()
////{
////	int choix;
////	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
////	if (detectCamera()==1){
////
////	// fn populer les resolutions
////	ResolutionFPS rfps[13];
////	populerResolutions(rfps,RES_TABLE);
////
////	// fn calculer et populer les framerates
////	if (populerFPS(rfps)==1){
////
//////	// fn demander la resolution a l'utilisateur
//////		choix = choixUser(rfps);
//////
//////		// fn enregistrer 5 secondes de video
//////		enregistVideo(rfps,choix);
////	}
////	}
////	  else
////	  {
////		 cout<<"Pas de ou pas la bonne camera.\n";
////	  }
////
////	return 0;
////}
//


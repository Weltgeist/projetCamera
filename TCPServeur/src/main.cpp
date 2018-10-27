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



#include <cstdlib>
#include<cstring>
//#include<iostream>
#include<fstream>
//#include<string>
#include<opencv2/opencv.hpp>
#include<time.h>


//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//

#include"class.h"
#include "constante.h"
#include "fonction.h"

#define PORT 4099;

using namespace cv;
using namespace std;
//using namespace sys;



const string CAM_ID="046d:0825";
const int NB_RES=13;
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};

//
//int main()
//{
//	int choix;
//	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
//	if (detectCamera()==1){
//
//	// fn populer les resolutions
//	ResolutionFPS rfps[13];
//	populerResolutions(rfps,RES_TABLE);
//
//	// fn calculer et populer les framerates
//	if (populerFPS(rfps)==1){
//
////	// fn demander la resolution a l'utilisateur
////		choix = choixUser(rfps);
////
////		// fn enregistrer 5 secondes de video
////		enregistVideo(rfps,choix);
//	}
//	}
//	  else
//	  {
//		 cout<<"Pas de ou pas la bonne camera.\n";
//	  }
//
//	return 0;
//}




void error(const char *msg)
{
    perror(msg);
    exit(1);
}






int main(int argc, char *argv[])
{
		int choix=7;
		// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
		if (detectCamera()==1){

		// fn populer les resolutions
		ResolutionFPS rfps[13];
		populerResolutions(rfps,RES_TABLE);

		// fn calculer et populer les framerates
		if (1/*populerFPS(rfps)==1*/){


	/////////
     VideoCapture capture(0);
     int sockfd, newsockfd, portno;
     long int bytes;
     int clientSock;
     socklen_t clilen;
     char buffer[1024];
     struct sockaddr_in serv_addr, cli_addr; // adress structure
     int n;
//     if (argc < 2) {
//         fprintf(stderr,"ERROR, no port provided\n");
//         exit(1);
//     }
     //Create a socket()
     sockfd = socket(AF_INET, SOCK_STREAM, 0); //AFINET  == communication domain Ipv4, SOCK_STREAM is communication type(TCP in our case), 0 is  value for internet protocole
     if (sockfd < 0)
        error("ERROR opening socket");
     //Construct a local address structure
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = PORT;//DEFINE PORT 4099 to be used as default instead of arg[v]//atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     //Assign a port to the number with bind() /Bind the local adress
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     cout << "ici";
     //Tell the system to allow connection made to that port with listen/ Mark the socket so it will listen for incomming connect
     listen(sockfd,5); //put the socket in passive mode and set 5 as the maximum number for queue
     cout << "ici2";
     clilen = sizeof(cli_addr);
     initCapture(capture,rfps[choix]);
     //BOUCLE!!!!
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     bzero(buffer,1024);
     //Decoder le uint32 ou le OK/Quit

     n = read(newsockfd,buffer,1023);
     if (n < 0) error("ERROR reading from socket");

     Mat frame; //
     //capture
     captureImage(capture,frame);
     //reshape
     frame = (frame.reshape(0,1)); // to make it continuous

     int  imgSize = frame.total()*frame.elemSize();

     // Send data here
     bytes = send(clientSock, frame.data, imgSize, 0);



     Mat image(rfps[choix].res.resX,rfps[choix].res.resY,CV_8UC3,*buffer);
    imwrite("/home/root/IMG_NOW.png",image);


     close(newsockfd);

     //FIN DE BOUCLE
     //Close communication
     close(sockfd);

     namedWindow( "Server", CV_WINDOW_AUTOSIZE );// Create a window for display.
     imshow( "Server", image );
     waitKey(0);

     ////////////////////
     ///
     ///
		}
		else
		     	  {
		     		 cout<<"Calcul des FPS ne fonctionne pas.\n";
		     	  }
     	}
     	  else
     	  {
     		 cout<<"Pas de ou pas la bonne camera.\n";
     	  }
     return 0;
}


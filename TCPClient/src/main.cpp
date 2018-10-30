
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
	// Initialisations
	int count=0;
	bool go=1;
	int choix=1;
	int table[4]={1,4,7,11};
	int nn=0;
    int sockfd, portno, n;
    long int bytes;
    int connectSock;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    uint32_t messages = ELE4205_OK;
    char buffer[256];
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
		//choix = choixUser(rfps);

		while(go){

			   count++;
			   if(count>=100)
			   {
				   choix=table[nn%4];
				   count=0;
				   nn++;
				   if(nn>=1000)
				   {
					   nn=0;

				   }

			   }

			   messages = (nn%4<<1)+ELE4205_OK;

			// Send ok to server to send the image
			sprintf(buffer,"%u", messages);
			n = write(sockfd,buffer,sizeof(messages));
			if (n < 0)
				 error("ERROR writing to socket");

			// Initialize image for reception
			Mat  img = Mat::zeros( rfps[choix].res.resY,rfps[choix].res.resX, CV_8UC3); //600x800
			int  imgSize = img.total()*img.elemSize();
			uchar sockData[imgSize];

			// Receive image
		   for (int i = 0; i < imgSize; i += bytes) {
	//		   cout<<bytes <<endl;
	//		   cout<< i <<endl;
	//		   cout<< imgSize<<endl;
			   ///////////
			   if ((bytes = recv(sockfd, sockData +i, imgSize  - i, 0)) == -1) {
				 cout<<"recv failed"<<endl;
				 return -1;
				 //i--;
				}
		   }

		   // Assign pixel value to img
		   int ptr=0;
		   for (int i = 0;  i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
			 img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
			 ptr=ptr+3;
			 }
			}

		   // Show image
		   //imwrite( "/export/tmp/4205_07/projet/projetCamera/Client.png", img);

		   namedWindow("Client", WINDOW_AUTOSIZE );
		   imshow( "Client", img);
		   //waitKey(15); waitKey(15);


		   char key = (char) waitKey(30);
		   if (key == 27) break;
		   //if (key == 13){ choix = choixUser(rfps);};



	}

	   messages = 0;
	   sprintf(buffer,"%u", messages);
	   n = write(sockfd,buffer,sizeof(messages));
	   if (n < 0)
	   		error("ERROR writing to socket");
	   // Close the client connection using close
	   close(sockfd);

	   cout<<"Logout Client"<<endl;

//	int choix = choixUser(rfps);

    return 0;
}











//Receive data here
//
//   for (int i = 0; i < imgSize; i += bytes) {
//   if ((bytes = recv(connectSock, sockData +i, imgSize  - i, 0)) == -1) {
//     //quit("recv failed", 1);
//	   return 1;
//    }
//   }





// Mauvais code
//    Mat image;
//    image = imread("4099", CV_LOAD_IMAGE_COLOR);
//    if(! image.data )                              // Check for invalid input
//    {
//        cout <<  "Could not open or find the image" << std::endl ;
//        return -1;
//    }





//// Irait dans le main apres la population des resolutions
//    if (argc < 3) {
//       fprintf(stderr,"usage %s hostname port\n", argv[0]);
//       exit(0);
//    }




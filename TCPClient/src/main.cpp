
//CLIENT///

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/core.hpp>
//#include<opencv2/imgproc.hpp>
//#include<opencv2/videoio.hpp>
#include <iostream>
//
#include"class.h"
////#include "constante.h"
#include "fonction.h"


using namespace cv;
using namespace std;

#define PORT 4099;


const int NB_RES=13;
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	int choix=7;
    int sockfd, portno, n;
    long int bytes;
    int connectSock;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

	// fn populer les resolutions
	ResolutionFPS rfps[13];
	populerResolutions(rfps,RES_TABLE);

//    if (argc < 3) {
//       fprintf(stderr,"usage %s hostname port\n", argv[0]);
//       exit(0);
//    }
    portno =PORT;// atoi(argv[2]);
//		Create TCP socket using socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("192.168.7.2"/*argv[1]*/);
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
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

//    Mat image;
//    image = imread("4099", CV_LOAD_IMAGE_COLOR);
//    if(! image.data )                              // Check for invalid input
//    {
//        cout <<  "Could not open or find the image" << std::endl ;
//        return -1;
//    }


 //Repeat operation,to receive data, to covert socket data to picture
//
Mat  img = Mat::zeros( rfps[choix].res.resX,rfps[choix].res.resY, CV_8UC3);//CV_8UC3
//   int  imgSize = img.total()*img.elemSize();
  // uchar sockData[imgSize];

 //Receive data here
/*
//
//   for (int i = 0; i < imgSize; i += bytes) {
//   if ((bytes = recv(connectSock, sockData +i, imgSize  - i, 0)) == -1) {
//     //quit("recv failed", 1);
//	   return 1;
//    }
//   }
*/

 // Assign pixel value to img

// int ptr=0;
// for (int i = 0;  i < img.rows; i++) {
//  for (int j = 0; j < img.cols; j++) {
//   img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
//   ptr=ptr+3;
//   }
//  }
//    n = write(sockfd,image.data,image.total()*image.channels());
//    if (n < 0)
//         error("ERROR writing to socket");
//		Close the client connection using close
  //  close(sockfd);

  //  namedWindow( "Client", CV_WINDOW_AUTOSIZE );// Create a window for display.
 //   imshow( "Client", image );
 //   waitKey(0);
    return 0;
}


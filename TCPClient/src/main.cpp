
//CLIENT///
/*
 * Code taken from https://stackoverflow.com/questions/20314524/c-opencv-image-sending-through-socket
 * createDir-Code taken from https://www.geeksforgeeks.org/create-directoryfolder-cc-program/
 * Code taken from https://docs.opencv.org/2.4.5/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html#cascade-classifier
 * Code taken from https://www.superdatascience.com/opencv-face-recognition/?fbclid=IwAR06Q9KKUCob0067iXzQogP6oozvgMveGPpSD-v7IscJ1Mi1DOHSWlYcrlw
 * read_csv - Code taken from https://docs.opencv.org/3.4/da/d60/tutorial_face_main.html
 * https://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_api.html
 */

/*
 * Copyright (c) 2011. Philipp Wagner <bytefish[at]gmx[dot]de>.
 * Released to public domain under terms of the BSD Simplified license.
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
//#include <vector>
#include <opencv2/opencv.hpp>
// #include "opencv2/objdetect/objdetect.hpp"
// #include "opencv2/highgui/highgui.hpp"
// #include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
//#include <sys/types.h>
//#include <signal.h>
#include"class.h"
//#include "constante.h"
#include "fonction.h"

using namespace cv;
using namespace std;

#define PORT 4099;
#define ELE4205_OK 0b1;

const int NB_RES=13;
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};




/**
 * \fn main
 * \brief Client will create a TCP socket and connect to the server. Client will receive server status and client will send a request for a picture. Client will
 * receive picture data from Server, create a picture from data and show it. Depending on server status, the picture may be saved and face detection and recognition
 * may be applied to it. A delay of 30 ms allows the user to quit using the escape key or to change the resolution of the sent picture using "a" key.
 * @param argc Not used
 * @param argv Not used
 * @return 0 if ended correctly.
 */
int main(int argc, char *argv[])
{
	// Initialisations
	int count=0;
	bool go=1;
	int choix=1;
	int choix0_3=0;
	int table[4]={1,3,9,12};
	int nn=0;
    int sockfd, portno;
    int n;
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
	Mat*  img2;
	int  imgSize;
	pid_t pid ;
	int ctr_img = 0;
	char sctr_img[50];
    portno = PORT;
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    String face_cascade_name = "haarcascade_frontalface_alt.xml" ;
    String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
    int mode; //0 training/collect data , 1 reconaissance
    int personne;
    //string label="SAM";
    string PATH="/export/tmp/4205_07/projet"; //Path dans lequel les folders contenant les photos seront places
    string PathCSV = "/export/tmp/4205_07/projet/Face_Label_DATA.csv";
    vector<Mat> listImages;
	vector<string> labels;
	vector<string> listeNoms;

    //createDir(PATH,label);


	//std::ofstream myfile ("/home/root/LOG.txt");
//    ofstream file("/export/tmp/4205_07/projet/Face_Label_DATA.csv",ofstream::out);
//    if (!file) {
//        string error_message = "Could not open file";
//        //CV_Error(Error::StsBadArg, error_message);
//        cout<<error_message<<endl;
//    }

	mode = choixMode();
	if (mode == 0){
		personne = choixPersonne(listeNoms, listImages, labels, PATH, PathCSV, ctr_img);
		ctr_img = find_ctr_img(listeNoms, listImages, labels, PATH, PathCSV, personne);
	}
//	cout << personne << endl;
//	cout << ctr_img << endl;
	cout << mode << endl;

	// Populer les resolutions
	ResolutionFPS rfps[13];
	populerResolutions(rfps,RES_TABLE);

   // Load the cascades
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

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

		 // Send ok to server to send the image
		sprintf(buffer,"%u", messages);
		n = write(sockfd,buffer,sizeof(messages));
		if (n < 0){ error("ERROR writing to socket");}


		// Initialize image for reception
		img=new Mat;
		*img= Mat::zeros( rfps[choix].getRes().getY() ,rfps[choix].getRes().getX() , CV_8UC3);
		//Mat img = Mat::zeros( rfps[choix].getRes().getY() ,rfps[choix].getRes().getX() , CV_8UC3);
		imgSize = img->total()*(img->elemSize());
		//imgSize = img.total()*(img.elemSize());
		//cout<<imgSize<<endl;
		//uchar sockData[imgSize];
		sockData.clear();
		sockData.resize(imgSize);////////////////////////SKIPS UCHAR ALL TOGETHER,BUT WE CAN ALSO USE A METHOD WITH UCHAR
		//WAITS!!!!!!!!!!!30 MS
		key =static_cast<char> (waitKey(30));  /*(char)*/

			if (state == 1 || state == 3) { // Tant qu'il y a de la lumiere
				// Receive image & assign to pixel
				 if ((bytes = recv(sockfd, img->data, imgSize, MSG_WAITALL)) == -1)
					 {cout<<"recv failed"<<endl;return -1;}


				 if (state == 3){
					 ctr_img++;
					pid = fork();
					if(pid == 0)
					{

						//img2=new Mat;
						//*img2=*img;

						sprintf(sctr_img,"/export/tmp/4205_07/projet/%s/cropresizePIC%u.png",listeNoms[personne].c_str(),ctr_img);
						imwrite(sctr_img, *img);

						if (mode == 0){ //Apprentissage
							writeToCSV("/export/tmp/4205_07/projet/Face_Label_DATA.csv",sctr_img, listeNoms[personne], ctr_img);

							//img2 =imread("/export/tmp/4205_07/projet/PIC%u.png");
							detectAndDisplay(sctr_img,face_cascade,eyes_cascade,ctr_img,PATH+"/"+listeNoms[personne]);
						}
						////////////////////////////
//						else if (mode == 1){ //Reconnaissance
//							sprintf(sctr_img,"/export/tmp/4205_07/projet/recon.png");
//							imwrite(sctr_img, *img);
//							//detectAndDisplay(sctr_img,face_cascade,eyes_cascade,ctr_img,PATH+"/");
//							recon(listeNoms, listImages, labels, PATH, PathCSV, personne, *img); //pas img, aller chercher le cropresize?
//						}

						//if(img2!=0){delete img2;}
						//img2=0;
						exit(0);

					}
					else if (pid>0)
					{
					  //myfile << pid<<endl;
					   // Show image
					   namedWindow("Client", WINDOW_AUTOSIZE );
					   imshow( "Client", *img);
						//cout<<"Parent"<<pid<<endl; //utile pour debug

					   ///////////////////////////
					   if (mode == 1){ //Reconnaissance
							sprintf(sctr_img,"/export/tmp/4205_07/projet/recon.png");
							imwrite(sctr_img, *img);
							//detectAndDisplay(sctr_img,face_cascade,eyes_cascade,ctr_img,PATH+"/");
							recon(listeNoms, listImages, labels, PATH, PathCSV, personne, *img); //pas img, aller chercher le cropresize?
						}

				}
				else
				{
					cout << "PID failed" << endl;
				}
				 }

				 else {
					 // Show image
				   namedWindow("Client", WINDOW_AUTOSIZE );
				   imshow( "Client", *img);
					//cout<<"Parent"<<pid<<endl; //utile pour debug
				 }
			   //Prepare next set;
				if(img!=0){delete img;}
				img=0;




			}

			//Test key
		   if (key == 27) {break;}
		   //Create New Message: Ok+RES
		   if (key == 97){ //a
			   choix0_3 = choixUser(rfps);
			   choix = table[choix0_3];
		   }
			messages = (choix0_3<<1)+ELE4205_OK;
			//cout<<messages<<endl;
			if (key == 98){ //b
				mode = choixMode();
				if (mode == 0){
					personne = choixPersonne(listeNoms, listImages, labels, PATH, PathCSV, ctr_img);
					ctr_img = find_ctr_img(listeNoms, listImages, labels, PATH, PathCSV, personne);
				}
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

//  file.close();


   cout<<"Logout Client"<<endl;

   return 0;

}



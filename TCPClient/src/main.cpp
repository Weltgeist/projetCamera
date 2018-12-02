
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
#include <opencv2/opencv.hpp>
#include <iostream>
#include"class.h"
//#include "constante.h"
#include "fonction.h"

using namespace cv;
using namespace std;

#define PORT 4099
#define ELE4205_OK 0b1

const int NB_RES=13;
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};




/**
 * \fn main
 * \brief Client will create a TCP socket and connect to the server. Client will receive server status and client will send a request for a picture. Client will
 * receive picture data from Server, create a picture from data and show it. Depending on server status, the picture may be saved and face detection and recognition
 * may be applied to it. A delay of 30 ms allows the user to quit using the escape key or to change the resolution of the sent picture using "a" key.
 * @return 0 if ended correctly.
 */
int main()
{
	// Initialisations
	int choix=1;
	int choix0_3=0;
	int table[4]={1,3,9,12};
	uint32_t state;
    long int bytes;
    char key;
	int ctr_img = 0;
    int mode; //0 training/collect data , 1 reconaissance
    int personne = 0;
	Client client;
	client.set_portno(PORT);
	client.set_messages(ELE4205_OK);


	// Choix du mode (apprentissage ou reconnaissance)
	mode = choixMode();
	if (mode == 0){
		personne = client.choixPersonne(ctr_img);
		ctr_img = client.find_ctr_img(personne);
	}
	// Populer les resolutions
	ResolutionFPS rfps[13];
	populerResolutions(rfps,RES_TABLE);
   // Load the cascades
   client.loadCascades();
	// Client initialization
   client.initClient();
	// Connection to server socket
   client.clientConnect();

	while(true){
		// Client receives server status and sends request for image
		state = client.clientRcvSend();
		// Initialize image for reception
		client.clientInitImg(rfps,choix);
		// Waitkey for quit, resolution change or mode change
		key =static_cast<char> (waitKey(30));

		if (state == 1 || state == 3) { // Tant qu'il y a de la lumiere
			// Receive image & assign to pixel
			 if ((bytes = recv(client.get_sockfd(), (client.get_img())->data, client.get_imgSize(), MSG_WAITALL)) == -1)
				 {cout<<"recv failed"<<endl;return -1;}

			 if (state == 3){
				ctr_img++;
				// Fork containing detection and recon
				client.clientFork(mode, ctr_img, personne);
			 }
			 else {
				// Show image
			   client.showImage();
			 }

		   //Prepare next set
			 client.deleteimg();
		}

		//Test key
	   if (key == 27) {break;}
	   //Create New Message: Ok+RES
	   if (key == 97){ //a
		   choix0_3 = choixUser(rfps);
		   choix = table[choix0_3];
	   }
		client.set_messages((choix0_3<<1)+ELE4205_OK);
		if (key == 98){ //b
			mode = choixMode();
			if (mode == 0){
				personne = client.choixPersonne(ctr_img);
				ctr_img = client.find_ctr_img(personne);
			}
		}
	}

	client.clientQuit();

   return 0;

}



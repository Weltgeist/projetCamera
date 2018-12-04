
/**
 * \file main.cpp
 * \brief  Implements the server side of the TCP connection.
 * \author ELE4205_07
 * \date 3 december 2018
 *
 */

/* boneCVtiming.cpp
 * Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
 * www.derekmolloy.ie
 */
/*
 * Code taken from https://stackoverflow.com/questions/20314524/c-opencv-image-sending-through-socket
 * 			   and http://www.cplusplus.com/doc/tutorial/files/
 */

 /**
\mainpage
The current code is the TCP server part of the project for class ELE4205 for team 07.
The server allows the user to send a stream of images according to the resolution demanded by the client.
The server will determine its state according to presence of light and release of a pushbutton to send to the client.
\image  ORIGIN1.png
The program uses OpenCV as a library for image capture and processing.
**/
 
 
#include<iostream>
#include<fstream>
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
#include"constante.h"
#include "fonction.h"

#define PORT 4099

using namespace cv;
using namespace std;

/**
 * \var CAM_ID
 * \brief The id of the camera as returned by lsusb command.
 */
const string CAM_ID="046d:0825";
/**
 * \var ADC_LUM
 * \brief The file path for the driver of the light sensor.
 */
const string ADC_LUM="/sys/class/saradc";
/**
 * \var GPIO228_PB
 * \brief The file path for the driver of the push-button.
 */
const string GPIO228_PB="/sys/class/gpio/gpio228/value";
/**
 * \var NB_RES
 * \brief The number of possible resolutions for the camera.
 */
const int NB_RES=13;
/**
 * \var RES_TABLE
 * \brief The list of possible resolutions with their value in x and y respectively.
 */
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};

/**
 * \fn main
 * \brief The function verifies if the correct camera is connected, then initializes the server TCP socket
 * and the capture of the image. It accepts the connect demand from the client, then finds the state of the
 * server (light or not, push-button release or not) and sends it to the client. The client responds with 
 * a demand for an image, that is decoded to know which resolution of image has to be used. If the resolution
 * changes, a new image is initialized. The server sends the image and to te finding of the server state. 
 * The server closes the connection if it receives a quit command instead of a demand for an image.
 * \return 0 if ended correctly.
 */
int main()
{
	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
	if (detectCamera()==1){

		// Initialisations
		 int choix;
		 int choixprec=0;
		 VideoCapture capture(0);
		 int clientSock;
		 Mat frame;
		 Mat frame2;
		 uint32_t etat;
		 uint32_t result;
		 Serveur serveur;
		 Resolution res[13];

		 // fn populer les resolutions
		populerResolutions(res,RES_TABLE);
		 // Initialize TCP server
		 serveur.initServeur(PORT);
		 // Initialize the resolution of the image to be captured
		 initCapture(capture,res[3]);
		 cout<<"Ready to accept"<<endl;
		 // Accept the client connection
		 serveur.servAccept();
		 //Infinite loop until the client's QUIT
		 while(1){
			  // Determiner l'etat (ready/down/button)
			 etat = findState();
			 // Envoyer l'etat, recevoir demande, decoder demande
			 result = serveur.servSendRecv(etat);
			 if (test(result,0)){ //Test Ok
				if (test(result,1)){
					if (test(result,2)) choix =12; //11
					else choix = 3; //01
					if(choix!=choixprec){
						// Initialize the resolution of the image to be captured
						 initCapture(capture,res[choix]);
						 Mat frame;
						 choixprec=choix;
					}
				 }
				else {
					if (test(result,2)) choix = 9; //10
					else choix = 1; //00
					if(choix!=choixprec){
						// Initialize the resolution of the image to be captured
						 initCapture(capture,res[choix]);
						 Mat frame;
						 choixprec=choix;
					}
				}
				if (etat == 1 || etat == 3) {
					serveur.servCaptureSend(frame, capture); }
			}
			else break;
		 }
		 serveur.servClose();
		 }
	  else
	  {
		 cout<<"Pas de ou pas la bonne camera.\n";
	  }

	cout<<"Logout Serveur"<<endl;
     return 0;
}




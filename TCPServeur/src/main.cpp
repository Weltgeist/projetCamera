

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


int main(int argc, char *argv[])
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

		 // fn populer les resolutions
		ResolutionFPS rfps[13];
		populerResolutions(rfps,RES_TABLE);
		 // Initialize TCP server
		 serveur.initServeur(PORT);
		 // Initialize the resolution of the image to be captured
		 initCapture(capture,rfps[3]);
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
					/////////
					if(choix!=choixprec){
						// Initialize the resolution of the image to be captured
						 initCapture(capture,rfps[choix]);
						 Mat frame;
						 choixprec=choix;
					}
					//////////
				 }
				else {
					if (test(result,2)) choix = 9; //10
					else choix = 1; //00
					///////////
					if(choix!=choixprec){
						// Initialize the resolution of the image to be captured
						 initCapture(capture,rfps[choix]);
						 Mat frame;
						 choixprec=choix;
					}
					///////////
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




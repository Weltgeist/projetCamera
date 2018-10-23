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
#include<iostream>
#include<fstream>
#include<string>
#include<opencv2/opencv.hpp>
#include<time.h>
#include"class.h"
#include "constante.h"
#include "fonction.h"

using namespace std;
using namespace cv;


const string CAM_ID="046d:0825";
const int NB_RES=13;
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};


int main()
{
	int choix;
	// fn detecter bonne camera (trouver id 046d:0825 dans les devices usb)
	if (detectCamera()==1){

	// fn populer les resolutions
	ResolutionFPS rfps[13];
	populerResolutions(rfps,RES_TABLE);

	// fn calculer et populer les framerates
	if (populerFPS(rfps)==1){

	// fn demander la resolution a l'utilisateur
		choix = choixUser(rfps);

		// fn enregistrer 5 secondes de video
		enregistVideo(rfps,choix);
	}
	}
	  else
	  {
		 cout<<"Pas de ou pas la bonne camera.\n";
	  }

	return 0;
}



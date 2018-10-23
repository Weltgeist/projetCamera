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
	std::system("lsusb | grep 046d:0825  > /home/root/trouver_cam.txt");

	  ////FROM http://www.cplusplus.com/doc/tutorial/files/
	  streampos begin,end;
	  ifstream myfile ("/home/root/trouver_cam.txt", ios::binary);
	  begin = myfile.tellg();
	  myfile.seekg (0, ios::end);
	  end = myfile.tellg();
	  myfile.close();
	  // cout << "size is: " << (end-begin) << " bytes.\n";
	  if((end-begin)!=0){
		  cout << "La bonne camera a ete trouvee.\n";



	// fn populer les resolutions
	ResolutionFPS rfps[13];
	populerResolutions(rfps,RES_TABLE);



	// fn calculer et populer les framerates
	// populerFPS();

	//	string nom_capture;

	for (int i = 0; i < 13; i++)
	{

		VideoCapture capture(0);
		capture.set(CV_CAP_PROP_FRAME_WIDTH,rfps[i].res.resX);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[i].res.resY);
		if(!capture.isOpened()){
			cout << "Failed to connect to the camera." << endl;
		}
		Mat frame, edges;
		// calibration de la camera
		capture >> frame;
		capture >> frame;

		struct timespec start, end;
		clock_gettime( CLOCK_REALTIME, &start );

		int frames=2;

		for(int i=0; i<frames; i++){
			capture >> frame;
			if(frame.empty()){
			cout << "Failed to capture an image" << endl;
			return -1;
			}
//	    	cvtColor(frame, edges, CV_BGR2GRAY);
//	    	Canny(edges, edges, 0, 30, 3);
		}

		clock_gettime( CLOCK_REALTIME, &end );
		double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0d;
		// cout << "It took " << difference << " seconds to process " << frames << " frames" << endl;
		cout << "Capturing and processing " << frames/difference << " frames per second for " << rfps[i].res.resX << "x" << rfps[i].res.resY << endl;
		rfps[i].fps = frames/difference;

//	    nom_capture = "capture"+itoa(i)+".png";
//	    cin >> nom_capture;
//		imwrite(nom_capture, frame);
		}





	// fn demander la resolution a l'utilisateur
		cout << "Choisissez une resolution parmi les suivantes:\n";
		for (int i = 0; i < 13; i++){
			cout << i+1 << ": " << rfps[i].res.resX << "x" << rfps[i].res.resY << "\n";
		}
		cin >> choix;
		while (!cin || choix < 1 || choix > 13) { //!isdigit(choix) ||
			cout << "L'entree doit etre un nombre de 1 a 13, choisissez a nouveau.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> choix;
		}
		choix--;






		// fn enregistrer 5 secondes de video
		VideoWriter vidW("/home/root/capture-liv1.avi",CV_FOURCC('M','J','P','G'),round(rfps[choix].fps),Size(rfps[choix].res.resX,rfps[choix].res.resY),true);
		VideoCapture capture2(0);

		capture2.set(CV_CAP_PROP_FRAME_WIDTH,rfps[choix].res.resX);
		capture2.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[choix].res.resY);
		if(!capture2.isOpened()){
			cout << "Failed to connect to the camera." << endl;
		}
		Mat video;

		for (int i = 0; i < 5*((int)rfps[choix].fps); i++)
		{
			cout << "Saving Frame number: " << i <<" in video." <<endl;
			capture2 >> video;
			vidW.write(video);
		}




	  }
	  else
	  {
		 cout<<"Pas de ou pas la bonne camera.\n";
	  }

	return 0;

}



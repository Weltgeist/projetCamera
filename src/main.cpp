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






int main()
{

	string nom_capture;

	// fn detecter bonne camera
		// trouver id 046d:0825

	// fn populer les resolution
	ResolutionFPS rfps[13];

	rfps[0].res.resX = 176;
	rfps[0].res.resY = 144;

	rfps[1].res.resX = 160;
	rfps[1].res.resY= 120;

	rfps[2].res.resX = 320;
	rfps[2].res.resY = 176;

	rfps[3].res.resX = 320;
	rfps[3].res.resY = 240;

	rfps[4].res.resX = 352;
	rfps[4].res.resY = 288;

	rfps[5].res.resX = 432;
	rfps[5].res.resY = 240;

	rfps[6].res.resX = 800;
	rfps[6].res.resY = 600;

	rfps[7].res.resX = 864;
	rfps[7].res.resY = 480;

	rfps[8].res.resX = 960;
	rfps[8].res.resY = 544;

	rfps[9].res.resX = 960;
	rfps[9].res.resY = 720;

	rfps[10].res.resX = 1184;
	rfps[10].res.resY = 656;

	rfps[11].res.resX = 1280;
	rfps[11].res.resY = 720;

	rfps[12].res.resX = 1280;
	rfps[12].res.resY = 960;




	// fn calculer et populer les framerates
	for (int i = 0; i < 4; i++)
	{
	  VideoCapture capture(0);
	    capture.set(CV_CAP_PROP_FRAME_WIDTH,rfps[i].res.resX);
	    capture.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[i].res.resY);
	    if(!capture.isOpened()){
		    cout << "Failed to connect to the camera." << endl;
	    }
	    Mat frame, edges;

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
		cout << "It took " << difference << " seconds to process " << frames << " frames" << endl;
		cout << "Capturing and processing " << frames/difference << " frames per second " << endl;
		rfps[i].fps = frames/difference;

//	    nom_capture = "capture"+itoa(i)+".png";
	    cin >> nom_capture;
		imwrite(nom_capture, frame);
	}

//		frameRes[i].fps = boneCVtiming();

	// Write to file
	// Taken from "http://www.cplusplus.com/doc/tutorial/files/" and modified
//	ofstream myfile ("Frame_resolution_timing.txt");
//	if (myfile.is_open())
//	{
//		for (int i = 0; i < 13; i++){
//			myfile << "For resolution " << frameRes[i].resX << " x " << frameRes[i].resY << " there are " << frameRes[i].fps << " fps.\n";
//		}
//	    	myfile.close();
//	  }
//	  else cout << "Unable to open file";



	// fn demander la resolution a l'utilisateur
		cout << "Choisissez une resolution parmi les suivantes:\n";
		for (int i = 0; i < 13; i++){
			cout << i+1 << ": " << rfps[i].res.resX << "x" << rfps[i].res.resY << "\n";
		}
//		int input;
//		cin >> input;
//		if (isdigit(input) && input >=1 && input <= 13){}
//		else
//			cout << "L'entree doit etre un nombre de 1 a 13";






	// fn enregistrer 5 secondes de video









	return 0;

}

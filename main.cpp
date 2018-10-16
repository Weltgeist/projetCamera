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

#include<iostream>
#include<fstream>
#include<opencv2/opencv.hpp>
#include<time.h>
#include "class.h"
#include "constante.h"
#include "fonction.h"
using namespace std;
using namespace cv;


double boneCVtiming()
{
    VideoCapture capture(0);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
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
    	cvtColor(frame, edges, CV_BGR2GRAY);
    	Canny(edges, edges, 0, 30, 3);
    }

    clock_gettime( CLOCK_REALTIME, &end );
    double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0d;
    cout << "It took " << difference << " seconds to process " << frames << " frames" << endl;
    cout << "Capturing and processing " << frames/difference << " frames per second " << endl;

    imwrite("edges.png", edges);
    imwrite("capture.png", frame);
    return difference;
}



int main()
{
	struct frameRes
		{
		int resX;
		int resY;
		double fps;
		} frameRes[13];

	frameRes[0].resX = 176;
	frameRes[0].resY = 144;

	frameRes[1].resX = 160;
	frameRes[1].resY = 120;

	frameRes[2].resX = 320;
	frameRes[2].resY = 176;

	frameRes[3].resX = 320;
	frameRes[3].resY = 240;

	frameRes[4].resX = 352;
	frameRes[4].resY = 288;

	frameRes[5].resX = 432;
	frameRes[5].resY = 240;

	frameRes[6].resX = 800;
	frameRes[6].resY = 600;

	frameRes[7].resX = 864;
	frameRes[7].resY = 480;

	frameRes[8].resX = 960;
	frameRes[8].resY = 544;

	frameRes[9].resX = 960;
	frameRes[9].resY = 720;

	frameRes[10].resX = 1184;
	frameRes[10].resY = 656;

	frameRes[11].resX = 1280;
	frameRes[11].resY = 720;

	frameRes[12].resX = 1280;
	frameRes[12].resY = 960;


	// Determine framerate
	for (int i = 0; i < 13; i++)
	{
		frameRes[i].fps = boneCVtiming();
	}

	// Write to file
	// Taken from "http://www.cplusplus.com/doc/tutorial/files/" and modified
	ofstream myfile ("Frame_resolution_timing.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 13; i++){	    
			myfile << "For resolution " << frameRes[i].resX << " x " << frameRes[i].resY << " there are " << frameRes[i].fps << " fps.\n";
		}
	    	myfile.close();
	  }
	  else cout << "Unable to open file";

	return 0;

}

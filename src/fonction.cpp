#include<cmath>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<math.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include "fonction.h"

double boneCVtiming()
{
//    VideoCapture capture(0);
//    capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
//    capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
//    if(!capture.isOpened()){
//	    cout << "Failed to connect to the camera." << endl;
//    }
//    Mat frame, edges;
//
//    struct timespec start, end;
//    clock_gettime( CLOCK_REALTIME, &start );
//
//    int frames=2;
//    for(int i=0; i<frames; i++){
//    	capture >> frame;
//    	if(frame.empty()){
//		cout << "Failed to capture an image" << endl;
//		return -1;
//    	}
//    	cvtColor(frame, edges, CV_BGR2GRAY);
//    	Canny(edges, edges, 0, 30, 3);
//    }
//
//    clock_gettime( CLOCK_REALTIME, &end );
//    double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0d;
//    cout << "It took " << difference << " seconds to process " << frames << " frames" << endl;
//    cout << "Capturing and processing " << frames/difference << " frames per second " << endl;
//
//    imwrite("edges.png", edges);
//    imwrite("capture.png", frame);
//    return frames/difference;
}



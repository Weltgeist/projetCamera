
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
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<time.h>
#include "class.h"
#include "fonction.h"
#include "constante.h"
//
//void populerResolutions(ResolutionFPS* rfps)
//{
//
///*	rfps[0].res.resX = 176;
//	rfps[0].res.resY = 144;
//
//	rfps[1].res.resX = 160;
//	rfps[1].res.resY = 120;
//
//	rfps[2].res.resX = 320;
//	rfps[2].res.resY = 176;
//
//	rfps[3].res.resX = 320;
//	rfps[3].res.resY = 240;
//
//	rfps[4].res.resX = 352;
//	rfps[4].res.resY = 288;
//
//	rfps[5].res.resX = 432;
//	rfps[5].res.resY = 240;
//
//	rfps[6].res.resX = 800;
//	rfps[6].res.resY = 600;
//
//	rfps[7].res.resX = 864;
//	rfps[7].res.resY = 480;
//
//	rfps[8].res.resX = 960;
//	rfps[8].res.resY = 544;
//
//	rfps[9].res.resX = 960;
//	rfps[9].res.resY = 720;
//
//	rfps[10].res.resX = 1184;
//	rfps[10].res.resY = 656;
//
//	rfps[11].res.resX = 1280;
//	rfps[11].res.resY = 720;
//
//	rfps[12].res.resX = 1280;
//	rfps[12].res.resY = 960;*/
//}
//


/////////////////////METHOD #3//////////////////// PASS BY REFERENCE -TOTAL TABLE













/**
*\fn void initRFPS(ResolutionFPS* Obj ,int t_id)
*\brief Pass a object vector line by line and assign initRes.
*\param t_id
*\param t_id:
*\return void
*/
void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2])
{

	for (int i=0;i<13;i++)
{
		(frps[i]).res.resX=table[i][0];
	    (frps[i]).res.resY=table[i][1];
}



}





//
//void populerFPS()
//{
////	string nom_capture;
//
////	for (int i = 0; i < 13; i++)
////	{
////
////		VideoCapture capture(0);
////		capture.set(CV_CAP_PROP_FRAME_WIDTH,rfps[i].res.resX);
////		capture.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[i].res.resY);
////		if(!capture.isOpened()){
////			cout << "Failed to connect to the camera." << endl;
////		}
////		Mat frame, edges;
////
////		struct timespec start, end;
////		clock_gettime( CLOCK_REALTIME, &start );
////
////		int frames=2;
////		for(int i=0; i<frames; i++){
////			capture >> frame;
////			if(frame.empty()){
////			cout << "Failed to capture an image" << endl;
////			return -1;
////			}
//////	    	cvtColor(frame, edges, CV_BGR2GRAY);
//////	    	Canny(edges, edges, 0, 30, 3);
////		}
////
////		clock_gettime( CLOCK_REALTIME, &end );
////		double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0d;
////		cout << "It took " << difference << " seconds to process " << frames << " frames" << endl;
////		cout << "Capturing and processing " << frames/difference << " frames per second " << endl;
////		rfps[i].fps = frames/difference;
////
//////	    nom_capture = "capture"+itoa(i)+".png";
//////	    cin >> nom_capture;
//////		imwrite(nom_capture, frame);
////		}
//}
//
////void capture5SEC(int choix)
////{
////		VideoCapture capture(0);
////		capture.set(CV_CAP_PROP_FRAME_WIDTH,rfps[choix].res.resX);
////		capture.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[choix].res.resY);
////		string nom_capture;
////		Mat video;
////
////		for (int i = 0; i < 5*rfps[choix].fps; i++)
////	{
////						capture >> video;
////	}
////
////		VideoWrite("capture-liv1.avi", video)
////
////}
//
//
//
//double boneCVtiming()
//{
////    VideoCapture capture(0);
////    capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
////    capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
////    if(!capture.isOpened()){
////	    cout << "Failed to connect to the camera." << endl;
////    }
////    Mat frame, edges;
////
////    struct timespec start, end;
////    clock_gettime( CLOCK_REALTIME, &start );
////
////    int frames=2;
////    for(int i=0; i<frames; i++){
////    	capture >> frame;
////    	if(frame.empty()){
////		cout << "Failed to capture an image" << endl;
////		return -1;
////    	}
////    	cvtColor(frame, edges, CV_BGR2GRAY);
////    	Canny(edges, edges, 0, 30, 3);
////    }
////
////    clock_gettime( CLOCK_REALTIME, &end );
////    double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0d;
////    cout << "It took " << difference << " seconds to process " << frames << " frames" << endl;
////    cout << "Capturing and processing " << frames/difference << " frames per second " << endl;
////
////    imwrite("edges.png", edges);
////    imwrite("capture.png", frame);
////    return frames/difference;
//}





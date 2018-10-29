#ifndef FONCTION_H
#define FONCTION_H
//#include<cmath>
//#include<cstring>
//#include<cstdio>
//#include<cstdlib>
//#include<math.h>
//#include<iostream>
//#include<fstream>
//#include<string>
#include<stdio.h>
#include<stdlib.h>
//#include<opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include<opencv2/core.hpp>
//#include<opencv2/imgproc.hpp>
//#include<opencv2/videoio.hpp>
//#include<time.h>
#include "class.h"
//#include "constante.h"

//using namespace cv;
//using namespace std;

void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2]);

void error(const char *msg);


#endif











//int detectCamera();

//int populerFPS(ResolutionFPS (&rfps)[13]);

//void capture5SEC(int choix);

//int choixUser(ResolutionFPS (&rfps)[13]);

//void enregistVideo(ResolutionFPS (&rfps)[13],int choix);

//void initCapture(VideoCapture &capture,ResolutionFPS &rfps);

//void captureImage(VideoCapture &capture,Mat &frame);

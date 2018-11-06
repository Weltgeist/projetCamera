#ifndef FONCTION_H
#define FONCTION_H

#include<math.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include<time.h>
#include "class.h"
#include "constante.h"

using namespace cv;
using namespace std;


int detectCamera();

void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2]);

void initCapture(VideoCapture &capture,ResolutionFPS &rfps);

bool test(uint32_t result, int bit);

void captureImage(VideoCapture &capture,Mat &frame);

void error(const char *msg);

uint32_t findState();


#endif








//int populerFPS(ResolutionFPS (&rfps)[13]);

//void capture5SEC(int choix);

//int choixUser(ResolutionFPS (&rfps)[13]);

//void enregistVideo(ResolutionFPS (&rfps)[13],int choix);

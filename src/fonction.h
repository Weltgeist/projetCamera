#ifndef FONCTION_H
#define FONCTION_H
#include "constante.h"
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


//void populerResolutions(ResolutionFPS* rfps);

void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2]);
//
//void populerFPS();
//
//void capture5SEC(int choix);

#endif

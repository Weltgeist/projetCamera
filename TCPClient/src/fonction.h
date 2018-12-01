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
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
//#include<opencv2/imgproc.hpp>
 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2/core/core.hpp>
//#include<opencv2/core.hpp>
//#include<opencv2/imgproc.hpp>
//#include<opencv2/videoio.hpp>
//#include<time.h>
#include "class.h"
//#include "constante.h"
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>


using namespace cv;
//using namespace cv::face;
using namespace std;



/**
 * void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2])
 * \brief Pass an object table by reference and assign resolutions X and Y to each instantiation .
 * @param frps
 * @param table
 */
void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2]);

/**
 * void error(const char *msg)
 * \brief Display an error message in console
 * @param msg The message to be displayed
 */
void error(const char *msg);

/**
 * @fn choixUser
 * \brief Offers the user a contextual menu to choose between 4 resolutions using keys 1 to 4.
 * @param rfps The object containing the resolutions according to their index from 1 to 13.
 * @return
 */
int choixUser(ResolutionFPS (&rfps)[13]);

/**
 * \fn detectAndDisplay
 * \brief
 * @param frame
 * @param face_cascade
 * @param eyes_cascade
 * @param ctr_img
 */
//void detectAndDisplay( Mat& frame ,CascadeClassifier& face_cascade,CascadeClassifier& eyes_cascade,int ctr_img);
void detectAndDisplay( char* adress ,CascadeClassifier& face_cascade,CascadeClassifier& eyes_cascade,int ctr_img,const string& Path,int mode=0);

/**
 * \fn read_csv
 * @param filename
 * @param images
 * @param labels
 * @param separator
 */
static void read_csv(const string& filename, vector<Mat>& images, vector<string>& labels, char separator = ';');

void writeToCSV(const string& CSVfilename,const string& IMGfilename,string label, int ctr_img, char separator= ';');

void createDir(const string& PATH,const string& label);

int choixMode();

int choixPersonne(vector<string>& listeNoms, vector<Mat>& images, vector<string>& labels, const string& PATH, const string& PathCSV, int ctr_img);

int find_ctr_img(vector<string>& listeNoms, vector<Mat>& images, vector<string>& labels, const string& PATH, const string& PathCSV, int personne);

void recon(vector<string>& listeNoms, vector<Mat>& images, vector<string>& labels, const string& PATH, const string& PathCSV, int personne, Mat& img);


#endif

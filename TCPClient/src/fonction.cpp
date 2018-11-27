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
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include<opencv2/core.hpp>
//#include<opencv2/imgproc.hpp>
 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
//#include<opencv2/videoio.hpp>
//#include<time.h>
#include<limits>
#include "class.h"
//#include "constante.h"
#include "fonction.h"
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>


using namespace std;
using namespace cv;


void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2])
{

	for (int i=0;i<13;i++)
	{
		(frps[i]).setRes(table[i][0],table[i][1]);

	}

}


void error(const char *msg)
{
    perror(msg);
    exit(0);
}


int choixUser(ResolutionFPS (&rfps)[13])
{
	int choix;
	int table[4]={1,3,9,12};
	char choixcar[1000];
	char* ptr;
	cout << "Choisissez une resolution parmi les suivantes:\n";
	for (int i = 0; i < 4; i++){
		cout << i+1 << ": " << rfps[table[i]].getRes().getX() << "x" << rfps[table[i]].getRes().getY()  << "\n";
	}
	cin >> choix;
	 //choix = getchar()-48;
	 std::cin.ignore(std::numeric_limits<char>::max(),'\n');

	while (choix < 1 || choix > 4) {
		cout << "L'entree doit etre un nombre de 1 a 4, choisissez a nouveau.\n";
		//cin.clear();
		//cin.ignore(INT_MAX, '\n');
		//choix = getchar()-48;
		cin >> choix;
		std::cin.ignore(std::numeric_limits<char>::max(),'\n');
	}
	return --choix;
}




//void detectAndDisplay( Mat& frame ,CascadeClassifier& face_cascade,CascadeClassifier& eyes_cascade,int ctr_img)
void detectAndDisplay( char* adress ,CascadeClassifier& face_cascade,CascadeClassifier& eyes_cascade,int ctr_img,const string& Path,int mode)
{
  std::vector<Rect> faces;
  Size defautSIZE(144,176); // width,height
  Mat frame_gray;
  char sctr_img[100];
  Mat frame =imread(adress);
  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
  Mat faceROI2;

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( int i = 0; i < faces.size(); i++ )
  {

    //Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    //ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Point point1(faces[i].x, faces[i].y);

    Point point2(faces[i].x + faces[i].width,
                                 faces[i].y + faces[i].height);

    rectangle(frame, point1, point2, Scalar( 255, 0,0, 255 ), 4, 8, 0 );

    //Crop
     Mat faceROI = frame_gray( faces[i] );
    //Resize
     if (faceROI.total()>0){
     resize(faceROI,faceROI2,defautSIZE);
     cout<<faceROI2.total()<<endl;
     }
     else{
    	 cout<<"Pas de FACE!!!"<<endl;
    	 cout<<faceROI2.total()<<endl;
     }
//    std::vector<Rect> eyes;
//
//    //-- In each face, detect eyes
//    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
//
//    for( int j = 0; j < eyes.size(); j++ )
//     {
//       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
//       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
//       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
//     }
  }
  //-- Show what you got
  //imshow( window_name, frame );
  sprintf(sctr_img,"%s/DetectPIC%u.png",Path.c_str(),ctr_img);
  imwrite(sctr_img, frame);
  if (faceROI2.total()>0){
  sprintf(sctr_img,"%s/cropresizePIC%u.png",Path.c_str(),ctr_img);
  imwrite(sctr_img, faceROI2);
  cout<<"Doing Great"<<endl;
  }


 }


static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator) { //static
    ifstream file(filename.c_str(),ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        //CV_Error(Error::StsBadArg, error_message);
        cout<<error_message<<endl;
    }
    else{
		string line, path, classlabel;
		while (getline(file, line)) {
			stringstream liness(line);
			getline(liness, path, separator);
			getline(liness, classlabel,separator);
			if(!path.empty() && !classlabel.empty()) {
				images.push_back(imread(path, 0));
				labels.push_back(atoi(classlabel.c_str()));
			}
		}
    }
}

void writeToCSV(const string& CSVfilename,const string& IMGfilename,string label, int ctr_img, char separator)
{
	ofstream file(CSVfilename.c_str(),ofstream::app);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        //CV_Error(Error::StsBadArg, error_message);
        cout<<error_message<<endl;
    }
    else
    {
    	file<<IMGfilename<<separator<<label<<separator<<ctr_img<<separator<<endl;
    }
    file.close();


}

void createDir(const string& PATH,const string& label)
{

    // Creating a directory
	string PATH_TOT=PATH+"/"+label;
    if (mkdir(PATH_TOT.c_str(), 0777) == -1)
        cerr << "Error :  " << strerror(errno) << endl;

    else
        cout << "Directory created";
}








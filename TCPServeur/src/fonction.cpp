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
#include "fonction.h"


using namespace std;
using namespace cv;


int detectCamera()
{
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
		  return 1;
	  }
	  else{return 0;}
}


/**
 * void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2])
 * \brief Pass an object table by reference and assign resolutions X and Y to each instantiation .
 * @param frps
 * @param table
 */
void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2])
{

	for (int i=0;i<13;i++)
	{
		(frps[i]).res.resX=table[i][0];
	    (frps[i]).res.resY=table[i][1];
	}

}


void initCapture(VideoCapture &capture,ResolutionFPS &rfps) ///Besoin d'envoyer rfps[choix]
{
	capture.set(CV_CAP_PROP_FRAME_WIDTH,rfps.res.resX);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,rfps.res.resY);
}


bool test(uint32_t result, int bit)
{
	 int mask=pow(2,bit);
	 bool test= result&mask;

	return test;
}


void captureImage(VideoCapture &capture,Mat &frame)
{
	capture >> frame;
}


void error(const char *msg)
{
    perror(msg);
    exit(1);
}









//int populerFPS(ResolutionFPS (&rfps)[13]){
// //	string nom_capture;
//
//for (int i = 0; i < 13; i++)
//{
//
//	VideoCapture capture(0);
//	capture.set(CV_CAP_PROP_FRAME_WIDTH,rfps[i].res.resX);
//	capture.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[i].res.resY);
//	if(!capture.isOpened()){
//		cout << "Failed to connect to the camera." << endl;
//		return -1;
//	}
//	Mat frame, edges;
//	// calibration de la camera
//	capture >> frame;
//	capture >> frame;
//
//	struct timespec start, end;
//	clock_gettime( CLOCK_REALTIME, &start );
//
//	int frames=2;
//
//	for(int i=0; i<frames; i++){
//		capture >> frame;
//		if(frame.empty()){
//		cout << "Failed to capture an image" << endl;
//		return -1;
//		}
// //	    	cvtColor(frame, edges, CV_BGR2GRAY);
// //	    	Canny(edges, edges, 0, 30, 3);
//	}
//
//	clock_gettime( CLOCK_REALTIME, &end );
//	double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0d;
//	// cout << "It took " << difference << " seconds to process " << frames << " frames" << endl;
//	cout << "Capturing and processing " << frames/difference << " frames per second for " << rfps[i].res.resX << "x" << rfps[i].res.resY << endl;
//	rfps[i].fps = frames/difference;
//
// //	    nom_capture = "capture"+itoa(i)+".png";
// //	    cin >> nom_capture;
// //		imwrite(nom_capture, frame);
//	}
//return 1;
//}


//int choixUser(ResolutionFPS (&rfps)[13])
//{
//	int choix;
//	cout << "Choisissez une resolution parmi les suivantes:\n";
//	for (int i = 0; i < 13; i++){
//		cout << i+1 << ": " << rfps[i].res.resX << "x" << rfps[i].res.resY << "\n";
//	}
//	cin >> choix;
//	while (!cin || choix < 1 || choix > 13) { //!isdigit(choix) ||
//		cout << "L'entree doit etre un nombre de 1 a 13, choisissez a nouveau.\n";
//		cin.clear();
//		cin.ignore(INT_MAX, '\n');
//		cin >> choix;
//	}
//	return --choix;
//}


//void( enregistVideo(ResolutionFPS (&rfps)[13],int choix){
//
//VideoWriter vidW("/home/root/capture-liv1.avi",CV_FOURCC('M','J','P','G'),round(rfps[choix].fps),Size(rfps[choix].res.resX,rfps[choix].res.resY),true);
//VideoCapture capture2(0);
//
//capture2.set(CV_CAP_PROP_FRAME_WIDTH,rfps[choix].res.resX);
//capture2.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[choix].res.resY);
//if(!capture2.isOpened()){
//	cout << "Failed to connect to the camera." << endl;
//}
//Mat video;
//
//for (int i = 0; i < 5*((int)rfps[choix].fps); i++)
//{
//	cout << "Saving Frame number: " << i <<" in video." <<endl;
//	capture2 >> video;
//	vidW.write(video);
//}
//}



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

#include <cstdlib>
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


const string CAM_ID="046d:0825";
const int NB_RES=13;
const int RES_TABLE[13][2]={{176,144},{160,120},{320,176},{320,240},{352,288},{432,240},{800,600},{864,480},{960,544},{960,720},{1184,656},{1280,720},{1280,960}};


int main()
{
	int choix;
	// fn detecter bonne camera
		// trouver id 046d:0825
	std::system("lsusb | grep 046d:0825  > /home/root/test.txt");
//	FILE * camFile;
//	camFile=fopen("/home/root/test.txt","r");
//	  if (camFile!=NULL)
//	  {
//	    //fputs ("fopen example",pFile);
//	    fclose (camFile);
//	  }
//	  //
//
//
//	  fclose (camFile);
	  ///FROM http://www.cplusplus.com/doc/tutorial/files/
	  streampos begin,end;
	  ifstream myfile ("/home/root/test.txt", ios::binary);
	  begin = myfile.tellg();
	  myfile.seekg (0, ios::end);
	  end = myfile.tellg();
	  myfile.close();
	  cout << "size is: " << (end-begin) << " bytes.\n";
	  if((end-begin)!=0){
//	string line;
//	    ifstream myfile ("/home/root/test.txt",ios::in | ios::out |ios::binary);
//	    if (!myfile){
//	        cout<<"cannot open file";
//	         exit (1);
//
//	    }
//
//	     while (!myfile.eof()){
//	        getline(myfile,line);
//	        cout<<line<<endl;
//
//	     }
//
//	     long l,m;
//	     l=myfile.tellg();
//	     myfile.seekg(0,ios::end);
//	     m=myfile.tellg();
//	     cout<<"size of  text file is:";
//	     cout<<(m-l)<<"bytes"<<endl;
//	     myfile.close();



	// fn populer les resolutions
	ResolutionFPS rfps[13];
	populerResolutions(rfps,RES_TABLE);



	// fn calculer et populer les framerates
	// populerFPS();

	//	string nom_capture;

		for (int i = 0; i < 13; i++)
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
	//	    cin >> nom_capture;
	//		imwrite(nom_capture, frame);
			}


	// fn demander la resolution a l'utilisateur
		cout << "Choisissez une resolution parmi les suivantes:\n";
		for (int i = 0; i < 13; i++){
			cout << i+1 << ": " << rfps[i].res.resX << "x" << rfps[i].res.resY << "\n";
		}

		cin >> choix;
		if (isdigit(choix) && choix >=1 && choix <= 13){}
		else cout << "L'entree doit etre un nombre de 1 a 13";
		//int choix=12;
		choix--;





	// fn enregistrer 5 secondes de video
	VideoWriter vidW("/home/root/capture-liv1.avi",CV_FOURCC('M','J','P','G'),(int)rfps[choix].fps,Size(rfps[choix].res.resX,rfps[choix].res.resY),true);
	VideoCapture capture2(0);

	capture2.set(CV_CAP_PROP_FRAME_WIDTH,rfps[choix].res.resX);
	capture2.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[choix].res.resY);
	if(!capture2.isOpened()){
		cout << "Failed to connect to the camera." << endl;
	}
	Mat video;

	for (int i = 0; i < 5*((int)rfps[choix].fps); i++)
	{
		cout << "Saving Frame number: " <<i<<"in video" <<endl;
		capture2 >> video;
		vidW.write(video);
	}






//
//	delete ptrfps;
//	ptrfps = 0;

	  }
	  else
	  {
		 cout<<"Pas la bonne camera" <<endl;
	  }

	return 0;

}




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

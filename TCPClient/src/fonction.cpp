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
#include<iostream>
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


using namespace std;
using namespace cv;


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


//void detectAndDraw( Mat& img, CascadeClassifier& cascade,
//                    CascadeClassifier& nestedCascade,
//                    double scale, int ctr_img)
//{
//    vector<Rect> faces, faces2;
//    Mat gray, smallImg;
//    char sctr_img[50];
//
//    cvtColor( img, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale
//    double fx = 1 / scale;
//
//    // Resize the Grayscale Image
//    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );
//    equalizeHist( smallImg, smallImg );
//
//    // Detect faces of different sizes using cascade classifier
//    cascade.detectMultiScale( smallImg, faces, 1.1,
//                            2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
//
//    // Draw circles around the faces
//    for ( size_t i = 0; i < faces.size(); i++ )
//    {
//        Rect r = faces[i];
//        Mat smallImgROI;
//        vector<Rect> nestedObjects;
//        Point center;
//        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
//        int radius;
//
//        double aspect_ratio = (double)r.width/r.height;
//        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
//        {
//            center.x = cvRound((r.x + r.width*0.5)*scale);
//            center.y = cvRound((r.y + r.height*0.5)*scale);
//            radius = cvRound((r.width + r.height)*0.25*scale);
//            circle( img, center, radius, color, 3, 8, 0 );
//        }
//        else
//            rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
//                    cvPoint(cvRound((r.x + r.width-1)*scale),
//                    cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
//        if( nestedCascade.empty() )
//            continue;
//        smallImgROI = smallImg( r );
//
//        // Detection of eyes int the input image
//        nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2,
//                                        0|CASCADE_SCALE_IMAGE, Size(30, 30) );
//
//        // Draw circles around eyes
//        for ( size_t j = 0; j < nestedObjects.size(); j++ )
//        {
//            Rect nr = nestedObjects[j];
//            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
//            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
//            radius = cvRound((nr.width + nr.height)*0.25*scale);
//            circle( img, center, radius, color, 3, 8, 0 );
//        }
//    }
//
//    // Show Processed Image with detected faces
// //   imshow( "Face Detection", img );
//
//sprintf(sctr_img,"/export/tmp/4205_07/projet/DetectPIC%u.png",ctr_img);
//imwrite(sctr_img, img);
//
//}





/** @function detectAndDisplay */
void detectAndDisplay( Mat& frame ,CascadeClassifier& face_cascade,CascadeClassifier& eyes_cascade,int ctr_img)
{
  std::vector<Rect> faces;
  Mat frame_gray;
  char sctr_img[50];

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( int i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );
    std::vector<Rect> eyes;

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( int j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
     }
  }
  //-- Show what you got
  //imshow( window_name, frame );
  sprintf(sctr_img,"/export/tmp/4205_07/projet/DetectPIC%u.png",ctr_img);
  imwrite(sctr_img, frame);
 }



//int detectCamera()
//{
//	std::system("lsusb | grep 046d:0825  > /home/root/trouver_cam.txt");
//
//	  ////FROM http://www.cplusplus.com/doc/tutorial/files/
//	  streampos begin,end;
//	  ifstream myfile ("/home/root/trouver_cam.txt", ios::binary);
//	  begin = myfile.tellg();
//	  myfile.seekg (0, ios::end);
//	  end = myfile.tellg();
//	  myfile.close();
//	  // cout << "size is: " << (end-begin) << " bytes.\n";
//	  if((end-begin)!=0){
//		  cout << "La bonne camera a ete trouvee.\n";
//		  return 1;
//	  }
//	  else{return 0;}
//}


//int populerFPS(ResolutionFPS (&rfps)[13]){
//	//string nom_capture;
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





//void enregistVideo(ResolutionFPS (&rfps)[13],int choix){
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
//
//}


//void captureImage(VideoCapture &capture,Mat &frame)
//{
//	capture >> frame;
//}


//void initCapture(VideoCapture &capture,ResolutionFPS &rfps) ///Besoin d'envoyer rfps[choix]
//{
//	capture.set(CV_CAP_PROP_FRAME_WIDTH,rfps.res.resX);
//	capture.set(CV_CAP_PROP_FRAME_HEIGHT,rfps.res.resY);
//}


//void capture5SEC(int choix)
//{
//		VideoCapture capture(0);
//		capture.set(CV_CAP_PROP_FRAME_WIDTH,rfps[choix].res.resX);
//		capture.set(CV_CAP_PROP_FRAME_HEIGHT,rfps[choix].res.resY);
//		string nom_capture;
//		Mat video;
//
//		for (int i = 0; i < 5*rfps[choix].fps; i++)
//	{
//						capture >> video;
//	}
//
//		VideoWrite("capture-liv1.avi", video)
//
//}










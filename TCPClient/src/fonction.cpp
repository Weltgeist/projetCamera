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
//#include "opencv2/face.hpp"
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
void detectAndDisplay( char* adress ,CascadeClassifier& face_cascade,CascadeClassifier& eyes_cascade,int ctr_img,const string& Path,int mode, std::vector<Rect>* ptrFace)
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
	if (mode==1)
	{
		*ptrFace=faces;
	}
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


static void read_csv(const string& filename, vector<Mat>& images, vector<string>& labels, char separator)
{
	images.clear();
	labels.clear();
	ifstream file(filename.c_str(),ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.\n";
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
				labels.push_back(classlabel.c_str());
			}
		}
		file.close();
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
        cout << "Directory created\n";
}



int choixMode()
{
	int mode, personne;
	char modecar[1000];
	char* ptr;
	cout << "Choisissez un mode parmi les suivants:\n1- Apprentissage\n2- Reconnaissance\n";
	cin >> mode;
	std::cin.ignore(std::numeric_limits<char>::max(),'\n');

	while (mode < 1 || mode > 2) {
		cout << "L'entree doit etre un nombre de 1 a 2, choisissez a nouveau.\n";
		cin >> mode;
		std::cin.ignore(std::numeric_limits<char>::max(),'\n');
	}

	return --mode;
}


int choixPersonne(vector<string>& listeNoms, vector<Mat>& images, vector<string>& labels, const string& PATH, const string& PathCSV, int ctr_img)
{
	int personne = 0;
	string nom;
	string label;
	int vide = 1;

	cout << "Choisissez une personne parmi les suivantes:\n";
	int i;
	cout << 0 << " - Nouveau" << endl;
	if (sizeof(listeNoms) > 0) {
		for (i = 0; i < listeNoms.size(); i++){
			cout << i+1 << " - " << listeNoms[i] << endl;
		}
		vide = 0;
	}
	else {
		vide = 1;
	}
	cin >> personne;
	std::cin.ignore(std::numeric_limits<char>::max(),'\n');


	// Verification
		while (personne < 0 || personne > i+1) {
			cout << "L'entree doit etre un nombre de 0 a " << i+1 << ", choisissez a nouveau.\n";
			cin >> personne;
			std::cin.ignore(std::numeric_limits<char>::max(),'\n');
		}


		// Nouvelle personne
		if (personne == 0){ //Personne est un choix, mais en sortis de fonction c'est la position dans la liste de nom
			cout << "Entrez le nom de la personne, sans espaces.\n";
			cin >> nom; //new Name
			std::cin.ignore(std::numeric_limits<char>::max(),'\n');
			listeNoms.push_back(nom);
			personne = listeNoms.size()-1;//new ID
			label = nom;
			createDir(PATH,label);//new DIR
		}

		// Personne ayant deja un dossier et des photos
		else {
			personne--;
		}


	return personne;
}


int find_ctr_img(vector<string>& listeNoms, vector<Mat>& images, vector<string>& labels, const string& PATH, const string& PathCSV, int personne)
{
	int ctr_img = 0;
	read_csv(PathCSV, images, labels);//label vector is a list of all names in csv files.
	for (int i = 0; i < labels.size(); i++){
		if (labels[i].compare(listeNoms[personne]) == 0) {
			ctr_img++; //Counts how many of a specific name is in the label vector
		}
	}
	return ctr_img;
}



void recon(vector<string>& listeNoms, vector<Mat>& images, vector<string>& labels, const string& PATH, const string& PathCSV, int personne, Mat& imgx, CascadeClassifier& face_cascade,CascadeClassifier& eyes_cascade)
{
	char sctr_img[100];
	int ctr_img = 0;
	char A[100];
    std::vector<Rect>* ptrFace=new  std::vector<Rect>;
    std::vector<Rect> faces;

	try {

    	read_csv(PathCSV, images, labels);
    } catch (const cv::Exception& e) {
        cerr << "Error opening file \"" << PathCSV << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }

    vector<int> labels_int;
	for (int i = 0; i < labels.size(); i++){
		for (int j = 0; j < listeNoms.size(); j++){
			cout<<"LN:"<<listeNoms.size()<<"j:"<<j<<"i:"<<i<<endl;
			// probleme de compare strings //std::vector<Rect> faces;convertis labels(liste de string) en label(liste de int) pour train fonction
			if (labels[i].compare(listeNoms[j]) == 0) {
				labels_int.push_back(j);
			}
		}
	}

	Mat testSample = images[images.size() - 1];
    int testLabel = labels_int[labels_int.size() - 1];
    images.pop_back();
    labels_int.pop_back();

    //Apprentissage
    Ptr<FaceRecognizer> model =  createLBPHFaceRecognizer();
    model->train(images, labels_int);


	sprintf(A,"/export/tmp/4205_07/projet/TOrecon.png");
	detectAndDisplay(A,face_cascade,eyes_cascade,ctr_img,"/export/tmp/4205_07/projet/",1,ptrFace);
	faces = *ptrFace;

	for (int i = 0; i < faces.size(); i++) {
		sprintf(sctr_img,"/export/tmp/4205_07/projet/cropresizePIC%d.png",i);
		Mat img = imread(sctr_img, CV_LOAD_IMAGE_GRAYSCALE);

		//Reconaissance
		int predicted = model->predict(img);
		string result_message = format("Predicted class = %d / Actual class = %d.", predicted, testLabel);
		cout << result_message << endl;

		Point point1(faces[i].x, faces[i].y);
		Point point2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
		Point point3(point1.x, point1.y-10);
		string nom = listeNoms[predicted];

		Mat img2 = imread("/export/tmp/4205_07/projet/TOrecon.png", CV_LOAD_IMAGE_GRAYSCALE);
		rectangle(img2, point1, point2, Scalar( 255, 0,0, 255 ), 4, 8, 0 );
		putText(img2, nom, point3, FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
		sprintf(sctr_img,"%s/TOrecon.png",PATH.c_str());
		imwrite(sctr_img, img2);
	}

}






/**
 * \file class.cpp
 * \brief Contains the function definitions of classes Resolution and Client.
 * \author ELE4205_07
 * \date 3 december 2018
 *
 */


#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include <opencv2/opencv.hpp>
#include<stdio.h>
#include<stdlib.h>
#include "class.h"

using namespace std;



void Client::error(const char *msg)
{
    perror(msg);
    exit(0);
}


void Client::createDir(const string& label)
{

    // Creating a directory
	string PATH_TOT=PATH+"/"+label;
    if (mkdir(PATH_TOT.c_str(), 0777) == -1)
    	cout << "Directory not created\n";
    else
        cout << "Directory created\n";
}


int Client::choixPersonne()
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
			createDir(label);//new DIR
		}

		// Personne ayant deja un dossier et des photos
		else {
			personne--;
		}


	return personne;
}

void Client::read_csv(char separator)
{
	listImages.clear();
	labels.clear();
	ifstream file(PathCSV.c_str(),ifstream::in);
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
				listImages.push_back(imread(path, 0));
				labels.push_back(classlabel.c_str());
			}
		}
		file.close();
    }
}


int Client::find_ctr_img(int personne)
{
	int ctr_img = 0;
	read_csv();//label vector is a list of all names in csv files.
	for (int i = 0; i < labels.size(); i++){
		if (labels[i].compare(listeNoms[personne]) == 0) {
			ctr_img++; //Counts how many of a specific name is in the label vector
		}
	}
	return ctr_img;
}






void Client::loadCascades(){
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); };
}


void Client::initClient(){
	// Create TCP socket using socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname("192.168.7.2");
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(portno);
}


void Client::clientConnect(){
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");
}


uint32_t Client::clientRcvSend(){
	// Receive state from server in uint32_t
	 bzero(buffer,256);
	 n = read(sockfd,buffer,255);
	 if (n < 0) error("ERROR reading from socket");

	 //Decoder le uint32 soit ici l'etat du serveur
	 uint32_t state = strtol(buffer,&ptrBuffer,10);

	 // Send ok to server to send the image
	sprintf(buffer,"%u", messages);
	n = write(sockfd,buffer,sizeof(messages));
	if (n < 0){ error("ERROR writing to socket");}

	return state;
}


void Client::clientInitImg(Resolution (&res)[13], int choix){
	// Initialize image for reception
	img=new Mat;
	*img= Mat::zeros( res[choix].getY() ,res[choix].getX() , CV_8UC3);
	imgSize = img->total()*(img->elemSize());

	sockData.clear();
	sockData.resize(imgSize);
}


void Client::writeToCSV(const string& CSVfilename,const string& IMGfilename,string label, int ctr_img, char separator)
{
	ofstream file(CSVfilename.c_str(),ofstream::app);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        cout<<error_message<<endl;
    }
    else
    {
    	file<<IMGfilename<<separator<<label<<separator<<ctr_img<<separator<<endl;
    }
    file.close();
}


int Client::detectAndDisplay( char* adress,int ctr_img,const string& Path,int mode, std::vector<Rect>* ptrFace)
{
	  std::vector<Rect> faces;
	  Size defautSIZE(144,176); // width,height
	  Mat frame_gray;
	  char sctr_img[100];
	  Mat frame =imread(adress);
	  cvtColor( frame, frame_gray, CV_BGR2GRAY );
	  equalizeHist( frame_gray, frame_gray );
	  Mat faceROI2;
	  int detect = 0;

	  //-- Detect faces
	  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
		if (mode==1)
		{
			*ptrFace=faces;
		}
	  for( int i = 0; i < faces.size(); i++ )
	  {
		Point point1(faces[i].x, faces[i].y);
		Point point2(faces[i].x + faces[i].width,faces[i].y + faces[i].height);
		rectangle(frame, point1, point2, Scalar( 255, 0,0, 255 ), 4, 8, 0 );
		//Crop
		 Mat faceROI = frame_gray( faces[i] );
		//Resize
		 if (faceROI.total()>0){
			 resize(faceROI,faceROI2,defautSIZE);
			 sprintf(sctr_img,"%s/cropresizePIC%u-%i.png",Path.c_str(),ctr_img,i);
			 imwrite(sctr_img, faceROI2);
			 detect = faces.size();
		 }
	  }
	  sprintf(sctr_img,"%s/DetectPIC%u.png",Path.c_str(),ctr_img);
	  imwrite(sctr_img, frame);
	  if (faces.size()>0){
	 }
	  return detect;
 }


void Client::recon(int personne)
{
	char sctr_img[100];
	int ctr_img = 0;
	char A[100];
	char B[100];
    std::vector<Rect>* ptrFace=new  std::vector<Rect>;
    std::vector<Rect> faces;
    string nom;
    int predicted;
    double current_threshold;
    int detect = 0;

	try {
		read_csv();
    } catch (const cv::Exception& e) {
        cerr << "Error opening file \"" << PathCSV << "\". Reason: " << e.msg << endl;
        exit(1);
    }

    //convertis labels(liste de string) en label(liste de int) pour train fonction
    vector<int> labels_int;
	for (int i = 0; i < labels.size(); i++){
		for (int j = 0; j < listeNoms.size(); j++){

			if (labels[i].compare(listeNoms[j]) == 0) {
				labels_int.push_back(j);
			}
		}
	}

	Mat testSample = listImages[listImages.size() - 1];
    int testLabel = labels_int[labels_int.size() - 1];
    listImages.pop_back();
    labels_int.pop_back();

    //Apprentissage
    Ptr<FaceRecognizer> model =  createLBPHFaceRecognizer();
    model->train(listImages, labels_int);

	sprintf(A,"%s/TOrecon.png",PATH.c_str());
	sprintf(B,"%s/",PATH.c_str());
	detect = detectAndDisplay(A,ctr_img,B,1,ptrFace);
	if (detect >= 1){
		faces = *ptrFace;
		for (int i = 0; i < faces.size(); i++) {
			sprintf(sctr_img,"%s/cropresizePIC%d-%i.png",PATH.c_str(),ctr_img,i);
			Mat img = imread(sctr_img, CV_LOAD_IMAGE_GRAYSCALE);

			//Reconnaissance
			predicted = model->predict(img);
			nom = listeNoms[predicted];

			string result_message = format("Predicted person = %s", nom.c_str());
			cout << result_message << endl;

			Point point1(faces[i].x, faces[i].y);
			Point point2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point point3(point1.x, point1.y-10);

			Mat img2 = imread(A, CV_LOAD_IMAGE_GRAYSCALE);
			rectangle(img2, point1, point2, Scalar( 255, 0,0, 255 ), 4, 8, 0 );
			putText(img2, nom, point3, FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
			sprintf(sctr_img,"%s/TOrecon.png",PATH.c_str());
			imwrite(sctr_img, img2);
		}

	}
	else
	{cout<<"not detected, please take another picture"<<endl;}

}



void Client::clientFork(int mode,int ctr_img, int personne){
	pid = fork();
	if(pid == 0)
	{
		int detect;
		if (mode == 0){ //Apprentissage
			sprintf(sctr_img,"%s/%s/ORIGIN%u.png",PATH.c_str(),listeNoms[personne].c_str(),ctr_img);
			imwrite(sctr_img, *img);
			sprintf(sctr_img,"%s/%s/DetectPIC%u.png",PATH.c_str(),listeNoms[personne].c_str(),ctr_img);
			imwrite(sctr_img, *img);
			detect = detectAndDisplay(sctr_img,ctr_img,PATH+"/"+listeNoms[personne]);
			if (detect >= 1){
				sprintf(sctr_img,"%s/%s/cropresizePIC%u-0.png",PATH.c_str(),listeNoms[personne].c_str(),ctr_img);
				writeToCSV(PathCSV,sctr_img, listeNoms[personne], ctr_img);
			}
		}
		else if (mode == 1){ //Reconnaissance
			sprintf(sctr_img,"%s/TOrecon.png",PATH.c_str());
			imwrite(sctr_img, *img);
			recon(personne);
		}
		exit(0);
	}
	else if (pid>0)
	{
	   showImage();
	}
	else
	{
		cout << "PID failed" << endl;
	}
}


void Client::showImage(){
   namedWindow("Client", WINDOW_AUTOSIZE );
   imshow( "Client", *img);
}


void Client::deleteimg(){
	if(img!=0){delete img;}
	img=0;
}


void Client::clientQuit(){
	//Create New Message: Quit
   messages = 0;
   sprintf(buffer,"%u", messages);
   n = write(sockfd,buffer,sizeof(messages));
   if (n < 0)
		error("ERROR writing to socket");

   // Close the client connection using close
   close(sockfd);

   cout<<"Logout Client"<<endl;

}














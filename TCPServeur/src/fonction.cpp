/**
 * \file fonction.cpp
 * \brief Contains the declarations of the functions used in server main program.
 * \author ELE4205_07
 * \date 3 december 2018
 *
 */

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
	  if((end-begin)!=0){
		  cout << "La bonne camera a ete trouvee.\n";
		  return 1;
	  }
	  else{return 0;}
}


void populerResolutions(Resolution (&res)[13],const int table[][2])
{

	for (int i=0;i<13;i++)
	{
		res[i].setX(table[i][0]);
		res[i].setY(table[i][1]);
	}

}


void initCapture(VideoCapture &capture,Resolution &res) ///Besoin d'envoyer rfps[choix]
{
	capture.set(CV_CAP_PROP_FRAME_WIDTH,res.getX());
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,res.getY());
}


bool test(uint32_t result, int bit)
{
	 int mask=pow(2,bit);
	 bool test= result&mask;

	return test;
}





uint32_t findState()
{
	  string tension;
	  string bouton;
	  static int boutonprec =1; // Pour qu'elle ne soit initialisee qu'une seule fois
	  uint32_t etat;
	  int a=0;
	  char *ptrB,*ptrC;


	ifstream myfile ("/sys/class/saradc/ch0");
	  ifstream myfile2 ("/sys/class/gpio/gpio228/value");
	  // Lire la lumiere
	  if (myfile.is_open())
	  {
			getline (myfile,tension);
			myfile.close();
			if (strtol(tension.c_str(),&ptrB,10) >= 800 ||strtol(tension.c_str(),&ptrB,10) == -1){
				etat = 0; // lumiere 0
			}
			else {
				// Lire le bouton
				if (myfile2.is_open())
					  {
						getline (myfile2,bouton);
						myfile2.close();
						if (strtol(bouton.c_str(),&ptrC,10) == 1 && boutonprec == 0){
							etat = 3; // lumiere 1 et bouton relache
						}
						else etat = 1; // lumiere 1 et pas de bouton
						boutonprec=strtol(bouton.c_str(),&ptrC,10);
				}
				else cout << "Unable to open push-button file"<< endl;
			}
	  }
	  else cout << "Unable to open light sensor file"<< endl;
	  return etat;
}




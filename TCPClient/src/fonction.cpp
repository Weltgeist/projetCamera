

#include "class.h"
//#include "constante.h"
#include "fonction.h"



using namespace std;
using namespace cv;



void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2])
{

	for (int i=0;i<13;i++)
	{
		(frps[i]).setRes(table[i][0],table[i][1]);

	}

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
	 std::cin.ignore(std::numeric_limits<char>::max(),'\n');

	while (choix < 1 || choix > 4) {
		cout << "L'entree doit etre un nombre de 1 a 4, choisissez a nouveau.\n";
		cin >> choix;
		std::cin.ignore(std::numeric_limits<char>::max(),'\n');
	}
	return --choix;
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



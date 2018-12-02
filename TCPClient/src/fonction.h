#ifndef FONCTION_H
#define FONCTION_H

#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include "class.h"
//#include "constante.h"

using namespace cv;
using namespace std;



/**
 * void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2])
 * \brief Pass an object table by reference and assign resolutions X and Y to each instantiation .
 * @param frps
 * @param table
 */
void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2]);

/**
 * @fn choixUser
 * \brief Offers the user a contextual menu to choose between 4 resolutions using keys 1 to 4.
 * @param rfps The object containing the resolutions according to their index from 1 to 13.
 * @return
 */
int choixUser(ResolutionFPS (&rfps)[13]);


int choixMode();



#endif

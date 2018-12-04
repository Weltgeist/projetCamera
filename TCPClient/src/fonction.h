/**
 * \file fonction.h
 * \brief Contains the prototypes of the functions called directly from the main program that are not part of the Client object.
 * \author ELE4205_07
 * \date 3 december 2018
 *
 */



#ifndef FONCTION_H
#define FONCTION_H

#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include "class.h"

using namespace cv;
using namespace std;


/**
 * \fn void populerResolutions(Resolution (&res)[13],const int table[][2])
 * \brief Pass an object table by reference and assign resolutions X and Y to each instantiation .
 * \param frps The table of possible resolutions and fps, empty when passed in parameters.
 * \param table The constant table containing the possible resolutions.
 */
void populerResolutions(Resolution (&res)[13],const int table[][2]);


/**
 * \fn int choixUser(Resolution (&res)[13])
 * \param rfps The filled table of possible resolutions of the camera.
 * \return The value between 0 and 3 of the user choice of resolution between the four possible resolutions.
 */
int choixUser(Resolution (&res)[13]);

/**
 * \fn int choixMode()
 * \return The number 0 for learning mode or 1 for recognition mode.
 */
int choixMode();



#endif

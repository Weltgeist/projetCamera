/**
 * \file fonction.h
 * \brief Contains the functions used in server main program.
 * \author ELE4205_07
 * \date 3 december 2018
 *
 */

#ifndef FONCTION_H
#define FONCTION_H

#include<math.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include<time.h>
#include "class.h"

using namespace cv;
using namespace std;

/**
 * \fn int detectCamera()
 * \brief Detects if the correct camera is connected to the Odroid.
 * \return 0 if not found, 1 if found.
 */
int detectCamera();

/**
 * \fn void populerResolutions(ResolutionFPS (&frps)[13],const int table[][2])
 * \brief Pass an object table by reference and assign resolutions X and Y to each instantiation .
 * \param frps The table of possible resolutions and fps, empty when passed in parameters.
 * \param table The constant table containing the possible resolutions.
 */
void populerResolutions(Resolution (&res)[13],const int table[][2]);

/**
 * \fn void initCapture(VideoCapture &capture,ResolutionFPS &rfps)
 * \brief Sets the values of the desired resolution to object capture.
 * \param capture The object that allows the capture of an image as defined in OpenCV
 * \param rfps The filled table of possible resolutions of the camera.
 */
void initCapture(VideoCapture &capture,Resolution &res);

/**
 * \fn bool test(uint32_t result, int bit)
 * \brief Tests whether or not a certain bit is true in a uint32_t.
 * \param result The word to be tested.
 * \param bit The position of the bit to be tested.
 * \return The value of the bit.
 */
bool test(uint32_t result, int bit);

/**
 * \fn uint32_t findState()
 * \brief Finds the state of the server by reading the driver value for the light sensor. If light is found,
 * the driver value of the push-button is read. If a step-down is detected, the push-button release is true.
 * The result is encoded in a uint32_t.
 * \return 0 if no light, 1 if light only, 0b11 if light and push-button release
 */
uint32_t findState();


#endif


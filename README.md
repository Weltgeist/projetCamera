# Face Detection and Recognition Software-ELE4205 Team 7
***
## Introduction

This BitBucket Repository contains the project for Polytechnique Montreal ELE4205 class project for team number 7. 
The team members are:

* Gabrielle Caron 
* Samuel Narcisse

[![N|Solid](https://cdn-images-1.medium.com/max/1000/1*MnbUSSXG1IDS9mXC0H8cKQ.png)](https://towardsdatascience.com/face-recognition-for-beginners-a7a9bd5eb5c2)
[![N|Solid](https://cdn-images-1.medium.com/max/1600/1*GCqsG3c2Xt-d9JQGUpytpQ.gif)](https://itnext.io/face-api-js-javascript-api-for-face-recognition-in-the-browser-with-tensorflow-js-bcc2a6c4cf07)

***
## Description: The project

The goal of this project is to interface an Odroid-c2 board with a webcam to a computer through a TCP-IP connection.

## Prerequisite
Hardware:
* Odroid-c2 embedded microcontrollor with a pre-installed OS,in this case a Yocto image.
* Scientific Linux 7.5 Computer
* USB Logitech c270 webcam

**Alternative configuration may work, but have not been tested**

***

## Documentation
Open CV version installed on Scientific Linux 7.5:
https://docs.opencv.org/2.4.5/
Open CV version installée sur l'Odroid-C2:
https://docs.opencv.org/3.1.0/
Yocto:
https://www.yoctoproject.org/
Face Recognition:
https://docs.opencv.org/3.4/da/d60/tutorial_face_main.html
Tutorial:
https://www.superdatascience.com/opencv-face-recognition/?fbclid=IwAR06Q9KKUCob0067iXzQogP6oozvgMveGPpSD-v7IscJ1Mi1DOHSWlYcrlw

***
## Instructions



## Compilation: How to use the repository

The repository is divided in two subfolders, the TCP client and TCP server.
The project can be compiled 

| Type/App. | Eclipse | Terminal |
|-----------|:---------:|:----------:|
| Debug     | C/S    | C/S     |
| Release   | C/S    | C/S     |



### TCPClient

The TCPClient folder contains the source code for the executable that will run on the computer. In the terminal, you will have to compile and "make" the code with the following instructions, or the equivalent:

#### Debug
##### Eclipse
##### Terminal
#### Release
##### Eclipse
##### Terminal
> cmake -DCMAKE_BUILD_TYPE=Release \
> make

### TCPServeur

The TCPServeur folder contains the source code for the executable that will run on the Odroid-c2. In the terminal, you will have to compile and "make" the code with the following instructions, or the equivalent:


#### Debug
##### Eclipse
##### Terminal
#### Release
##### Eclipse
##### Terminal
> source [insert here the path to the sdk for your Yocto image]
> cmake -v -DCMAKE_BUILD_TYPE=Release \ -DOpenCV_DIR:STRING="/export/tmp/4205_nn/poky/build-oc2/tmp/sysroots/odroid-c2/usr/share/OpenCV"
> make

### PROCEDURE

Additional steps will be needed to configure certain GPIOs of embedded control and to set up connection.

1. Verify that USB ETHERNET FILAIRE CONNECTIONN is set to OFF
2. Manualy set up USB Ethernet Connection
> sudo /users/Cours/ele4205/commun/scripts/ifconfig-enp0s29f7-up
3. Clean known_hosts files .
> gedit .ssh/known_hosts
4. Connect to Odroid via ssh and set up pin configuration
> ssh root@192.168.7.2 
> echo 228 > /sys/class/gpio/export
> echo in > /sys/class/gpio/gpio228/direction
> exit

***

## The functionalities
### Log in/Tag in
Some files need to be create or modified in main PATH before using the program. 
By Main path we define it to be ../projectCamera, nothing is saved in git repository.

You will need to create:

+ Face\_Label\_DATA.csv, Blank file.
	
If it's already present:

* Please complete Log/Out Tag Out Procedure 2.3-clear file content.
	
Your are welcome to save this data elsewhere if needed.

### Initialization
In either release or Debug, TCPServeur should be run first. 
Program will open a terminal window and set up some initial server parameter.
After the program outputs on terminal ''Ready to accept'', it's a ideal time to run TCPClient program.

### Main Menu
Program is controlled by either interface outputs connected to board or by a hidden menu available at all time.
Keyboard is read at each 30ms.
#### Hardware
1. Light receptor-Will stop streaming if their is bad light conditions or if it's covered.
2. Push button-Main input to take a action, Forks program to needed fonctions
#### Software
1. Key:*a*-will display Resolution menu.
	*Inputs:  1-160X120 2-320X240 3- 960X720 4-1280X960 -will change window size
2. Key:*b*-will display mode menu. 
	*Inputs: 1-Training(Apprentissage),1-Recognition(Reconaissance)-will fork to corresponding mode
3. Key:*Esc-Key*-will exit client module and send a quit signal to server modules and close

**To use Keys, mouse must be hovering over streaming window **
**To use inputs, must click inside terminal window write input and click enter, you will have to go back after to window to see change **

### Normal Mode
By Default in Training Mode.
Will do nothing if no user is created. 


### Training mode
Responsible of detecting faces and storing 
After clicking b and choosing mode 1, you will have a prompt to create a new user(create a new user folder with new images) or to log in into a existing user (update a existing user folder with new images)
1. 0 To create a new user and folder
2. Any number to to log in into existing user
3. In Training Mode, any click of the pushbutton will save original picture, detected picture and resized face picture in the corresponding sub folder.
It will also update the CSV file with new image path.
### Recognition mode
In Recognition Mode, 
It will load all face sub folder and create a face trained model.
Then any click of the pushbutton will save ToRecon original picture,ToRecon  detected picture and ToRecon  resized face picture in the corresponding current folder.
It will use recognition algorithm to compared resize face(if any) to face trained model and output prediction in format of a new picture with name written on it.

### Log out/Tag out
1. Use Esc-Key
2. Save files elsewhere and delete in succession these folders and files.
	1. Delete ALL **generated** user picture sub-folders.
	2. Delete ToRecon,CropResizePic and DetectedPic .png files in current folder 
	3. Open Face_Label_Data.csv with text editor and clear all data for futur use. CTRL-A, CTRL-X,CTRL-S.


These steps are necessary because:
* no cleaning method has been implemented in the code as of yet
* code is expecting a clean slate before each use
**Presently not part of the Scope of Work** 
**Will be implemented/fix or/and improved in futur revision** 

***

## Acknowledgements
Polytechnique, Richard Gourdeau, Jeremie,Yocto,Open CV, Online tutorials.






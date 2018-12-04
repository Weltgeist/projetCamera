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
### Description: The project

The goal of this project is to interface an Odroid-c2 board with a webcam to a computer through a TCP-IP connection.
***

### Prerequisite
Hardware:
1. Odroid-c2 embedded microcontrollor with a pre-installed OS,in this case a Yocto image.  
2. Scientific Linux 7.5 Computer  
3. USB Logitech c270 webcam  

**Alternative configuration may work, but has not been tested**

***

### Documentation
Open CV version installed on Scientific Linux 7.5:
https://docs.opencv.org/2.4.5/  
Open CV version installed on the Odroid-C2:
https://docs.opencv.org/3.1.0/  
Yocto:
https://www.yoctoproject.org/  
Face Recognition:
https://docs.opencv.org/3.4/da/d60/tutorial_face_main.html  
Tutorial:
https://www.superdatascience.com/opencv-face-recognition/?fbclid=IwAR06Q9KKUCob0067iXzQogP6oozvgMveGPpSD-v7IscJ1Mi1DOHSWlYcrlw  

***

## Compilation: How to use the repository

The repository is divided in two subfolders, the TCP client and TCP server.

### TCPClient

The TCPClient folder contains the source code for the executable that will run on the computer. Create a sister folder named debug, in which you will have to compile and "make" the code with the following instructions in the terminal, or the equivalent:

#### Terminal
> cmake -DCMAKE_BUILD_TYPE=Release ../src  
> make

### TCPServeur

The TCPServeur folder contains the source code for the executable that will run on the Odroid-c2. Create a sister folder named debug, in which you will have to compile and "make" the code with the following instructions in the terminal, or the equivalent:

#### Terminal
> bash  
> source /export/tmp/4205_07/opt/poky/environment-setup-aarch64-poky-linux  
> cmake -DCMAKE_BUILD_TYPE=Release \ -DOpenCV_DIR:STRING="/export/tmp/4205_nn/poky/build-oc2/tmp/sysroots/odroid-c2/usr/share/OpenCV" ../src  
> make  
> scp TCPServeur root@192.168.7.2:/home/root

***

### Setup procedure

Additional steps will be needed to configure certain GPIOs of embedded control and to set up connection.

1. Verify that USB ETHERNET WIRED CONNECTION is set to OFF.
2. Manually set up USB Ethernet Connection
> sudo /users/Cours/ele4205/commun/scripts/ifconfig-enp0s29f7-up
3. Clean known_hosts files.
> gedit .ssh/known_hosts
4. Connect to Odroid via ssh and set up pin configuration
> ssh root@192.168.7.2   
> echo 228 > /sys/class/gpio/export  
> echo in > /sys/class/gpio/gpio228/direction  
> exit  
5. Download file "haarcascade_frontalface_alt.xml" and put it in the same folder as your client's executable.
6. In the code, in the client's class.h, change the values for the path and csv file to fit your computer.
7. Create a blank file named "Face\_Label\_DATA.csv" in the repository identified in your path.

***

## The functionalities

### Initialization
1.TCPServeur should be run first. Run command:
> ./TCPServeur
2.Program will open a terminal window. Wait until "Ready to accept" appears in terminal window, then execute the command:
> ./TCPClient

### Main Menu
Program is controlled by either interface outputs connected to board or by a hidden menu available at all time.

#### Hardware
1. Light receptor: Will stop streaming if there are bad lighting conditions or if it's covered.
2. Push button: Main input to take a action, forks program to needed fonctions.
#### Software
1. Key:*a*-will display Resolution menu.
	*Inputs:  1-160X120 2-320X240 3- 960X720 4-1280X960 -will change window size
2. Key:*b*-will display mode menu. 
	*Inputs: 1-Training(Apprentissage),1-Recognition(Reconaissance)-will fork to corresponding mode
3. Key:*Esc-Key*-will exit client module and send a quit signal to server modules and close

**To use Keys, streaming window must be selected **  
**To use inputs, must click inside terminal window write input and click enter, you will have to go back after to window to see change **

### Training mode
**Has to be selected first. At least two users have to be created, each having taken around 20 pictures **
Responsible of detecting faces and storing them.
After clicking b and choosing mode 1, you will have a prompt to create a new user(create a new user folder with new images) or to log in into a existing user (update a existing user folder with new images)
1. 0 To create a new user and folder
2. Any number to to log in into existing user
3. In Training Mode, any click of the pushbutton will save original picture, detected picture and resized face picture in the corresponding sub folder.
It will also update the CSV file with new image path.

### Recognition mode
**Can be selected only once at least two users have been created and taken around 20 pictures in training mode **
It will load all face sub folder and create a face trained model.
Then any click of the pushbutton will save ToRecon original picture,ToRecon  detected picture and ToRecon  resized face picture in the corresponding current folder.
It will use recognition algorithm to compared resize face(if any) to face trained model and output prediction in format of a new picture with name written on it.

### Log out/Tag out
1. Use Esc-Key
2. Save files elsewhere and delete in succession these folders and files.
	1. Delete ALL **generated** user picture sub-folders.
	2. Delete ToRecon,CropResizePic and DetectedPic .png files in current folder 
	3. Open Face_Label_Data.csv with text editor and clear all data for futur use. CTRL-A, CTRL-X,CTRL-S.

These steps are necessary because: no cleaning method has been implemented in the code as of yet and code is expecting a clean slate before each use.

***
### Doxygen documentation
To obtain the doxygen documentation, follow the steps:

1. In a terminal, place yourself in the folder with your source code
2. Execute the command
> doxygen -g
3. Execute the command
> doxygen
4. In the generated "html" folder, double-click on file "index.html"

***

## Acknowledgements
Polytechnique, Richard Gourdeau, Jeremie Pilon, Yocto, OpenCV, Online tutorials.






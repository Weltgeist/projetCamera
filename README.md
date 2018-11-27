# ELE4205 Team 7

This BitBucket Repository contains the project for Polytechnique Montreal ELE4205 class project for team number 7. The team members are Gabrielle Caron and Samuel Narcisse.

## The project

The goal of this project is to interface an Odroid-c2 board with a webcam to a computer through a TCP-IP connection. The Odroid-c2 should already have a OS, in this case a Yocto image. The computer runs on Scientific Linux 7. The webcam is a USB Logitech c270.

## How to use the repository

The repository is divided in two subfolders, the TCP client and TCP server.

### TCPClient

The TCPClient folder contains the source code for the executable that will run on the computer. In the terminal, you will have to compile and "make" the code with the following instructions, or the equivalent:

> cmake -DCMAKE_BUILD_TYPE=Release \
> make

### TCPServeur

The TCPServeur folder contains the source code for the executable that will run on the Odroid-c2. In the terminal, you will have to compile and "make" the code with the following instructions, or the equivalent:

> source [insert here the path to the sdk for your Yocto image]
> cmake -v -DCMAKE_BUILD_TYPE=Release \ -DOpenCV_DIR:STRING="/export/tmp/4205_nn/poky/build-oc2/tmp/sysroots/odroid-c2/usr/share/OpenCV"
> make


###PROCEDURE

#ETAPE 1: 
S'ASSURER QUE LA CONNECTION FILAIRE USB ETHERNET EST A OFF. 
#ETAPE 2: 
sudo /users/Cours/ele4205/commun/scripts/ifconfig-enp0s29f7-up
#ETAPE 3: 
Vider tout l'information dans ce fichier.
gedit .ssh/known_hosts
#ETAPE 4:
Connexion ssh au Odroid
ssh root@192.168.7.2 
# Etape 5:
echo 228 > /sys/class/gpio/export

# Etape 6:
echo in > /sys/class/gpio/gpio228/direction

# Etape 7:
exit

## The functionalities

This project will allow you to **to be completed**

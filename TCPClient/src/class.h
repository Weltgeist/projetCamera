/**
 * \file class.h
 * \brief Contains the class definitions of objects Resolution and Client.
 * \author ELE4205_07
 * \date 3 december 2018
 *
 */


#ifndef CLASS_H
#define CLASS_H

#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <vector>
using namespace cv;

/**
 * \class Resolution
 * \brief Contains the resolution in x and y of the possible images.
 */
class Resolution
{
private:
	/**
	 * \var resX
	 * \brief The value in x of the resolution.
	 */
	int resX;
	/**
	 * \var resY The value in y of the resolution.
	 */
	int resY;

public:

	/**
	 * \fn Resolution(int a = -1, int b = -1)
	 * \brief Constructor of the Resolution class
	 * \param a The corresponding x value of the resolution.
	 * \param b The corresponding y value of the resolution.
	 */
	Resolution(int a = -1, int b = -1){ resX=a; resY=b;return; }
	/**
	 * \fn ~Resolution()
	 * \brief Destructor of the Resolution class
	 */
	~Resolution(){ return; }
	/**
	 * \fn int getX() const
	 * \brief Accesses the x value.
	 * \return The x value of the resolution.
	 */
	int getX()const{ return resX; };
	/**
	 * \fn int getY() const
	 * \brief Accesses the y value.
	 * \return The y value of the resolution.
	 */
	int getY()const{ return resY; };
	/**
	 * \fn int setX(int a)
	 * \brief Sets the x value.
	 * \param a The x value of the resolution.
	 */
	void setX(int a){ resX = a; };
	/**
	 * \fn void setY(int a)
	 * \brief Sets the y value.
	 * \param a The y value of the resolution.
	 */
	void setY(int a){ resY = a; };
};



/**
 * \class Client
 * \brief Contains the parameters and functions necessary to create and operate the client in the TCP connection.
 */
class Client
{
private:
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
    String face_cascade_name;
    String eyes_cascade_name;
	int sockfd, portno, connectSock;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int n;
	uint32_t messages;
	char buffer[256];
	char* ptrBuffer;
	Mat* img;
	int imgSize;
	vector<uchar> sockData;
	pid_t pid;
	char sctr_img[50];
	string PATH; //Path dans lequel les folders contenant les photos seront places
	string PathCSV;
	vector<Mat> listImages;
	vector<string> labels;
	vector<string> listeNoms;

public:

	/**
	 * \fn Client()
	 * \brief Constructor of the class Client. Initializes some constant values such as paths.
	 */
	Client(){
		face_cascade_name = "haarcascade_frontalface_alt.xml" ;
		eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
		PATH="/export/tmp/4205_07/projet"; //Path dans lequel les folders contenant les photos seront places
		PathCSV = "/export/tmp/4205_07/projet/Face_Label_DATA.csv";
	}
	/**
	 * \fn ~Client()
	 * \brief Destructor of the class Client.
	 */
	~Client(){};
	/**
	 * \fn void error(const char *msg)
	 * \brief Displays an error message and quits.
	 * \param msg The error message to be displayed.
	 */
	void error(const char *msg);
	/**
	 * \fn void createDir(const string& label)
	 * \brief Creates a directory with the specified name at the PATH location.
	 * \param label The name of the person that becomes the name of the created folder.
	 */
	void createDir(const string& label);
	/**
	 * \fn int choixPersonne(int ctr_img)
	 * \brief Prompts the user to choose the person to collect data for in the list of names.
	 * \return The index of the chosen person in the list of names (listeNoms).
	 */
	int choixPersonne();
	/**
	 * \fn void read_csv(char separator = ';')
	 * \brief Reads the CSV file to update the lists of collected images and labels.
	 * \param separator The separator of the csv file, by default ';'.
	 */
	void read_csv(char separator = ';');
	/**
	 * \fn int find_ctr_img(int personne)
	 * \brief Reads the CSV file to find how many pictures of a given person have already been taken.
	 * \param personne The index of the person in the list of names.
	 * \return The iterator of the image counter (ctr_img).
	 */
	int find_ctr_img(int personne);
	/**
	 * \fn void loadCascades()
	 * \brief Loads the xml file necessary for the face detection.
	 */
	void loadCascades();
	/**
	 * \fn void initClient()
	 * \brief Creates a client TCP socket and initializes it with the necessary information.
	 */
	void initClient();
	/**
	 * \fn void clientConnect()
	 * \brief Connects with the TCP Server socket.
	 */
	void clientConnect();
	/**
	 * \fn clientRcvSend()
	 * \brief TCP client socket receives the state of the server (no light, light, push-button released),
	 * then sends the ok to server to send the image.
	 * \return The state of the server as a uint32_t. If state is 0, there is no light, if 1 there is light, if 3 there is light and push-button has been released.
	 */
	uint32_t clientRcvSend();
	/**
	 * \fn void clientInitImg(Resolution (&res)[13], int choix)
	 * \brief Instantiates a new Mat object, fills it with zeros at the chosen size (resolution), calculates its size
	 * and resizes the socket data object.
	 * \param res The table of possible resolutions.
	 * \param choix The user's choice of resolution as an index of res.
	 */
	void clientInitImg(Resolution (&res)[13], int choix);
	/**
	 * \fn void writeToCSV(const string& CSVfilename,const string& IMGfilename,string label, int ctr_img, char separator=';')
	 * \brief Writes the image filename, person's label and image counter as a new line in the CSV file.
	 * \param CSVfilename The name of the csv file to be written to.
	 * \param IMGfilename The name of the file containing the image to be written to the csv.
	 * \param label The label of the person corresponding to the image.
	 * \param ctr_img The iterator that numbers the image.
	 * \param separator The separator of the CSV file, by default ';'.
	 */
	void writeToCSV(const string& CSVfilename,const string& IMGfilename,string label, int ctr_img, char separator=';');
	/**
	 * \fn int detectAndDisplay( char* adress,int ctr_img,const string& Path,int mode=0, std::vector<Rect>* ptrFace=NULL)
	 * \brief Creates an image from the adress filename and performs face detection on it. For all the found faces, a rectangle is drawn around the faces and a "DetectPIC"
	 * is created. A "cropresizePIC" is created with only the cropped and resized face.
	 * \param adress The filename of the image to have face detection done on it.
	 * \param ctr_img The iterator that numbers the image.
	 * \param Path The path in which to put the processed images.
	 * \param mode By default 0. Serves for the recognition mode to modify prtFace.
	 * \param ptrFace By default null. Serves when mode is 1, so recognition mode, to pass by reference a pointer to the rectangles vector containing the detected faces.
	 * \return The number of detected faces.
	 */
	int detectAndDisplay( char* adress,int ctr_img,const string& Path,int mode=0, std::vector<Rect>* ptrFace=NULL);
	/**
	 * \fn void recon(int personne)
	 * \brief Performs the face recognition. Reads the CSV, converts the labels from string to int, prepares the vectors, creates the model, trains it. Then, face detection
	 * is performed, and for every face found performs a prediction of the label. Initial image is modified with rectangles around the faces with the name of the recognized
	 * person above it.
	 * \param personne The index of the person in the list of names.
	 */
	void recon(int personne);
	/**
	 * \fn void clientFork(int mode, int ctr_img, int personne)
	 * \brief Creates a fork in the program execution. Inside the fork are two cases, depending on the mode. In learning mode, images are written, face detection is performed
	 * and if a face has been found, writes it to the CSV. If mode is recognition, image is written and recon function is called. Outside the fork, the image sent by the server
	 * is shown.
	 * \param mode The mode of the program, 0 is learning and 1 is recognition.
	 * \param ctr_img The iterator that numbers the image.
	 * \param personne The index of the person in the list of names.
	 */
	void clientFork(int mode, int ctr_img, int personne);
	/**
	 * \fn void showImage()
	 * \brief Creates a new window and displays the image sent by the server.
	 */
	void showImage();
	/**
	 * \fn void deleteimg()
	 * \brief Deletes the new Mat that was created in image initialization.
	 */
	void deleteimg();
	/**
	 * \fn void clientQuit()
	 * \brief Writes to the socket the quit message to send to the server and closes the socket.
	 */
	void clientQuit();

	/**
	* \fn int get_sockfd() const
	* \brief Gets value for sockfd.
	* \return sockfd.
	*/
	int get_sockfd()const{ return sockfd; };
	/**
	* \fn int get_portno()const
	* \brief Gets value for portno.
	* \return The port number.
	*/
	int get_portno()const{ return portno; };
	/**
	* \fn struct sockaddr_in  get_serv_addr() const
	* \brief Gets value for serv_addr.
	* \return The server address.
	*/
	struct sockaddr_in  get_serv_addr()const{ return serv_addr; };
	/**
	* \fn int get_n() const
	* \brief Gets value for n.
	* \return The value of byte counter n.
	*/
	int get_n()const{ return n; };
	/**
	* \fn Mat* get_img() const
	* \brief Gets value for img.
	* \return The Mat pointer img.
	*/
	Mat* get_img()const{return img;};
	/**
	* \fn int get_imgSize() const
	* \brief Gets value for imgSize.
	* \return The value of the size of img.
	*/
	int get_imgSize()const{ return imgSize; };

	/**
	* \fn void set_sockfd(int a)
	* \brief Sets the value for socket sockfd.
	* \param a The value of sockfd.
	*/
	void set_sockfd(int a){ sockfd = a; };
	/**
	* \fn void set_portno(int a)
	* \brief Sets the value of the port number.
	* \param a The port number.
	*/
	void set_portno(int a){ portno = a; };
	/**
	* \fn void set_serv_addr(int a)
	* \brief Sets the value of server address.
	* \param a The server address.
	*/
	void set_serv_addr(int a){
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(a);};
	/**
	* \fn void set_n( int a)
	* \brief Sets the value of byte counter n.
	* \param a The value of n.
	*/
	void set_n( int a){ n = a; };
	/**
	* \fn void set_messages(uint32_t a)
	* \brief Sets the value of messages.
	* \param a The value of messages.
	*/
	void set_messages(uint32_t a){messages = a;};


};



#endif

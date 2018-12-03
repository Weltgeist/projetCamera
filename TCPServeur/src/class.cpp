
#include "class.h"


//cpp


Resolution operator*(const double factor, const Resolution &b){ return (b*factor); };
Resolution operator/(const double factor, const Resolution &b){ return (b / factor); };

ResolutionFPS operator*(const double factor, const ResolutionFPS &b){ return (b*factor); };
ResolutionFPS operator/(const double factor, const ResolutionFPS &b){ return (b / factor); };

void error(const char *msg)
{
    perror(msg);
    exit(1);
}



void  Serveur::initServeur(int portNum)
{


	 //Create a socket()
	 sockfd = socket(AF_INET, SOCK_STREAM, 0); //AFINET  == communication domain Ipv4, SOCK_STREAM is communication type(TCP in our case), 0 is  value for internet protocole
	 if (sockfd < 0)
		error("ERROR opening socket");

	 //Construct a local address structure
	 bzero((char *) &serv_addr, (uint)sizeof(serv_addr));
	 serv_addr.sin_family = AF_INET;
	 serv_addr.sin_addr.s_addr = INADDR_ANY;
	 serv_addr.sin_port = htons(portNum);

	 //Assign a port to the number with bind() /Bind the local address
	 if (bind(sockfd, (struct sockaddr *) &serv_addr,
			 (uint)sizeof(serv_addr)) < 0)
			  error("ERROR on binding");

	 //Tell the system to allow connection made to that port with listen/ Mark the socket so it will listen for incoming connect
	 listen(sockfd,5); //put the socket in passive mode and set 5 as the maximum number for queue

	 clilen = sizeof(cli_addr);
}


void Serveur::servAccept(){

	 newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
	 if (newsockfd < 0)
	  error("ERROR on accept");
}


uint32_t Serveur::servSendRecv(uint32_t etat){
	uint32_t result;

	// Envoyer l'etat au client
	bzero(buffer,1024);
	sprintf(buffer,"%u", etat);
	n = write(newsockfd,buffer,(int)sizeof(etat));
	if (n < 0){ error("ERROR writing to socket");}

	  // Lire le uint_32 envoye par le client
	 bzero(buffer,1024);
	 n = read(newsockfd,buffer,1023);
	 if (n < 0) error("ERROR reading from socket");

	//Decoder le uint32 soit ici le OK/Quit
	result = strtol(buffer,&ptrBuffer,10);

	return result;
}


void Serveur::servCaptureSend(Mat& frame, VideoCapture &capture){

	//Capture
	capture >> frame;
	imgSize = frame.total()*(frame.elemSize());

	//Send data
	bytes = send(newsockfd, frame.data, imgSize, 0);
}


void Serveur::servClose(){
	close(newsockfd);
	close(sockfd);
}



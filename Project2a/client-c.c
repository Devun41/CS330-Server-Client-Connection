/*****************************************************************************
 * client-c.c                                                                 
 * Name:
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcnt1.h>

#define SEND_BUFFER_SIZE 2048

/*Step 1: (client) Prepare the HTTP request and put it in the buffer, and send
Step 3: (client) Receive the content, and print it out*/
/*
 * main()
*/
int main(int argc, char **argv) {
  
  struct hostent *hp; 
  struct sockaddr_in sin;
  char *host,*port;
  char buf[MAX_SIZE];
  int s, len;
  char *URI;
  //check if two arguments passed, if not exit
  if (argc != 2) {
    fprintf(stderr, "Usage: %s [absolute URI]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  URI= argv[1]; //set URI to second argument passed

/* translate host name into peer IP Address*/
  hp=gethostbyname(host);
  if(!hp){
    fprintf(stderr, "%s: unknown host\n", host);
    exit(1);
  }

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);

  /*TO-DO: check if there is an abs_path in URI, if not then use port 80*/
  
    
    char *hostname; //hostname

    int hostlen; //hostname length
    int abslen; //abs_path length

    //finding if URI has an absolute path, if not set port to 80 **not correct, needs to accept IP addresses
    hostlen=strchr(UNI,'/')-1; //checks for backslash, stores place in hostlen -1 
    strcopy(hostname,&UNI,hostlen);
     abslen=strlen(UNI)-strlen(hostlen)+2;
      char abs_path[abslen+1]; //sets the abs_path
      strcopy(abs_path,&UNI[hostlen],abslen); //gets the substring from hostlen to the end of UNI and stores in abs_path
/*
    if(hostlen>0){
      *port=80;
    }
    else if(strstr(UNI,'www.')==NULL){
      UNI="www."+UNI;
     
      *port=URI;
    }
    else if(strstr(UNI,'www.')>-1)){
      abslen=strlen(UNI)-strlen(hostlen)+2
      char abs_path[abslen+1]; //sets the abs_path
      strcopy(abs_path,&UNI[hostlen],abslen); //gets the substring from hostlen to the end of UNI and stores in abs_path
      *port=URI;
    }
  else{
    *port=URI;
  }
  */
  


  sin.sin_port = htons(atoi(port));
  //Step 1: (client) Prepare the HTTP request and put it in the buffer, and send
  write(s,"GET /"+abs+" HTTP/1.1\r\nHost:"+hostname+"\r\n\r\n", strlen("GET /"+abs+" HTTP/1.1\r\nHost:"+hostname+"\r\n\r\n")); //adds request to buffer

  /* active open */
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }

  if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0){
    perror("simplex-talk: connect");
    close(s);
    exit(1);
  }
  
  int size;
  while( (size=fread(buf, 1, MAX_SIZE, stdin) )) {
    if(send(s, buf, size, 0) < 0) {
      perror("client: send");
    }
  }

 



  bzero(buf,SEND_BUFFER_SIZE);

  
// Done, close the s socket descriptor
  close(s);

  return 0;
}  

/*
The client should take one command-line argument: the hostname or
IP address of the server, followed by the abs_path
  
  //check to see if there is a abs_path in URI, if not then use port 80 to connect to server

For example, the following

./client-c daemon.bradley.edu/research.html

provides abs_path /research.html to a file research.html under 
the web root of the web server daemon.bradley.edu

The default abs_path is

    /
if no other subpath/file name is provided

For example, the following should return the default page configured
 on the server

./client-c daemon.bradley.edu

or

./client-c daemon.bradley.edu/

The client should use port 80 to connect to the server

The client will form an HTTP request based on the hostname 
(or IP address), default port number 80, and abs_path

After sending out the HTTP request to the server, the client will wait
 for the web server to respond

Each client should gracefully handle error values potentially returned 
by socket programming library functions.
   */



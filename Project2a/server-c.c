/*****************************************************************************
 * server-c.c                                                                 
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
#include <errno.h>

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048
/*Step 2: (server) Receive the HTTP request, parse the request, and get the file to be opened
Step 2.1: (server) If the file does not exist, prepare the 404 message, put it in the buffer, send
Step 2.2: (server) If the file exists, open the file, put the content in the buffer, and send*/
/*
 * main():
 */
int main(int argc, char **argv) {
  char *server_port;
  char *filename;
  struct sockaddr_in sin;
  char buf[RECV_BUFFER_SIZE];
  int buf_len;
  socklen_t addr_len;
  int s, new_s;
  char *port;

//3 arguments: server-c.c server_port filename
  if (argc != 3) {
    fprintf(stderr, "Usage: %s [default web content file]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  filename = argv[2];

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = 80;

  /* setup passive open */
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
    perror("simplex-talk: bind");
    exit(1);
  }
  listen(s, MAX_PENDING);

  /* wait for connection, then receive and print text
    parse the string from the buffer "buf", by parsing for www
     if the file doesnt exist, prepare 404 error and send it back to client 
     
     use strrchr() fxn to parse string to the file name, check if it exists
     if it doesnt, return Error 404 not found: HTTP/1.1 404 Not Found\r\n \r\n
     */
  while(1) {
    if ((new_s = accept(s, (struct sockaddr *)&sin, &addr_len)) < 0) {
      fprintf(stderr, "error: %s accept\n", argv[0]);

    exit(1);
    }
    while ( (buf_len = recv(new_s, buf, sizeof(buf), 0)) ) {
      fwrite(buf, 1, buf_len, stdout);
    }
    fflush(stdout);
    close(new_s);
  }




  close(s);
  return 0;
}
  /*
  
   The server program should listen on a socket, wait for a client to 
   connect, receive the HTTP request from the client, send the content 
   of the page back to the client (when the request is valid and the file
    does exist), and then wait for the next client indefinitely.

Each server should take one command-line argument: the default file name
 with the web content

For example, if the argument is hello.html and the HTTP request has
 abs_path   /
the server will get the content from hello.html file and send its content
 to the client

Each server should accept and process client communications in an infinite
 loop, allowing multiple clients to send messages to the same server. The
  server should only exit in response to an external signal (e.g. SIGINT 
  from pressing ctrl-c).

Each server should maintain a short (5-10) client queue and handle 
multiple client connection attempts sequentially. In real applications,
 a TCP server would fork a new process to handle each client connection
  concurrently, but that is not necessary for this assignment.

Each server should gracefully handle error values potentially returned 
by socket programming library functions (see specifics for each language
 below). Errors related to handling client connections should not cause 
 the server to exit after handling the error; all others should.
   */





/*! @file cgi.cpp
 * @brief CGI used for the webinterface
 */

#include <cstdio>
#include <cstdlib>
using namespace std;


#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>

#include "cgi.h"



void copyAll(int outFd, int inFd, int* num_written) {

	if(num_written) *num_written=0;
	
	size_t num;
	char buffer[1024];
	
	while((num=read(inFd, buffer, sizeof(buffer))) != 0) {
		if(num > 0) {
			if(num_written) *num_written+=num;
			while(write(outFd, buffer, num) == -1 
					&& (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR)) {
				//usleep(1000);
			}
		}
	}
}


int main(int argc, char ** argv) {
	
	/* process request */
	int fd, err, num_written;
	
	
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(fd < 0) {
		fprintf(stderr, "Error creating the socket: %s", strerror(errno));
		return(-1);
	}
	
	{
		struct sockaddr_un servaddr;
		servaddr.sun_family=AF_UNIX;
		
		strncpy(servaddr.sun_path, CGI_SOCKET_PATH, sizeof servaddr.sun_path);
		
		err = connect(fd, (struct sockaddr *) &servaddr, SUN_LEN(&servaddr));
		if(err != 0) {
			fprintf(stderr, "Error connecting to the server: %s", strerror(errno));
			close(fd);
			return(-1);
		}
	}
	
	copyAll(fd, 0, &num_written); //copy POST data from stdin to socket
	
	if(num_written==0) { //no POST data -> try GET variables
		for(int arg=1; arg<argc; ++arg) {
			write(fd, argv[arg], strlen(argv[arg]));
			write(fd, "\n", 1);
		}
	}
	
	
	err = shutdown(fd, 1);
	if(err != 0) {
		fprintf(stderr, "Error closing the writing part of the connection: %s", strerror(errno));
		close(fd);
		return(-1);
	}
	
	copyAll(1, fd, &num_written); //copy socket data to stdout
	
	if(num_written==0) {
		printf("Status: 200 OK\n");
		printf("Content-Type: text/plain\n");
		printf("\n");
		fflush(stdout);
	}
	
	err = close(fd);
	if(err != 0) {
		fprintf(stderr, "Error closing the writing part of the connection: %s", strerror(errno));
		return(-1);
	}
}

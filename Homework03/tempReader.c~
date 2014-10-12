#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>	// Defines signal-handling functions (i.e. trap Ctrl-C)
#include "gpio-utils.h"

 /****************************************************************
 * Constants
 ****************************************************************/
 
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

/****************************************************************
 * Global variables
 ****************************************************************/
int keepgoing = 1;	// Set to 0 when ctrl-c is pressed

/****************************************************************
 * signal_handler
 ****************************************************************/
void signal_handler(int sig);
// Callback called when SIGINT is sent to the process (Ctrl-C)
void signal_handler(int sig)
{
	printf( "Ctrl-C pressed, cleaning up and exiting..\n" );
	keepgoing = 0;
}

int main()
{
	struct pollfd fdset[2];
	int nfds = 2;
	int alert_fd, timeout, rc;
	char command[50];
	unsigned int alert;
	int len;

	strcpy(command, "./i2cTemp");
	system(command);
	
	// Set the signal callback for Ctrl-C
	signal(SIGINT, signal_handler);

	alert = 30;
	gpio_export(alert);
	gpio_set_dir(alert, "in");
	gpio_set_edge(alert, "rising");
	alert_fd = gpio_fd_open(alert, O_RDONLY);
	timeout = POLL_TIMEOUT;

	while(keepgoing){
	
		memset((void*)fdset, 0, sizeof(fdset));

		fdset[0].fd = STDIN_FILENO;
		fdset[0].events = POLLIN;
      
		fdset[1].fd = alert_fd;
		fdset[1].events = POLLPRI;

		rc = poll(fdset, nfds, timeout);      

		if (rc < 0) {
			printf("\npoll() failed!\n");
			return -1;
		}
      
		if (rc == 0) {
			printf(".");
		}

		if (rc == 1) {
			printf("polled\n");
		}
            
		if (fdset[1].revents & POLLPRI) {
			system(command);
		}

		fflush(stdout);
	}	
	gpio_fd_close(alert_fd);
	return 0;
}

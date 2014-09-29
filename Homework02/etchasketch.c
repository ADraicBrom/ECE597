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
int gridSize;

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


void printGrid(char (*pGrid)[gridSize])
{
	int i, k;
	for(i=0; i<gridSize; i++){
		for(k=0; k<gridSize; k++){
			printf("%c", pGrid[i][k]);
		}
		printf('\n');
	}
	printf('\n');
}

void clear(char (*pGrid)[gridSize])
{
	int i;
	int k;
	for(i=0; i<gridSize; i++){
		for(k=0; k<gridSize; k++){
			pGrid[i][k]=' ';
		}
	}
}

int main()
{

	struct pollfd fdset[5];
	int nfds = 5;
	int button0_fd, button1_fd, button2_fd, button3_fd, timeout, rc;
	int led0_fd, led1_fd, led2_fd, led3_fd;
	char buf[MAX_BUF];
	unsigned int button0, button1, button2, button3;
	unsigned int led0, led1, led2, led3;
	int len;
	int toggle0 = 1;
	int toggle1 = 1;
	int toggle2 = 1;
	int toggle3 = 1;

	// Set the signal callback for Ctrl-C
	signal(SIGINT, signal_handler);

	//gpio = atoi(argv[1]);
	button0 = 30;
	button1 = 31;
	button2 = 48;
	button3 = 3;

	led0 = 60;
	led1 = 50;
	led2 = 51;
	led3 = 49;

	gpio_export(button0);
	gpio_export(button1);
	gpio_export(button2);
	gpio_export(button3);

	gpio_export(led0);
	gpio_export(led1);
	gpio_export(led2);
	gpio_export(led3);

	//gpio_export(gpio);
	gpio_set_dir(button0, "in");
	gpio_set_dir(button1, "in");
	gpio_set_dir(button2, "in");
	gpio_set_dir(button3, "in");
	gpio_set_dir(led0, "out");
	gpio_set_dir(led1, "out");
	gpio_set_dir(led2, "out");
	gpio_set_dir(led3, "out");
	gpio_set_edge(button0, "both");  // Can be rising, falling or both
	gpio_set_edge(button1, "both");
	gpio_set_edge(button2, "both");
	gpio_set_edge(button3, "both");
	button0_fd = gpio_fd_open(button0, O_RDONLY);
	button1_fd = gpio_fd_open(button1, O_RDONLY);
	button2_fd = gpio_fd_open(button2, O_RDONLY);
	button3_fd = gpio_fd_open(button3, O_RDONLY);
	
	led0_fd = gpio_fd_open(led0, O_RDONLY);
	led1_fd = gpio_fd_open(led1, O_RDONLY);
	led2_fd = gpio_fd_open(led2, O_RDONLY);
	led3_fd = gpio_fd_open(led3, O_RDONLY);

	timeout = POLL_TIMEOUT;

	int i, k, gridS;
	int x=0;
	int y=0;
	int moveX, moveY;
	char string[8];
	printf("Input grid size\n");
	scanf("%i", &gridSize);
	printf("size input\n");
	printf("%i",gridSize);
	char grid[gridSize][gridSize];
	//char *pGrid=grid;
	printf("grid created");
	for(i=0; i<gridS; i++){
		for(k=0; k<gridSize; k++){
			grid[i][k]=' ';
		}
	}
	printf("grid set");

	//gridSize = &gridS;
	
	printGrid(grid);
	
	while(keepgoing){
		moveX = 0;
		moveY = 0;
		
		memset((void*)fdset, 0, sizeof(fdset));

		fdset[0].fd = STDIN_FILENO;
		fdset[0].events = POLLIN;
      
		fdset[1].fd = button0_fd;
		fdset[1].events = POLLPRI;

		fdset[2].fd = button1_fd;
		fdset[2].events = POLLPRI;

		fdset[3].fd = button2_fd;
		fdset[3].events = POLLPRI;

		fdset[4].fd = button3_fd;
		fdset[4].events = POLLPRI;

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
			toggle0 = !toggle0;
			gpio_set_value(led0, toggle0);
			moveX = -1;
		}

		if (fdset[2].revents & POLLPRI) {
			toggle1 = !toggle1;
			gpio_set_value(led1, toggle1);
			moveY = 1;
		}

		if (fdset[3].revents & POLLPRI) {
			toggle2 = !toggle2;
			gpio_set_value(led2, toggle2);
			moveY = -1;
		}

		if (fdset[4].revents & POLLPRI) {
			toggle3 = !toggle3;
			gpio_set_value(led3, toggle3);
			moveX = 1;
		}

		if (fdset[0].revents & POLLIN) {
			(void)read(fdset[0].fd, buf, 1);
			printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
		}
		
		if(x+moveX > gridSize || x+moveX < 0 || y+moveY > gridSize || y+moveY < 0){printf("OUT OF BOUNDS\n");}
		else{
			x += moveX;
			y += moveY;
			grid[y][x] = 'X';
			printGrid(grid);
		}

		fflush(stdout);
	}
}



/* Copyright (c) 2011, RidgeRun
 * All rights reserved.
 *
From https://www.ridgerun.com/developer/wiki/index.php/Gpio-int-test.c

 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the RidgeRun.
 * 4. Neither the name of the RidgeRun nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY RIDGERUN ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL RIDGERUN BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

/****************************************************************
 * Main
 ****************************************************************/
int main(int argc, char **argv, char **envp)
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

	if (argc < 1) {
		printf("Usage: gpio-int <gpio-pin>\n\n");
		printf("Waits for a change in the GPIO pin voltage level or input on stdin\n");
		exit(-1);
	}

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
 
	while (keepgoing) {
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
			lseek(fdset[1].fd, 0, SEEK_SET);  // Read from the start of the file
			len = read(fdset[1].fd, buf, MAX_BUF);
			printf("\npoll() GPIO %d interrupt occurred, value=%c, len=%d\n",
				 button0, buf[0], len);
			toggle0 = !toggle0;
			gpio_set_value(led0, toggle0);
		}

		if (fdset[2].revents & POLLPRI) {
			lseek(fdset[2].fd, 0, SEEK_SET);  // Read from the start of the file
			len = read(fdset[2].fd, buf, MAX_BUF);
			printf("\npoll() GPIO %d interrupt occurred, value=%c, len=%d\n",
				 button1, buf[0], len);
			toggle1 = !toggle1;
			gpio_set_value(led1, toggle1);
		}

		if (fdset[3].revents & POLLPRI) {
			lseek(fdset[3].fd, 0, SEEK_SET);  // Read from the start of the file
			len = read(fdset[3].fd, buf, MAX_BUF);
			printf("\npoll() GPIO %d interrupt occurred, value=%c, len=%d\n",
				 button2, buf[0], len);
			toggle2 = !toggle2;
			gpio_set_value(led2, toggle2);
		}

		if (fdset[4].revents & POLLPRI) {
			lseek(fdset[4].fd, 0, SEEK_SET);  // Read from the start of the file
			len = read(fdset[4].fd, buf, MAX_BUF);
			printf("\npoll() GPIO %d interrupt occurred, value=%c, len=%d\n",
				 button3, buf[0], len);
			toggle3 = !toggle3;
			gpio_set_value(led3, toggle3);
		}

		if (fdset[0].revents & POLLIN) {
			(void)read(fdset[0].fd, buf, 1);
			printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
		}

		fflush(stdout);
	}

	gpio_fd_close(button0_fd);
	gpio_fd_close(button1_fd);
	gpio_fd_close(button2_fd);
	gpio_fd_close(button3_fd);
	gpio_fd_close(led0_fd);
	gpio_fd_close(led1_fd);
	gpio_fd_close(led2_fd);
	gpio_fd_close(led3_fd);
	return 0;
}


#include <stdio.h>
#include <string.h>

int main()
{
	char command[50];

	strcpy(command, "./i2cTemp");
	system(command);

	while(1){
	
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
			lseek(fdset[1].fd, 0, SEEK_SET);  // Read from the start of the file
			len = read(fdset[1].fd, buf, MAX_BUF);
			printf("\npoll() GPIO %d interrupt occurred, value=%c, len=%d\n",
				 button0, buf[0], len);
			toggle0 = !toggle0;
			gpio_set_value(led0, toggle0);
		}
	}	
}
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define DEVICE_FILE	"/dev/gpio_w_driver"

int main() {
	int file;
	int i;
	char command;
	
	printf("Hello from the User Application\n");
	if((file = open(DEVICE_FILE, O_RDWR)) < 0) {
		printf("Could not open the device file\n");
		return -1;
	}

loop: if(i<5) {
	      command = '0';
	      if(write(file, &command, sizeof(command)) < 0) {
		      printf("could not write to device file\n");
		      return -1;
	      }
	      sleep(1);

	      command = '1';
	      if(write(file, &command, sizeof(command)) < 0) {
		      printf("Could not write to device file\n");
		      return -1;
	      }
	      sleep(1);
	      
	      i++;
	      goto loop;
      }
      close(file);
      return 0;
}

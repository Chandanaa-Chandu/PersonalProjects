#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define DEVICE_FILE	"/dev/gpio_rw_driver"

int main(void) {
	int file;
	char status;
	char set;

	/* Open a device file */
	if((file = open(DEVICE_FILE, O_RDWR)) < 0) {
		printf("User - Could not open device file %s\n", DEVICE_FILE);
		return -1;
	}

	while(1) {
		/* Get a Push button status */
		if(read(file, &status, sizeof(status)) < 0) {
			printf("User - Unable to read the status of button\n");
			return -1;
		}
		
		if(status == '1') {
			printf("User - Button Pressed\n");
	
			/* Turn ON the LED */
			set = '1';
			if(write(file, &set, sizeof(set)) < 0) {
				printf("User - Unable to turn ON the LED\n");
				return -1;
			}
		} else if(status == '0') {
			printf("User - Button Released\n");

			/* Turn OFF the LED */
			set = '0';
			if(write(file, &set, sizeof(set)) < 0) {
				printf("User - Unable to turn OFF the LED\n");
				return -1;
			}
		} else {
			printf("User - Invalid read status\n");
		}
	}

		close(file);
		return 0;
}

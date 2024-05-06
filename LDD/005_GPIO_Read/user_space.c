#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_FILE	"/dev/gpio_rd_driver"

int main(void)
{
	int file;
	char status[3];

	if((file = open(DEVICE_FILE, O_RDWR)) < 0) {
		printf("User_Space - Unable to open device file\n");
		return -1;
	}

	while(1) {
		if(read(file, &status, sizeof(status)) < 0) {
			printf("User_Space - Read failed\n");
			return -1;
		}
		if(status[0] == '1') {
			printf("User_Space - Push button is pressed\n");
		} else if(status[0] == '0') {
			printf("User_Space - Push button is released\n");
		} else {
			printf("User_Space - Data not correct\n");
		}
	}
	close(file);
	return 0;
}

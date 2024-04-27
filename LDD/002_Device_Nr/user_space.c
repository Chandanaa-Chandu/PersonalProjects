#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int dev_file;

	dev_file=open("/dev/device_reg_devfile", O_RDONLY);

	if(dev_file == -1) {
		printf("Could not open device file\n");
		return -1;
	}

	printf("Device file opened successfully\n");
	close(dev_file);
	return 0;
}


# This module will automatically assign a device number (major nad minor numbers)

This will dynamically create device class and device file along with the driver and automatically register a device file with the kernel
Also implemented buffer read an write from/to device file.

To write into the buffer in cmd line:
```bash
echo "The_message" > /dev/<driver_name>
```

To read the buffer from the device file in cmd line:
```bash
head -n 1 /dev/<driver_name>
```

To give the access permission to the device file/driver
```bash
sudo chmod 666 /dev/<driver_name>
```

obj-m += gpio_rw.o

module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

user:
	gcc user_space.c -o user_space

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f user_space


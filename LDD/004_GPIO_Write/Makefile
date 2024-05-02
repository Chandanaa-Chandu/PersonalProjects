obj-m += led_write.o

src = user_space

devfile:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

userfile:
	gcc $(src).c -o $(src)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f $(src)

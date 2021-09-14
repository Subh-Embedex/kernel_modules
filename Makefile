#Makefile for compiling kernel module

obj-m+=hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 

deploy:
	sudo insmod hello.ko

undeploy:
	sudo rmmod hello.ko


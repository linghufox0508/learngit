#KERNEL_DIR := /lib/modules/$(shell uname -r)/build
#PWD := $(shell pwd)

#module-objs:=yin.o

#obj-m := hello.o

#default:
#	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules


KVERS = $(shell uname -r)

#kernel modules
obj-m += hello.o

build:kernel_modules

kernel_modules:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) clean

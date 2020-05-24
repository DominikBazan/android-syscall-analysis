obj-m:= lkm_android.o
KERNEL_DIR := /opt/kernel
CCPATH_EXT := x86_64-linux-android-

EXTRA_CFLAGS=-fno-pic
 
all:
	make ARCH=x86_64 CROSS_COMPILE=$(CCPATH_EXT) -C $(KERNEL_DIR) M=$(PWD) EXTRA_CFLAGS=$(EXTRA_CFLAGS) modules
clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
	rm -rf *.c~
	rm -rf *.o
	rm -f modules.order

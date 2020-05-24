cd opt/kernel
echo $PWD

export ARCH=x86_64
echo "ARCH Configured \n"

export CROSS_COMPILE=x86_64-linux-android-
echo "CROSS_COMPILE Configured \n"

export PATH=$PATH:/opt/android-ndk/x86_64-linux-android-4.9/bin
echo "PATH Configured \n"

echo "Run defconfig file. WAIT PLEASE ...\n"
make x86_64_ranchu_defconfig
echo "Config finished \n"

docker run -v $PWD/android-4.14-p-release/:/opt/kernel \
	-v $PWD/android-ndk:/opt/android-ndk \
	-v $PWD/androidLKM:/opt/androidLKM \
	-v $PWD/3_config_kernel.sh:/3_config_kernel.sh \
	-v $PWD/4_compile_docker.sh:/opt/4_compile_docker.sh \
	-it our_android_kernel bash 

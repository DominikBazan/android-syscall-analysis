export SYSCALL_TABLE=$(grep sys_call_table $PWD/kernel/System.map | awk '{print $1}') 
echo "SYSCALL_TABLE = " 
echo $SYSCALL_TABLE
sed -i s/SYSCALL_TABLE/$SYSCALL_TABLE/g $PWD/androidLKM/lkm_android.c
echo "Sed completed"
cd androidLKM
echo $PWD 
make

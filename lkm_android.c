#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/semaphore.h>
#include <linux/string.h>
#include <asm/cacheflush.h>
#include <linux/sched.h>

#define N 9

MODULE_AUTHOR("Andrea Sindoni @invictus1306");
MODULE_LICENSE("GPL");
MODULE_VERSION("1");
MODULE_DESCRIPTION("Android syscall monitor");

void **sys_call_table;

asmlinkage ssize_t (*original_open)(int, const char *, int, int);
asmlinkage ssize_t (*original_close)(int);
asmlinkage ssize_t (*original_read)(unsigned int, char *, int);
asmlinkage ssize_t (*original_write)(int , char *, size_t);
asmlinkage long (*original_creat)(const char __user *, umode_t);
asmlinkage long (*original_rmdir)(const char __user *);
asmlinkage long (*original_mkdir)(const char __user *, umode_t);

asmlinkage ssize_t our_read(unsigned int fd, char *buf, int count)
{
    printk (KERN_INFO "SYS_READ: %s\n", buf);
    return original_read(fd, buf, count);
}

asmlinkage ssize_t our_write (int fd, char *buf, size_t count)
{
    printk (KERN_INFO "SYS_WRITE: %s\n", buf);
    return original_write(fd, buf, count);
}

asmlinkage ssize_t our_open(int dirfd, const char *file, int flags, int mode)
{  
    int i;

    const char *strings[N] = {
            "/data/data/com.android.providers.contacts/databases/contacts2.db",
            "/data/data/com.android.providers.telephony/databases/telephony.db",
            "/data/data/com.android.providers.telephony/databases/mmssms.db",
            "/data/data/com.facebook.katana/databases",
            "/data/data/com.facebook.orca/databases",
            "/data/data/com.skype.raider/files/shared.xml",
            "/data/data/com.whatsapp/shared_prefs",
            "/data/data/com.whatsapp/shared_prefs/RegisterPhone.xml",
            "/data/data/com.viber.voip/files"
    };

    for (i=0; i<N; i++)
    {
        if (strcmp(file, strings[i]) == 0)
        {
            printk( KERN_INFO "Task %s [PID:%d] make use of this file: %s \n", current->comm, current->pid, file);
            break;
        }    
    }

    return original_open(dirfd, file, flags, mode);
}

asmlinkage ssize_t our_close(int fd)
{
    printk(KERN_INFO "SYS_CLOSE %s\n", current->comm);
    return original_close(fd);
}

asmlinkage ssize_t our_creat (const char __user *pathname, umode_t mode)
{
    printk (KERN_INFO "SYS_CREAT %s\n", pathname);
    return original_creat(pathname, mode);
}

asmlinkage ssize_t our_rmdir (const char __user *pathname)
{
    printk (KERN_INFO "SYS_RMDIR %s\n", pathname);
    return original_rmdir(pathname);
}

asmlinkage ssize_t our_mkdir (const char __user *pathname, umode_t mode)
{
    printk (KERN_INFO "SYS_MKDIR %s\n", pathname);
    return original_mkdir(pathname, mode);
}

int init_module(void)
{
    sys_call_table = (void*)0x00;
    original_open = sys_call_table[__NR_openat];
    original_close = sys_call_table[__NR_close];
    original_read = sys_call_table[__NR_read];
    original_write = sys_call_table[__NR_write];
    original_creat = sys_call_table[__NR_creat];
    original_rmdir = sys_call_table[__NR_rmdir];
    original_mkdir = sys_call_table[__NR_mkdir];
    
    sys_call_table[__NR_openat] = our_open;
    sys_call_table[__NR_close] = our_close;
    sys_call_table[__NR_read] = our_read;
    sys_call_table[__NR_write] = our_write;
    sys_call_table[__NR_creat] = our_creat;    
    sys_call_table[__NR_rmdir] = our_rmdir;
    sys_call_table[__NR_mkdir] = our_mkdir;
    
    return 0;
}

void cleanup_module(void)
{
    sys_call_table[__NR_openat] = original_open;
    sys_call_table[__NR_close] = original_close;
    sys_call_table[__NR_read] = original_read;
    sys_call_table[__NR_write] = original_write;
    sys_call_table[__NR_creat] = original_creat;
    sys_call_table[__NR_rmdir] = original_rmdir;
    sys_call_table[__NR_mkdir] = original_mkdir;
}

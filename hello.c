#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*header files  to support char device*/

#include <linux/cdev.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Subhankar");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

#define MY_DEV_MAJOR_NUMBER     220

static int dummy_param=7;
module_param(dummy_param,int,0);

static struct cdev my_dev;
/*device open function*/
static int my_dev_open(struct inode* inode,struct file* file)
{
pr_info("my_dev_open() is called.\n");
return 0;
}

/*device close function */
static int my_dev_close(struct inode *inode,struct file* file)
{
pr_info("my_dev_close() is called .\n");
return 0;
}

static const  struct file_operations my_dev_fops ={
.owner= THIS_MODULE,
.open = my_dev_open,
.release =my_dev_close
};

static int __init hello_init(void)
{
int ret ;

/*get first device identifier*/
dev_t dev= MKDEV(MY_DEV_MAJOR_NUMBER,0);
pr_info("module init");

/*Allocate a number od devices*/
ret = register_chrdev_region(dev,1,"my_char_dev");

if(ret<0)
{
pr_info("unable to allocate major number %d\n",MY_DEV_MAJOR_NUMBER);
return ret;
}

/*Initialize the cdev and add it to kernel space*/

cdev_init(&my_dev,&my_dev_fops);
ret =cdev_add(&my_dev,dev,1);

if(ret<0)
{
pr_info("unable to add cdev\n");
unregister_chrdev_region(dev,1);
return ret;
}

return 0;
}

static void  __exit hello_exit(void)
{
printk(KERN_INFO "Exit from module");
cdev_del(&my_dev);
unregister_chrdev_region(MKDEV(MY_DEV_MAJOR_NUMBER,0),1);
}

module_init(hello_init);
module_exit(hello_exit);


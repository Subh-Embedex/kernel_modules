#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Subhankar");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

static int dummy_param=7;
module_param(dummy_param,int,0);

static int __init hello_init(void)
{
printk(KERN_INFO "Hi There");
pr_info("Hello There!");
pr_info("mod param is %d",dummy_param);
return 0;
}

static void  __exit hello_exit(void)
{
printk(KERN_INFO "Exit from module");
}

module_init(hello_init);
module_exit(hello_exit);


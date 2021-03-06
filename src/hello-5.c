/*
 * hello-5.c - Demonstrates command line argument passing to a module.
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

#define DRIVER_AUTHOR "Raghu Murugesan <ragmurug@cisco.com>"
#define DRIVER_DESC   "A sample driver"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);    /* Who wrote this module? */
MODULE_DESCRIPTION(DRIVER_DESC);    /* What does this module do */
MODULE_SUPPORTED_DEVICE("testdevice");

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "test string";
static int myintArray[2] = {1, 2};
static int arr_argc = 0;

/* 
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits, 
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 */

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");

/*
 * module_param_array(name, type, num, perm);
 * the first param is the parameter's (in this case the array's) name
 * The second param is the data type of the element of the array
 * The third argument is a pointer to the variable that will store the number
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */

module_param_array(myintArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintArray, "An array of integers");

static int __init hello_5_init(void)
{
    int i;
    printk(KERN_EMERG "Hello, world 5\n=============\n");
    printk(KERN_EMERG "myshort is a short integer: %hd\n", myshort);
    printk(KERN_EMERG "myint is an integer: %d\n", myint);
    printk(KERN_EMERG "mylong is a long integer: %ld\n", mylong);
    printk(KERN_EMERG "mystring is a string: %s\n", mystring);
    for (i = 0; i < (sizeof myintArray / sizeof (int)); i++)
    {
        printk(KERN_EMERG "myintArray[%d] = %d\n", i, myintArray[i]);
    }
    printk(KERN_EMERG "got %d arguments for myintArray.\n", arr_argc);
    return 0;
}

static void __exit hello_5_exit(void)
{
    printk(KERN_EMERG "Goodbye, world 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);

/*
 * chardev.c: Creates a read-only char device that says how many times
 * you've read from the dev file
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */

/*
 * Prototypes - this would normally go in a .h file
 */

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev" /* dev name as it appears in /proc/devices */
#define BUF_LEN 80 /* Max length of the message from the device */

/*
 * Global variable are declared as static, so are the global within the file.
 */

static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0;	/* Is device open */

static char msg[BUF_LEN];
static char *msg_ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/*
 * This function is called when the module is loaded
 */
int init_module(void)
{
	Major = register_chardev(0, DEVICE_NAME, &fops);
	if (Major < 0) {
		
	}
}


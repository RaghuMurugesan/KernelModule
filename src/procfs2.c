/**
 * procfs2.c - create a file in /proc
 */

#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module */
#include <linux/proc_fs.h>	/* Necessary because we use the proc fs */
#include <asm/uaccess.h>	/* for copy_from_user */

#define PROCFS_MAX_SIZE		1024
#define PROCFS_NAME			"buffer1k"

/**
 * This structure hold information about the /proc file
 */
static struct proc_dir_entry *Our_Proc_File;

/**
 * The buffer used to store character for this module
 */
static char procfs_buffer[PROCFS_MAX_SIZE];

/**
 * The size of the buffer
 */
static unsigned long procfs_buffer_size = 0;

/**
 * This function is called when the /proc file is read
 */
int
procfile_read(char *buffer,
	      char **buffer_location,
	      off_t offset, int buffer_length, int *eof, void *data)
{
	int ret;

	printk(KERN_INFO "procfile_read (/proc/%s) called\n", PROCFS_NAME);

	/*
	 * We give all of our information in one go, so if the
	 * user asks us if we have more information the
	 * answer should always be no.
	 *
	 * This is important because the standard read
	 * function from the library would continue to issue
	 * the read system call until the kernel replies
	 * that it has no more information, or until its
	 * buffer is filled.
	 */
	if (offset > 0) {
		/* We have finished to read return 0 */
		ret = 0;
	} else {
		/* fill the buffer, return the buffer size */
		memcpy(buffer, procfs_buffer, procfs_buffer_size);
		ret = procfs_buffer_size;
	}

	return ret;
}

/**
 *  This function is called when the /proc file is written
 */
int procfile_write(struct file *file, const char *buffer, unsigned long count,
					void *data)
{
	//char *data_copy = data;
	/* Get buffer size */
	procfs_buffer_size = count;
	if (procfs_buffer_size > PROCFS_MAX_SIZE) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	//printk(KERN_INFO ">>>>>>>>RAGHU>>>>=%s=>>=%lu=>>%s=\n", buffer, count, data_copy);
	/* Write data to the buffer */
	if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size)) {
		return -EFAULT;
	}

	return procfs_buffer_size;
}

/**
 *  This function is called when the module is loaded
 */

int init_module()
{
	/* create the /proc file */
	Our_Proc_File = create_proc_entry(PROCFS_NAME, 0644, NULL);

	if (Our_Proc_File == NULL) {
		remove_proc_entry(PROCFS_NAME, NULL);
		printk(KERN_INFO "Error: Could not initialize /proc/%s\n", PROCFS_NAME);
		return -ENOMEM;
	}

	Our_Proc_File->read_proc	= procfile_read;
	Our_Proc_File->write_proc	= procfile_write;
	Our_Proc_File->mode 	 	= S_IFREG | S_IRUGO;
	Our_Proc_File->uid 	 		= 0;
	Our_Proc_File->gid 	 		= 0;
	Our_Proc_File->size 	 	= 37;

	printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);
	return 0;
}

/**
 *This function is called when the module is unloaded
 *
 */
void cleanup_module()
{
	remove_proc_entry(PROCFS_NAME, NULL);
	printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}

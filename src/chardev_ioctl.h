/**
 * chardev_ioctl.h
 *
 * The declaration have to in a header file, because
 * they need to be known to both kernel module (chardev_ioctl.c)
 * and the process calling the ioctl (ioctl.c)
 */

#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

/**
 * The major device number. We can't rely on dynamic
 * registration any more, because ioctls need to know it.
 */
#define MAJOR_NUM 100

/**
 * SET the message of the device driver
 */
#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)
/**
 * _IOR means that we're creating an ioctl command
 * number for passing information from a user process
 * to the kernel module.
 *
 * The first argument MAJOR_NUM, is the major device
 * number that we are using
 *
 * The second number is the number of the command (command number)
 * (there could be several command numbers with different meanings).
 *
 * The third argument is the type we want to get from
 * the process to the kernel.
 */

/**
 * Get the message of the device driver
 */
#define IOCTL_GET_MSG _IOW(MAJOR_NUM, 1, char *)
/**
 * This IOCTL is used for output, to get the message
 * of the device driver. However, we still need the
 * buffer to place the message in to be input,
 * as it is allcated by the process.
 */

/**
 * Get the n'th byte of the message
 */
#define IOCTL_GET_NTH_BYTE _IOWR(MAJOR_NUM, 2, int)
/**
 * The IOCTL is used for both input and output. It
 * receives from the user a number, n, and returns
 * Message[n]
 */

/**
 * THe name of the device file
 */
#define DEVICE_FILE_NAME "char_dev_ioctl"

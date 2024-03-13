#ifndef _API_H
#define _API_H

#include "def.h"

int sa_register(struct device *dev, const char *path, int type, int flags, struct device_ops *ops, struct driver_ops *drv);
int sa_open(const char *path, int flags);
int sa_close(int desc);
ssize_t sa_read(int desc, void *buf, size_t count);
ssize_t sa_write(int desc, const void *buf, size_t count);
int sa_ioctl(int desc, int cmd, void *args);
int sa_isr(struct device *dev, int event, void *args);



#endif // !_API_H
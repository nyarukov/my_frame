#include "..\include\def.h"

const char *find_str(const char *str)
{
    const char *next_path = strchr(str, '/');
    if (next_path != NULL)
    {
        str += (int)(next_path - str) + 1;
        return find_str(str);
    }
    return str;
}


int sa_register(struct device *dev,
                const char *path,
                enum devuce_type type,
                int flags,
                struct device_ops *device_ops,
                struct driver_ops *driver_ops)
{
    const char *cur_path = find_str(path);
    memset(dev->name, 0, SA_NAME_MAX);
    dev->type = type;
    dev->flags = flags;
    dev->device_ops = device_ops;
    dev->driver_ops = driver_ops;
    
    return dev_register(dev, path);
    return 0;
}
int sa_open(const char *path, int flags)
{
}
int sa_close(int desc)
{
}
ssize_t sa_read(int desc, void *buf, size_t count)
{
}
ssize_t sa_write(int desc, const void *buf, size_t count)
{
}
int sa_ioctl(int desc, int cmd, void *args)
{
}
int sa_isr(struct device *dev, int event, void *args)
{
}

// 测试函数

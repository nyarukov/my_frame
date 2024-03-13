#include "..\include\api.h"

struct pin_device
{
    struct device dev;
    uint32_t pins[32];
};

struct pin_device_ops
{
    int (*open)(struct pin_device *dev);
    int (*close)(struct pin_device *dev);
    int (*read)(struct pin_device *pin, int number, uint8_t *value);
    int (*write)(struct pin_device *pin, int number, uint8_t value);
    int (*ioctl)(struct pin_device *pin, int cmd, void *arg);
    int (*irq)(struct pin_device *dev, int event, void *arg);
};

int sa_pin_register(struct pin_device *pin, const char *path, struct driver_ops *drv);
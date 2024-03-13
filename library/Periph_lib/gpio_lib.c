#include "gpio_lib.h"

static int sa_pin_open(struct device *dev){
    struct pin_device *pin=(struct pin_device *)dev;
    struct pin_device_ops *ops=(struct pin_device_ops *)dev->device_ops;
    ops->open(pin);
    return 0;
}
static int sa_pin_close(struct device *dev){
    struct pin_device *pin = (struct pin_device *)dev;
    struct pin_device_ops *ops =(struct pin_device_ops *)dev->device_ops;
    ops->close(pin);
    return 0;
}

static ssize_t sa_pin_read(struct pin_device *dev, void *buf, size_t count)
{
    struct pin_device *pin = (struct pin_device *)dev;
    struct pin_device_ops *ops = (struct pin_device_ops *)dev->dev.device_ops; 
    uint8_t *rd_buf = (uint8_t *)buf;
    ssize_t rd_size;


    for (rd_size = 0; rd_size < count; rd_size += sizeof(*rd_buf)) {
        int ret = (uint8_t)ops->read(pin, 0, rd_buf);
        if (ret < 0) {
            return (rd_size == 0) ? ret : rd_size;
        }
        rd_buf++;
    }
    return rd_size;
}

static ssize_t sa_pin_write(struct pin_device *dev, const void *buf, size_t count)
{
    struct pin_device *pin = (struct pin_device *)dev;
    struct pin_device_ops *ops = (struct pin_device_ops *)dev->dev.device_ops;
    uint8_t *wr_buf = (uint8_t *)buf;
    ssize_t wr_size;

    for (wr_size = 0; wr_size < count; wr_size += sizeof(*wr_buf)) {
        int ret = ops->write(pin,0, *wr_buf);
        if (ret < 0) {
            return (wr_size == 0) ? ret : wr_size;
        }
        wr_buf++;
    }
    return wr_size;
}

int sa_pin_register(struct pin_device *pin, const char *path, struct driver_ops *drv){
    static struct pin_device_ops ops = {sa_pin_open,
                                        sa_pin_close,
                                        sa_pin_read,
                                        sa_pin_write
                                        };
    sa_register(&pin->dev, path,DEV_TYPE_GPIO,DEV_FLAG_INIT,&ops,drv); 
}
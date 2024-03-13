#include "borad_gpio.h"

static struct pin_device pin_dev;

int pin_open(struct pin_device *dev){
    printf("Testing pin_open\n");
    return 0;
}
int pin_close(struct pin_device *dev){
    printf("Testing pin_close\n");
    return 0;
}
int pin_read(struct pin_device *dev,int number, uint8_t *value){
    printf("Testing pin_read\n");
    return 0;
}
int pin_write(struct pin_device *dev,int number, uint8_t *value){
    printf("Testing pin_write\n");
    return 0;
}
int pin_ioctl(struct pin_device *dev, int cmd, void *arg){
    printf("Testing pin_ioctl\n");
    return 0;
}
int pin_irq(struct pin_device *dev, int event, void *args){
    printf("Testing pin_isr\n");
    return 0;
}

struct device_ops pin_device_ops={
    pin_open,
    pin_close,
    pin_read,
    pin_write,
    pin_ioctl,
    pin_irq
};
struct driver_ops pin_driver_ops = {
    &pin_device_ops,
    NULL
};

void gpio_init(struct device *dev){
    sa_pin_register(&pin_dev,"pin1",&pin_driver_ops);
}


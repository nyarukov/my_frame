#ifndef _BORAD_GPIO_H
#define _BORAD_GPIO_H

#include "..\..\library\Periph_lib\gpio_lib.h"


struct drv_pin_port_data
{
    //GPIO_TypeDef *port;
    uint16_t *port;
};

struct drv_pin_data
{
    uint32_t pin;
};



#endif // !_BORAD_GPIO_H
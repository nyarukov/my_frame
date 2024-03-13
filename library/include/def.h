#ifndef _DEF_H
#define _DEF_H

#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#define DEV_FLAG_INIT                       (0x00000001UL)      // 设备初始化
#define DEV_FLAG_READY                      (0x00000002UL)      // 设备就绪
#define DEV_FLAG_OPEN                       (0x00000004UL)      // 设备打开
#define DEV_FLAG_CLOSE                      (0x00000008UL)      // 设备关闭
#define DEV_FLAG_BUSY                       (0x00000010UL)      // 设备忙

#define DEV_STATUS_REGISTERED               (0x00000020UL)      // 设备已经注册
#define DEV_STATUS_INIT_COMPLETED           (0x00000040UL)      // 设备注册完成

#define DEV_FIND_FLAG_ERR                   (0x0000001UL)       // 查找失败
#define DEV_FIND_FLAG_OK                    (0x0000002UL)       // 查找成功



/****************************************************************************************************/
// 设备类型
enum devuce_type
{
    DEV_TYPE_ROOT,
    DEV_TYPE_GPIO,
    DEV_TYPE_I2C,
    DEV_TYPE_SPI,
    DEV_TYPE_UART,
    DEV_TYPE_PWM,
    DEV_TYPE_ADC,
    DEV_TYPE_MAX
};

// 设备链表
struct sa_list
{
    struct sa_list *next;
    struct sa_list *prev;
};

// 设备驱动程序
struct driver_ops
{
    void *ops;  // 操作
    void *data; // 数据
};

// 设备结构体
struct device
{
    const char name[SA_NAME_MAX];  // 设备名字
    enum devuce_type type;         // 设备类型
    uint32_t flags;                // 设备状态
    void *parent;                  // 父级指针
    struct sa_list *siblings;      // 同级设备列表
    struct sa_lsit *children;      // 子设备列表
    struct driver_ops *driver_ops; // 设备驱动程序
    struct device_ops *device_ops; // 设备操作
};

// 设备操作结构体
struct device_ops
{
    int (*open)(struct device *dev);                                     // 打开设备
    int (*close)(struct device *dev);                                    // 关闭设备
    ssize_t (*read)(struct device *dev, void *buf, size_t count);        // 读取数据
    ssize_t (*write)(struct device *dev, const void *buf, size_t count); // 写入数据
    long (*ioctl)(struct device *dev, int cmd, void *arg);               // 控制设备
    ssize_t (*isr)(struct device *dev, int event, void *args);           // 中断
};

extern struct device root;

// 根节点
struct device root = {
    .name = "root",
    .type = DEV_TYPE_ROOT,
    .flags = DEV_FLAG_READY,
    .parent = NULL,
    .siblings = SA_list_init(root),
    .children = SA_list_init(root),
    .driver_ops = NULL,
    .device_ops = NULL};

#endif

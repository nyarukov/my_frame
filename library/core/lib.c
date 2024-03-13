#include "..\include\lib.h"

/**
 * @brief 计算字符串长度
 * 
 * @param _str 缓冲区
 * @return int 个数
 */
int str_len(char *_str)
{
	int len = 0;

	while (*_str++) len++;
	return len;
}

/**
 * @brief 复制字符串
 * 
 * @param _tar 目标缓冲区
 * @param _src 源缓冲区
 */
void str_cpy(char *_tar, char *_src)
{
	do
	{
		*_tar++ = *_src;
	}
	while (*_src++);
}

/**
 * @brief 字符串比较
 * 
 * @param _s1 字符串1
 * @param _s2 字符串2
 * @return int 0 表示相等 非0表示不等
 */
int str_cmp(char * _s1, char * _s2)
{
	while ((*_s1!=0) && (*_s2!=0) && (*_s1==*_s2))
	{
		_s1++;
		_s2++;
	}
	return *_s1 - *_s2;
}

/**
 * @brief 将内存块的内容设置为指定的值
 * 
 * @param _ptr 要设置的内存块的指针
 * @param _value 要设置的值
 * @param _len 要设置的字节数
 */
void mem_set(void *_ptr, int _value, int _len) {
    char *p = (char *)_ptr;
    while (_len--) {
        *p++ = (char)_value;
    }
}

/**
 * @brief 将一个内存块的内容复制到另一个内存块
 * 
 * @param _dest 目标内存块的指针
 * @param _src 源内存块的指针
 * @param _len 要复制的字节数
 */
void mem_cpy(void *_dest, const void *_src, int _len) {
    char *d = (char *)_dest;
    const char *s = (const char *)_src;

    while (_len--) {
        *d++ = *s++;
    }
}

/**
 * @brief CRC-8 校验函数
 * 
 * @param buf 缓冲区
 * @param len 长度
 * @return uint16_t 
 */
uint16_t Check_CRC8(uint8_t *buf, uint16_t len)
{
    uint8_t crc = 0;
    for (uint16_t i = 0; i < len; ++i)
    {
        crc ^= buf[i];
        for (uint8_t j = 0; j < 8; ++j)
        {
            if (crc & 0x01)
            {
                crc = (crc >> 1) ^ 0x8C;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

/**
 * @brief Modbus CRC-16 校验函数
 * 
 * @param data 缓冲区
 * @param length 长度
 * @return uint16_t 
 */
uint16_t Check_Modbus_CRC16(uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF; // 初始CRC值设为0xFFFF
    for (uint16_t i = 0; i < length; i++)
    {
        crc ^= data[i]; // 与当前字节进行XOR操作
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {                  // 如果最低位为1
                crc >>= 1;     // 右移一位
                crc ^= 0xA001; // 与多项式0xA001进行异或
            }
            else
            {
                crc >>= 1; // 右移一位
            }
        }
    }

    return crc;
}

/**
 * @brief Xmodem CRC-16 校验函数
 * 
 * @param buf 缓冲区
 * @param len 长度
 * @return uint16_t 
 */
uint16_t Check_Xmodeme_CRC16(uint8_t *buf, uint16_t len)
{
    uint16_t crc = 0;
    for (uint16_t i = 0; i < len; ++i)
    {
        crc ^= ((uint16_t)buf[i] << 8);
        for (uint8_t j = 0; j < 8; ++j)
        {
            if (crc & 0x8000)
            {
                crc = (crc << 1) ^ 0x1021;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

/**
 * @brief Ymodem CRC-16 校验函数
 * 
 * @param buf 缓冲区
 * @param len 长度
 * @return uint16_t 
 */
uint16_t Check_Ymodeme_CRC16(uint8_t *buf, uint16_t len)
{
    uint16_t crc = 0;
    for (uint16_t i = 0; i < len; ++i)
    {
        crc ^= (uint16_t)buf[i] << 8;
        for (uint8_t j = 0; j < 8; ++j)
        {
            if (crc & 0x8000)
            {
                crc = (crc << 1) ^ 0x8408;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}
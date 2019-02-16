#ifndef _REG_OFFSET_H_
#define _REG_OFFSET_H_

enum
{
    GPIO_ATL_0  =   0x0,
    GPIO_ATL_1  =   0x1,
    GPIO_ATL_2  =   0x2,
    GPIO_ATL_3  =   0x3,
    GPIO_ATL_4  =   0x4,
    GPIO_ATL_5  =   0x5
};

#define     DEVICE_BASE             0x3F000000

/*********************************
 * GPIO Control Register Offset
*********************************/
#define     GPIO_DEVICE_OFFSET      0x200000
#define     GPIO_SEL_OFFSET         0x0
#define     GPIO_SET_OFFSET         0x1C
#define     GPIO_CLR_OFFSET         0x28


#define     GPIO_DEVICE_BASE        (DEVICE_BASE + GPIO_DEVICE_OFFSET)
#define     GPFSELx(g)              (GPIO_DEVICE_BASE + (((g) + GPIO_SEL_OFFSET) << 2))
#define     GPSETx(g)               (GPIO_DEVICE_BASE + (((g) + GPIO_SET_OFFSET) << 2))                
#define     GPCLRx(g)               (GPIO_DEVICE_BASE + (((g) + GPIO_CLR_OFFSET) << 2))  

#endif
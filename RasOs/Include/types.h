#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned char  uint8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;

typedef unsigned char  bool;

#define NULL                0
#define True                1
#define False               0

enum RETURN_STATUS
{
    RETURN_SUCCESS = 0x0,
    RETURN_FAILED  = 0x1
};

#endif
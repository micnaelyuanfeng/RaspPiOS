#ifndef _UART_H_
#define _UART_H_

typedef bool (*_uart_init)(void);
typedef bool (*_uart_send)(uint8 character);
typedef bool (*_uart_receive)(uint8* character);
typedef bool (*_uart_send_string)(void);

typedef struct _uart_rts
{
    _uart_init          uart_init;
    _uart_send          uart_send_character;
    _uart_receive       uart_receive_character;
    _uart_send_string   uart_send_string;
}uart_rts_call_backs;

struct device_uart
{
    uart_rts_call_backs uart_rts;
};

bool uart_device_init(void);

#endif
#if !defined  (_COM_H)
#define _COM_H
#include "..\app\includes.h"
void sendchar (int ch);

void myprintf(char *buf);

void USART1_InitConfig(uint32_t BaudRate);

#endif


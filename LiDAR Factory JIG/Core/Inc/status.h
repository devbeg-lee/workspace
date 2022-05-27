#ifndef __STATUS_H__
#define __STATUS_H__

#include "main.h"
#include "string.h"
#include "usart.h"
#include "protocol.h"
#include "switch.h"
#include "adc.h"

extern uint8_t connect;
extern uint8_t VIEWER_RX_BUFF[9];

void Info_status(void);
void Detect1_status(void);
void Detect2_status(void);
void Detect3_status(void);
void Idle_status(void);
void Mode_status(void);
void Test_status(void);
void Result_status(void);

#endif
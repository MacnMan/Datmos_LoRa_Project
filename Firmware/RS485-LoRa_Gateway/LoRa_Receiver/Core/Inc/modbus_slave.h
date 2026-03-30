#ifndef MODBUS_SLAVE_H
#define MODBUS_SLAVE_H

#include "main.h"

// Your Modbus Slave ID configuration
#define SLAVE_ID  1

// Since 20 bytes = 10 Registers (16-bit each)
#define NUM_HOLDING_REGISTERS 10

extern uint16_t Modbus_Holding_Registers[NUM_HOLDING_REGISTERS];

// Function prototypes
uint16_t Calculate_CRC(uint8_t *buf, uint16_t len);
void Process_Modbus_Request(uint8_t *rx_buf, uint16_t rx_len, UART_HandleTypeDef *huart);
void Send_Modbus_Response(uint8_t *tx_buf, uint16_t tx_len, UART_HandleTypeDef *huart);

#endif


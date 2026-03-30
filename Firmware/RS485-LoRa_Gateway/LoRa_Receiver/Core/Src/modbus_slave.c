#include "modbus_slave.h"

// The array that holds your 20 bytes of LoRa data (10 x 16-bit registers)
uint16_t Modbus_Holding_Registers[NUM_HOLDING_REGISTERS] = {0};

// Standard Modbus CRC16 Calculation
uint16_t Calculate_CRC(uint8_t *buf, uint16_t len) {
    uint16_t crc = 0xFFFF;
    for (uint16_t pos = 0; pos < len; pos++) {
        crc ^= (uint16_t)buf[pos];
        for (int i = 8; i != 0; i--) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// Actually Transmits the data and toggles the MAX3485 DIR pin (PA0)
void Send_Modbus_Response(uint8_t *tx_buf, uint16_t tx_len, UART_HandleTypeDef *huart) {
    // 1. Set DE/RE High (Transmit Mode)
    HAL_GPIO_WritePin(GPIOA, RS485_DIR_Pin, GPIO_PIN_SET);

    // 2. Send the data
    HAL_UART_Transmit(huart, tx_buf, tx_len, 100);

    // 3. Set DE/RE Low (Receive Mode)
    HAL_GPIO_WritePin(RS485_DIR_GPIO_Port, RS485_DIR_Pin, GPIO_PIN_RESET);
}

// Parses the incoming Modbus frame
void Process_Modbus_Request(uint8_t *rx_buf, uint16_t rx_len, UART_HandleTypeDef *huart) {
    // Check if the frame is long enough and addressed to us
    if (rx_len < 8 || rx_buf[0] != SLAVE_ID) return;

    // Verify CRC
    uint16_t received_crc = (rx_buf[rx_len - 1] << 8) | rx_buf[rx_len - 2];
    uint16_t calculated_crc = Calculate_CRC(rx_buf, rx_len - 2);
    if (received_crc != calculated_crc) return;

    // Check Function Code (0x03 is Read Holding Registers)
    if (rx_buf[1] == 0x03) {
        uint16_t start_addr = (rx_buf[2] << 8) | rx_buf[3];
        uint16_t num_regs  = (rx_buf[4] << 8) | rx_buf[5];

        // Ensure master is not requesting more registers than we have
        if ((start_addr + num_regs) <= NUM_HOLDING_REGISTERS) {
            uint8_t response[256];
            response[0] = SLAVE_ID;
            response[1] = 0x03;
            response[2] = num_regs * 2; // Byte count

            // Fill response with your LoRa data mapped to registers
            int idx = 3;
            for (int i = 0; i < num_regs; i++) {
                response[idx++] = (Modbus_Holding_Registers[start_addr + i] >> 8) & 0xFF; // High Byte
                response[idx++] = Modbus_Holding_Registers[start_addr + i] & 0xFF;        // Low Byte
            }

            // Calculate and append CRC to response
            uint16_t tx_crc = Calculate_CRC(response, idx);
            response[idx++] = tx_crc & 0xFF;
            response[idx++] = (tx_crc >> 8) & 0xFF;

            // Send Response back to Master
            Send_Modbus_Response(response, idx, huart);
        }
    }
}

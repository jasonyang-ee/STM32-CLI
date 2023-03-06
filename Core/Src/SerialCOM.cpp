#include "SerialCOM.hpp"

#include "stdio.h"
#include "string.h"

SerialCOM::SerialCOM() {}

SerialCOM::~SerialCOM() {}

void SerialCOM::setPort(UART_HandleTypeDef *port) { m_port = port; }

bool SerialCOM::isTxComplete() { return tx_complete; }

void SerialCOM::setTxComplete() { tx_complete = true; }

void SerialCOM::send() {
    int size{};
    uint8_t *location_ptr;

    location_ptr = (uint8_t *)strchr((char *)m_tx_data, '\0');
    size = location_ptr - m_tx_data;

    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, m_tx_data, size);
}

void SerialCOM::send(uint8_t value) {
    int size{};
    uint8_t msg[BUFFER_SIZE]{};
    uint8_t *location_ptr;

    sprintf((char *)msg, "%d", (int)value);
    location_ptr = (uint8_t *)strchr((char *)msg, '\0');
    size = location_ptr - msg;

    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, msg, size);
}

void SerialCOM::send(uint16_t value) {
    int size{};
    uint8_t msg[BUFFER_SIZE]{};
    uint8_t *location_ptr;

    sprintf((char *)msg, "%d", (int)value);
    location_ptr = (uint8_t *)strchr((char *)msg, '\0');
    size = location_ptr - msg;

    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, msg, size);
}

void SerialCOM::send(uint32_t value) {
    int size{};
    uint8_t msg[BUFFER_SIZE]{};
    uint8_t *location_ptr;

    sprintf((char *)msg, "%d", (int)value);
    location_ptr = (uint8_t *)strchr((char *)msg, '\0');
    size = location_ptr - msg;

    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, msg, size);
}

void SerialCOM::send(int value) {
    int size{};
    uint8_t msg[BUFFER_SIZE]{};
    uint8_t *location_ptr;

    sprintf((char *)msg, "%d", value);
    location_ptr = (uint8_t *)strchr((char *)msg, '\0');
    size = location_ptr - msg;

    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, msg, size);
}
void SerialCOM::send(float value) {
    int size{};
    uint8_t msg[BUFFER_SIZE]{};
    uint8_t *location_ptr;

    sprintf((char *)msg, "%f", value);
    location_ptr = (uint8_t *)strchr((char *)msg, '\0');
    size = location_ptr - msg;

    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, msg, size);
}

void SerialCOM::send(double value) {
    int size{};
    uint8_t msg[BUFFER_SIZE]{};
    uint8_t *location_ptr;

    sprintf((char *)msg, "%f", value);
    location_ptr = (uint8_t *)strchr((char *)msg, '\0');
    size = location_ptr - msg;

    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, msg, size);
}

void SerialCOM::send(uint8_t *data) {
    size_t output_size{};
    size_t src_size{};
    uint8_t *src_loc_ptr;
    uint8_t *output_loc_ptr;

    src_loc_ptr = (uint8_t *)strchr((char *)data, '\0');
    src_size = src_loc_ptr - data;

    memset(m_tx_data, 0, sizeof m_tx_data);
    memcpy(m_tx_data, data, src_size);

    output_loc_ptr = (uint8_t *)strchr((char *)m_tx_data, '\0');
    output_size = output_loc_ptr - m_tx_data;

    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, m_tx_data, output_size);
}

void SerialCOM::send(const char *data) {
    size_t output_size{};
    size_t src_size{};
    char *src_loc_ptr;
    uint8_t *output_loc_ptr;

    src_loc_ptr = strchr((char *)data, '\0');
    src_size = src_loc_ptr - data;

    memset(m_tx_data, 0, sizeof m_tx_data);
    memcpy(m_tx_data, data, src_size);

    output_loc_ptr = (uint8_t *)strchr((char *)m_tx_data, '\0');
    output_size = output_loc_ptr - m_tx_data;

    // while (!tx_complete)
    //     ;
    // tx_complete = false;
    HAL_UART_Transmit_IT(m_port, m_tx_data, output_size);
}

void SerialCOM::send_ln() {
    while (!tx_complete)
        ;
    tx_complete = false;
    HAL_UART_Transmit_IT(m_port, (uint8_t *)"\n", 1);
}
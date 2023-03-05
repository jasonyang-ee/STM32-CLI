#ifndef CORE_INC_SERIALCOM
#define CORE_INC_SERIALCOM

#include "main.h"

class SerialCOM {
   public:
    SerialCOM();
    virtual ~SerialCOM();

    void setPort(UART_HandleTypeDef *);
	bool isTxComplete();
	void setTxComplete();

	void send();
    void send(uint8_t);
    void send(uint16_t);
    void send(uint32_t);
    void send(int);
    void send(float);
    void send(double);
	void send(uint8_t *);
    void send(const char*);

	void send_ln();

    // Buffer
    uint8_t m_tx_data[BUFFER_SIZE];	//BUFFER_SIZE defined in main.h
    uint8_t m_rx_data[BUFFER_SIZE];

   private:
    // Port
    UART_HandleTypeDef *m_port;
	bool tx_complete{true};
};


#endif    /* CORE_INC_SERIALCOM */

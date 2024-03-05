#ifndef __LING_SERIAL_H__
#define __LING_SERIAL_H__

#include <ling.defs.h>

#define LING_UART uart0
#define LING_UART_BAUD 115200

static inline void uart_puti(uart_inst_t *uart, int data) {
	char buff[20];
	snprintf(buff, 20, "%d", data);
	uart_puts(uart, buff);
}

#ifdef __cplusplus

class ling_serial_c {
private:
	uart_inst_t *_serial_uart_inst;
public:
	constexpr ling_serial_c(uart_inst_t* UART): _serial_uart_inst(UART) {};

	void init(uart_inst_t* UART) {
		_serial_uart_inst = UART;
	}

	ling_serial_c& operator<<(const char* data) {
		uart_puts(_serial_uart_inst, data);
		return *this;
	}

	ling_serial_c& operator<<(int data) {
		char buff[20];
		snprintf(buff, 20, "%d", data);
		uart_puts(_serial_uart_inst, buff);
		return *this;
	}
};


#endif // __cplusplus

#endif // __LING_SERIAL_H__

#include "main.h"
/*
 * This is the initialization of the UART device
 * for the usual parameters for a communication over a serial line.
 */
void serial_init(uint16_t port) {

  mmio_store(port+1,0x00);    // Disable all interrupts
  mmio_store(port+3,0x80);    // Enable DLAB (set baud rate divisor)

  mmio_store(port+0,0x01);    // Set divisor to 1 (lo byte) 115200 baud
  mmio_store(port+1,0x00);    //                0 (hi byte)

  mmio_store(port+3,0x03);    // 8 bits, no parity, one stop bit
}

/*
 * Receives one character from the serial line.
 * Nota Bene: 
 *   this function will block until there is a character available.
 */
char serial_receive(uint16_t port) {
	while ((mmio_load(port + 5) & 1) == 0);
   return mmio_load(port);
}

/*
 * Sends one character to the serial line.
 * Nota Bene: 
 *   this function will block until there is room to send a character available.
 */
void serial_send(uint16_t port, char c) {
  while ((mmio_load(port + 5) & 0x20) == 0);
  mmio_store(port,c);
}

/*
 * Sends a null-terminated string to the serial line.
 * Nota Bene: 
 *   this function will block until the entire string has been sent.
 */
void serial_send_string(uint16_t port, const unsigned char *s) {
  while(*s != '\0') {
    serial_send(port,*s);
    s++;
  }
}


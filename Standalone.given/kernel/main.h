

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

/*
 * GCC builtin support for variable number of arguments
 * passed to C function.
 */
#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_arg __builtin_va_arg
#define va_end __builtin_va_end

/*
 * Load from a memory-mapped input-output hardware register (mmio register), 
 * called a port in the i386 world. Notice the i386 processor
 * uses a special assembly instruction for reading values from mmio registers.
 */
__inline __attribute__((always_inline, no_instrument_function))
uint8_t mmio_load(uint16_t port) {
  uint8_t data;
  __asm __volatile("inb %w1,%0" : "=a" (data) : "d" (port));
  return data;
}

/*
 * Store a value to a memory-mapped input-output hardware register (mmio register), 
 * called a port in the i386 world. Notice the i386 processor
 * uses a special assembly instruction for writing values to mmio registers.
 */
__inline __attribute__((always_inline, no_instrument_function))
void mmio_store(uint16_t port, uint8_t data) {
  __asm __volatile("outb %0,%w1" : : "a" (data), "d" (port));
}

/*
 * The ports for the first two serial lines, 
 * called COM1 and COM2 in the i386 world.
 */
#define COM1 ((uint16_t)0x3f8)
#define COM2 ((uint16_t)0x2f8)

/*
 * Definitions for the functions related to the serial lines.
 */
void serial_init(uint16_t port);

void serial_send(uint16_t port, char c);

void serial_send_string(uint16_t port, const unsigned char *s);

char serial_receive(uint16_t port);

/*
 * Definitions for the functions related to the video device,
 * i.e. the screen.
 */
void video_write_string(int color, const char *string);
void video_write(int color, const char c);

/*
 * Definitions for the functions related to printing.
 *
 * The function kputchar is expected to print the given character 
 * somewhere. this function is called indirectly from kprintf
 * to print each character.
 *
 * The function kprintf works like the regular function printf, 
 * with a first argument that is a format string, followed
 * by a variable number of arguments, possibly none. 
 */
void kputchar(char c);

void kprintf(const char *fmt, ...);

int kvprintf(char const *fmt, void (*func)(char), int radix, va_list ap);

void clearScreen();

void printf(const char *fmt, ...);

void moveLeft();

void moveRight();

void moveUp();

void moveDown();

void moveCursor();

void delete();

void backspace();

void shiftRight();
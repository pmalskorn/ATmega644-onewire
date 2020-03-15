#include <inttypes.h>

#ifndef ONEWIRE_H_
#define ONEWIRE_H_
typedef struct onewire_t
{
	// bit = pin of port
	uint8_t bit;
	uint8_t *ddr;
	uint8_t *port;
	uint8_t *pin;
} onewire_t;

enum timmings
{
	A = 6,
	B = 64,
	C = 60,
	D = 10,
	E = 9,
	F = 55,
	G = 0,
	H = 500,
	I = 70,
	J = 410
};

void set_gpio_input(onewire_t *ow);
void set_gpio_output(onewire_t *ow);

void onewire_line_low(onewire_t *ow);
void onewire_line_release(onewire_t *ow);

uint8_t onewire_reset(onewire_t *ow);

uint8_t onewire_read_line(onewire_t *ow);
uint8_t onewire_read_bit(onewire_t *ow);
void onewire_write_bit(onewire_t *ow, uint8_t bit);
void onewire_write_byte(onewire_t *ow, uint8_t byte);
uint8_t onewire_read_byte(onewire_t *ow);


#endif /* ONEWIRE_H_ */
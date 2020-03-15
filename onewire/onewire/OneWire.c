#include <inttypes.h>
#include <util/delay.h>
#include "OneWire.h"

void set_gpio_input(onewire_t *ow)
{
	// set pin to input
	*(ow->ddr) &= ~(ow->bit);
	
	// set pull-up
	*(ow->port) |= (ow->bit);
}


void set_gpio_output(onewire_t *ow)
{
	// set pin to output
	*(ow->ddr) |= (ow->bit);
	
	// set output to zero / remove pull-up
	*(ow->port) &= ~(ow->bit);
}


void onewire_line_low(onewire_t *ow){
	set_gpio_output(ow);
}


void onewire_line_release(onewire_t *ow){
	set_gpio_input(ow);
}

uint8_t onewire_reset(onewire_t *ow)
{
	_delay_us(G);
	onewire_line_low(ow);
	_delay_us(H);
	onewire_line_release(ow); // no release because of the 2 pin config
	_delay_us(I);
	
	if (onewire_read_line(ow)){ // line should be pulled down by slave
		return 1;
	}
	
	_delay_us(J);
	
	if (!onewire_read_line(ow)){ // line should be "released" by slave
		return 2;
	}
	
	return 0;
}


uint8_t onewire_read_line(onewire_t *ow)
{
	return (*(ow->pin) & ow->bit) / ow->bit;
}


uint8_t onewire_read_bit(onewire_t *ow)
{
	uint8_t bit;
	onewire_line_low(ow);
	_delay_us(A);
	onewire_line_release(ow);
	_delay_us(E);
	bit = onewire_read_line(ow);
	_delay_us(F);
	return bit;
}


void onewire_write_bit(onewire_t *ow, uint8_t bit)
{
	onewire_line_low(ow);
	if (bit){
		_delay_us(A);
	}
	else{
		_delay_us(C);
	}
	
	onewire_line_release(ow);
	if (bit){
		_delay_us(B);
	}
	else{
		_delay_us(D);
	}
}


uint8_t onewire_read_byte(onewire_t *ow)
{
	uint8_t byte = 0;
	for (uint8_t i = 0; i < 8; i++)
	{
		byte >>= 1;
		if (onewire_read_bit(ow)){
			byte |= 0x80;
		}
	}
	return byte;
}


void onewire_write_byte(onewire_t *ow, uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		onewire_write_bit(ow, byte & 1);
		byte >>= 1;
	}
}


#pragma once
#include <stdint.h>

// Initialize LEDs
void init_leds();

// Set the color of an LED
void set_led(int index, uint8_t r, uint8_t g, uint8_t b);

// Send the cached color out (update all lights at once)
void show_leds();

// Clear all lights (set to black)
void clear_leds();

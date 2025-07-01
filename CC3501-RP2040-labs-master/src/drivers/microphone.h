#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <stdint.h>

// Initialize microphone (configure ADC)
void microphone_init();

// Read a certain number of ADC samples (each sample is uint16_t)
void microphone_read(uint16_t* buffer, uint32_t num_samples);

#endif // MICROPHONE_H

#pragma once

#include "hardware/i2c.h"
#include <stdint.h>
#define LIS3DH_I2C_ADDR 0x19  // LIS3DH I2C address (0x19 for SA0=0, 0x18 for SA0=1)
#define LIS3DH_WHO_AM_I_REG  0x0F
#define LIS3DH_WHO_AM_I_ID   0x33
void lis3dh_init(i2c_inst_t* i2c, uint sda_pin, uint scl_pin);

void lis3dh_read_raw_xyz(int16_t* x, int16_t* y, int16_t* z);

void write_register(uint8_t reg, uint8_t value);

float convert_raw_to_g(int16_t raw_value);

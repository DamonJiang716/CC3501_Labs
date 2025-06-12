#include "lis3dh.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h> 
static i2c_inst_t* i2c_port = nullptr;

void lis3dh_init(i2c_inst_t* i2c, uint sda_pin, uint scl_pin) {
    i2c_port = i2c;

    //  Set the I2C communication rate to 400kHz
    i2c_init(i2c_port, 400 * 1000);  // 400kHz = 400000
    
    //  Set the pin function to I2C mode
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);

    
    // Read the device ID to confirm whether the connection is successful
    uint8_t reg = 0x0F;
    uint8_t id = 0;
    i2c_write_blocking(i2c_port, LIS3DH_I2C_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c_port, LIS3DH_I2C_ADDR, &id, 1, false);

    if (id != 0x33) {
        printf(" ERROR: WHO_AM_I = 0x%02X (expected 0x33)\n", id);
    } else {
        printf(" LIS3DH detected, WHO_AM_I = 0x%02X\n", id);
    }

   
    // CTRL_REG1 (0x20): Data rate 100Hz, XYZ enabled → 0x57
    uint8_t ctrl1[2] = {0x20, 0x57};
    i2c_write_blocking(i2c_port, LIS3DH_I2C_ADDR, ctrl1, 2, false);

    // CTRL_REG4 (0x23): ±2g, High resolution mode → 0x88
    uint8_t ctrl4[2] = {0x23, 0x88};
    i2c_write_blocking(i2c_port, LIS3DH_I2C_ADDR, ctrl4, 2, false);

    printf("LIS3DH initialization complete\n");
}

void write_register(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    i2c_write_blocking(i2c_port, LIS3DH_I2C_ADDR, data, 2, false);
}

void lis3dh_read_raw_xyz(int16_t* x, int16_t* y, int16_t* z) {
    uint8_t start_addr = 0x28 | 0x80;  // Starting address + auto increment
    uint8_t buffer[6];  // Store 6 bytes of data：X_L, X_H, Y_L, Y_H, Z_L, Z_H

    
    i2c_write_blocking(i2c_port, LIS3DH_I2C_ADDR, &start_addr, 1, true);

    
    i2c_read_blocking(i2c_port, LIS3DH_I2C_ADDR, buffer, 6, false);

    // Combine the low and high bytes, and right shift by 4 to get the 12-bit value

    *x = (int16_t)((buffer[1] << 8) | buffer[0]) >> 4;
    *y = (int16_t)((buffer[3] << 8) | buffer[2]) >> 4;
    *z = (int16_t)((buffer[5] << 8) | buffer[4]) >> 4;
}


float convert_raw_to_g(int16_t raw_value) {
    // Sensitivity in ±2g mode is 0.001 g/LSB
    return raw_value * 0.001f;
}

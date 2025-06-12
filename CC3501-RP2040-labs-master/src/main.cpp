#include "lis3dh.h"
#include "tasks/accelerometer.h"
#include "pico/stdlib.h"
#include "board.h"
int main() {
    stdio_init_all();
    sleep_ms(1000);  // Delay waiting for serial port to be ready
    lis3dh_init(i2c0,I2C_SDA_PIN, I2C_SCL_PIN);  // SDA/SCL
    run_accelerometer_task();  
    return 0;
}

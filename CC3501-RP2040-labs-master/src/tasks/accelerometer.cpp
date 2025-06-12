#include "accelerometer.h"
#include "lis3dh.h"
#include "leds.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "board.h" 

int map_to_led_index(float g) {
    int i = (int)((g + 1.0f) * (NUM_LEDS - 1) / 2.0f);
    if (i < 0) i = 0;
    if (i >= NUM_LEDS) i = NUM_LEDS - 1;
    return i;
}

void run_accelerometer_task() {
    init_leds();

    while (true) {
        int16_t raw_x, raw_y, raw_z;
        lis3dh_read_raw_xyz(&raw_x, &raw_y, &raw_z);

        float x_g = convert_raw_to_g(raw_x);
        float y_g = convert_raw_to_g(raw_y);
        float z_g = convert_raw_to_g(raw_z);

        printf("X=%.3f g  Y=%.3f g  Z=%.3f g\n", x_g, y_g, z_g);

        // Controlling LEDs with Y-axis acceleration
        int led_index = map_to_led_index(y_g);

        clear_leds();
        set_led(led_index, 0, 255, 0);  
        show_leds();

        sleep_ms(100);  
    }
}

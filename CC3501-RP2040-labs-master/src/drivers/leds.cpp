#include "leds.h"
#include "hardware/pio.h"
#include "WS2812.pio.h"  // FOR WS2812
#include "board.h"
#include "pico/stdlib.h"


// Save the color of each light（GRB）
static uint32_t led_data[NUM_LEDS];

// PIO related variables
static PIO pio = pio0;
static uint sm = 0;

void init_leds() {
    // Load the WS2812 program into PIO and initialize the state machine
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, LED_PIN, 800000, false);

    // Initialize and clear the lights
    clear_leds();
    show_leds();
}

void set_led(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < 0 || index >= NUM_LEDS) return;

    led_data[index] = (g << 24) | (r << 16) | (b << 8);
}

void show_leds() {
    // Send the colors of all lights in the cache to PIO in sequence
    for (int i = 0; i < NUM_LEDS; ++i) {
        pio_sm_put_blocking(pio, sm, led_data[i]);
    }
    sleep_us(300);

}

void clear_leds() {
    for (int i = 0; i < NUM_LEDS; ++i) {
        led_data[i] = 0;
    }
}

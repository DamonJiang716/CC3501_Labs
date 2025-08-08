#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "microphone.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "board.h"
void microphone_init() {
    adc_init(); // Initialize ADC module
    adc_gpio_init(MIC_ADC_PIN); // ADC0 → GPIO26 → Microphone analog output
    adc_select_input(ADC_INPUT); // Select channel 0 (connect microphone)
    
    // Set sampling frequency to 44.1kHz:
    // clkdiv = (48e6 / 44100) - 1 ≈ 1087.43
    adc_set_clkdiv(1087); // Use floating point number to set frequency division ratio
    
    // Enable FIFO to support continuous sampling
    adc_fifo_setup(
    true, // Enable FIFO
    false, //Needn't use DMA
    0, // Need not use threshold
    false, // Do not include error flag in FIFO data
    false // Do not shift data
    );
    }
    
    void microphone_read(uint16_t* buffer, uint32_t num_samples) {
    adc_run(true); // Start free-running sampling mode
    
    for (uint32_t i = 0; i < num_samples; ++i) {
    buffer[i] = adc_fifo_get_blocking(); // Wait and read samples
    }
    
    adc_run(false); // Stop sampling
    
   // Clear FIFO to avoid mixing old samples later
   adc_fifo_drain();
    }

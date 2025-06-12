#pragma once

// Accelerometer tasks: read value, display on LED, print out
void run_accelerometer_task();

int map_to_led_index(float g);
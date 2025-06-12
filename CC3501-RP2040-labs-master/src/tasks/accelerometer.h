#pragma once

// 加速度计任务：读取值、显示在LED上、打印出来
void run_accelerometer_task();

int map_to_led_index(float g);
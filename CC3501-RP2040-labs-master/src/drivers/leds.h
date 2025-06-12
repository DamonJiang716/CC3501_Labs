#pragma once
#include <stdint.h>

// 初始化 LED（加载 PIO 程序等）
void init_leds();

// 设置某个 LED 的颜色（缓存，未立即发送）
void set_led(int index, uint8_t r, uint8_t g, uint8_t b);

// 把缓存中的颜色发送出去（一次性更新所有灯）
void show_leds();

// 清除所有灯（设置为黑色）
void clear_leds();

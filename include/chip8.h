#ifndef _CHIP8_H
#define _CHIP8_H

#include "config.h"
#include "chip8memory.h"
#include "chip8registers.h"
#include "chip8stack.h"
#include "chip8keyboard.h"
#include "chip8screen.h"
#include <stddef.h>

struct chip8
{
    struct chip8_memory memory;
    struct chip8_stack stack;
    struct chip8_registers registers;
    struct chip8_keyboard keyboard;
    struct chip8_screen screen;
};

void chip8_init(struct chip8* chip8);
void chip8_deinit(struct chip8 *chip8);

void chip8_load(struct chip8* chip8, const char* buf, size_t size);
void chip8_exec(struct chip8* chip8, unsigned short opcode);
void chip8_beep(struct chip8 *chip8, int duration_ms, int freq);
void chip8_sleep(struct chip8 *chip8, int del);

#endif


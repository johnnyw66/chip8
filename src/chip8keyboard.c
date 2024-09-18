#include "chip8keyboard.h"
#include <assert.h>

static void chip8_keyboard_ensure_in_bounds(int key)
{
    assert(key >=0 && key < CHIP8_TOTAL_KEYS);
}
int chip8_keyboard_map(const char *bindings, char real_key)
{
    for (int i = 0 ; i < CHIP8_TOTAL_KEYS; i++)
    {
        if (bindings[i] == real_key)
        {
            return i;
        }
    }
    return -1 ;
}

void chip8_keyboard_down(struct chip8_keyboard *keyboard, int key)
{
    chip8_keyboard_ensure_in_bounds(key);
    keyboard->keyboard[key] = true ;
}
void chip8_keyboard_up(struct chip8_keyboard *keyboard, int key)
{
    chip8_keyboard_ensure_in_bounds(key);
    keyboard->keyboard[key] = false ;

}

bool chip8_keyboard_is_down(struct chip8_keyboard *keyboard, int key)
{
    chip8_keyboard_ensure_in_bounds(key);
    return keyboard->keyboard[key];
}



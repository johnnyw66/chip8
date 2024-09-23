#include "chip8screen.h"
#include <assert.h>
#include <memory.h>
#include <stdio.h>

static void chip8_screen_check_bounds(int x, int y)
{
    assert(x >= 0 && x < CHIP8_WIDTH && y >= 0 && y < CHIP8_HEIGHT);
}

static inline byte calc_bitmask(int x)
{
    byte bitmask = 1<<(7 - (x & 7));
    return bitmask;
}

static inline int pixel_offset(int x, int y)
{
    int offset = (y*(CHIP8_WIDTH>>3)) + (x>>3) ;
    return offset;
}

void chip8_screen_set(struct chip8_screen* screen, int x, int y)
{
    chip8_screen_check_bounds(x, y);
    int offset = pixel_offset(x, y);
    byte bitmask = calc_bitmask(x);
    screen->pixels[offset] |= bitmask;
 
}


void chip8_screen_clear(struct chip8_screen* screen)
{
    memset(screen->pixels, 0x0, CHIP8_HEIGHT*(CHIP8_WIDTH>>3));
}

bool chip8_screen_is_set(struct chip8_screen* screen, int x, int y)
{
    chip8_screen_check_bounds(x, y);
    int offset = pixel_offset(x, y);
    byte bitmask = calc_bitmask(x);
    return (screen->pixels[offset] & bitmask) != 0;
}

bool chip8_screen_draw_sprite(struct chip8_screen* screen, int x, int y, const char* sprite, int num)
{
    bool pixel_collison = false;

    for (int ly = 0; ly < num; ly++)
    {
        char c = sprite[ly];
        for (int lx = 0; lx < 8; lx++)
        {
            if ((c & (0b10000000 >> lx)) == 0)
                continue;

            int offset = pixel_offset(x + lx, y + ly);
            byte bitmask = calc_bitmask(x + lx) ;
            pixel_collison = screen->pixels[offset] & bitmask;        
            screen->pixels[offset] ^=bitmask;

        }
    }
    return pixel_collison;
}



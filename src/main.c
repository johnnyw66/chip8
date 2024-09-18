#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "chip8.h"
#include "chip8stack.h"
#include "chip8keyboard.h"


// Real Keys '0'-'9', 'a'-'f' mapped to chip8 keys 0 to 15
const char keyboard_bindings[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3,
    SDLK_4, SDLK_5, SDLK_6, SDLK_7,
    SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f
};
void test()
{
 struct chip8 chip8;
 chip8.registers.V[2] = 50 ;
 
 chip8_memory_set(&chip8.memory, 0x400, 'Z');
 printf("%c\n", chip8_memory_get(&chip8.memory, 0x400));
 printf("%d\n", chip8.registers.V[2]);

 chip8.registers.SP = 0;
 chip8_stack_push(&chip8, 0x100);

 //chip8_stack_push(&chip8, 0x200);
 //char bindings[3] = ['0','1','2'];


 unsigned short addr1 = chip8_stack_pop(&chip8);
 printf("1st Pop %x\n", addr1);
 unsigned short addr2 = chip8_stack_pop(&chip8);
 printf("2nd Pop %x\n", addr2);


 chip8_keyboard_down(&chip8.keyboard, 0x0f);
 bool is_down = chip8_keyboard_is_down(&chip8.keyboard, 0x0f);
 printf("IS DOWN %i\n", is_down);

 char chip8_key = chip8_keyboard_map(keyboard_bindings, 'M');
 printf("CHIP8 KEY for M is %d\n", chip8_key);

}

int main(int argc, char** argv)
{

 test() ;

 struct chip8 chip8;

 chip8_init(&chip8);

 if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
    EMULATOR_WINDOW_TITLE,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER,
    CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLIER, SDL_WINDOW_SHOWN
  );

 if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
  if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
  }

  SDL_Event event;
  int quit = 0;
  while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch(event.type) {

                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_KEYDOWN:
                    {
                        char key = event.key.keysym.sym ;
                        int virt_key = chip8_keyboard_map(keyboard_bindings, key);
                        if (virt_key != -1) {
                            printf("VIRT KEY IS DOWN %d\n", virt_key);
                            chip8_keyboard_down(&chip8.keyboard, virt_key);
                        }
                    }
                    break;

                case SDL_KEYUP:
                    {
                        char key = event.key.keysym.sym ;
                        int virt_key = chip8_keyboard_map(keyboard_bindings, key);
                        if (virt_key != -1) {
                            printf("VIRT KEY IS UP %d\n", virt_key);
                            chip8_keyboard_up(&chip8.keyboard, virt_key);
                        }
                    }
                    break;


            }
        }
        //printf("Render\n");
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = 40;
        r.h = 40;
        SDL_RenderDrawRect(renderer, &r);
        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

  return 0;
}



#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    printf("Starting parsing the image...\n");
    FILE *in = stdin;
    char *sizeImageString = calloc(1000, sizeof(char));
    fgets(sizeImageString, 1000, in);

    const int width = 900;
    const int height = 600;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Simple Window", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    Uint8 r, g, b;
    r = 0xFF;
    g = b = 0;

    Uint32 color = SDL_MapRGB(surface->format, r, g, b);

    // int x = 50;
    // int y = 50;
    // SDL_Rect rect = (SDL_Rect){x, y, 100, 100};
    // SDL_FillRect(surface, &rect, color);

    SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};
    for (int x = 0; x < width; x++) {
        pixel.x = x;
        for (int y = 0; y < height; y++) {
            pixel.y = y;
            SDL_FillRect(surface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    Uint32 start = SDL_GetTicks();

    // Loop de eventos por 3 segundos
    while (SDL_GetTicks() - start < 3000) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                goto quit;
        }
        SDL_Delay(16);
    }

quit:
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

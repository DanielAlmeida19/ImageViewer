#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    printf("Starting parsing the image...\n");
    FILE *in = stdin;
    char *throwAway = calloc(1000, sizeof(char));

    // Read the first line (specifier P3 or P6 - ignore here)
    fgets(throwAway, 1000, in);

    // Read the second line (comment)
    fgets(throwAway, 1000, in);

    // Read the third line (dimmensions: width and height)
    char *dimensions = calloc(1000, sizeof(char));
    fgets(dimensions, 1000, in);

    int width = -1;
    int height = -1;
    sscanf(dimensions, "%d %d\n", &width, &height);
    printf("width = %d; height = %d\n", width, height);
    free(dimensions);

    // Read the fourth line (maximum color value - ignore here)
    fgets(throwAway, 1000, in);
    free(throwAway);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};
    Uint32 color = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Uint8 r, g, b;
            r = (char)getchar();
            g = (char)getchar();
            b = (char)getchar();

            color = SDL_MapRGB(surface->format, r, g, b);
            pixel.x = x;
            pixel.y = y;

            SDL_FillRect(surface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(window);

    int appRunning = 1;
    while (appRunning) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                appRunning = 0;
        }
        SDL_Delay(100);
    }
}

#include <SDL3/SDL.h>
#include <iostream>
using namespace std;

#define WIDTH 900
#define HEIGHT 600

void FillCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    int x = radius, y = 0;
    int p = 1 - radius; // Decision parameter

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

    while (x >= y)
    {
        // Draw horizontal lines (scanlines) for better performance
        SDL_RenderLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
        SDL_RenderLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
        SDL_RenderLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
        SDL_RenderLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

        y++;
        if (p <= 0)
        {
            p += 2 * y + 1;
        }
        else
        {
            x--;
            p += 2 * (y - x) + 1;
        }
    }
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Ray Caster", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Clear screen (set background color)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Draw a red rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect rect = {100, 100, 200, 150};
    SDL_RenderFillRect(renderer, &rect);

    // Draw an optimized filled circle in white
    FillCircle(renderer, WIDTH / 2, HEIGHT / 2, 100);

    // Update the screen
    SDL_RenderPresent(renderer);

    SDL_Delay(3000); // Wait for 3 seconds

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TEXT_SIZE = 48;
const int TEXT_X = 200;
const int TEXT_Y = 250;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("I HATE YOU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Color text_color = { 255, 255, 255, 255 };
    SDL_Surface* text_surface = TTF_RenderText_Solid(TTF_OpenFont("arial.ttf", TEXT_SIZE), "I HATE YOU", text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    SDL_Rect text_rect = { TEXT_X, TEXT_Y, text_surface->w, text_surface->h };

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        SDL_RenderPresent(renderer);

        SDL_Rect window_rect;
        SDL_GetWindowPosition(window, &window_rect.x, &window_rect.y);
        window_rect.w = SCREEN_WIDTH;
        window_rect.h = SCREEN_HEIGHT;
        if (window_rect.x + window_rect.w >= SDL_GetDesktopDisplayMode(0)->w || window_rect.x <= 0) {
            window_rect.x = 0;
        } else {
            window_rect.x += rand() % 5 - 2;
        }
        if (window_rect.y + window_rect.h >= SDL_GetDesktopDisplayMode(0)->h || window_rect.y <= 0) {
            window_rect.y = 0;
        } else {
            window_rect.y += rand() % 5 - 2;
        }
        SDL_SetWindowPosition(window, window_rect.x, window_rect.y);

        SDL_Delay(10);
    }

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

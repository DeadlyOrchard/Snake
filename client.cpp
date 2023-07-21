#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include "Snake.hpp"
#include "Food.hpp"

int main(int argc, char *args[] ){
    const int SCREEN_WIDTH {1920}, SCREEN_HEIGHT {1080}, FRAME_RATE {100};

    // set up SDL systems
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    // game object dependencies
    const int BLOCK_SIZE{20}, SPEED{20}, LENGTH{1}, MIN_X{10}, MIN_Y{10};
    const int MAX_X{SCREEN_WIDTH - BLOCK_SIZE / 2}, MAX_Y{SCREEN_HEIGHT - BLOCK_SIZE * 10 - BLOCK_SIZE / 2};

    // game objects
    Snake snake {BLOCK_SIZE, SPEED, LENGTH, MIN_X, MIN_Y, MAX_X, MAX_Y, 1, 0};
    Food food {MIN_X, MIN_Y, MAX_X, MAX_Y, BLOCK_SIZE};

    // UI
    SDL_Rect GAME_BACKGROUND; // background of the actual gameplay
    GAME_BACKGROUND.w = MAX_X - MIN_X;
    GAME_BACKGROUND.h = MAX_Y - MIN_Y;
    GAME_BACKGROUND.x = MIN_X;
    GAME_BACKGROUND.y = MIN_Y;
    SDL_Rect scoreBlock;
    scoreBlock.w = BLOCK_SIZE;
    scoreBlock.h = BLOCK_SIZE;

    // game loop dependencies
    SDL_Event e;
    bool quit {false};

    // game loop
    while (!quit){
        // hardware event handling
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                quit = true; 
            }
            if (e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_RIGHT:
                        snake.SetVel(1, 0);
                        break;
                    case SDLK_LEFT:
                        snake.SetVel(-1, 0);
                        break;
                    case SDLK_UP:
                        snake.SetVel(0, -1);
                        break;
                    case SDLK_DOWN:
                        snake.SetVel(0, 1);
                        break;
                }
            }
        }
        // draw game background
        SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
        SDL_RenderFillRect(renderer, &GAME_BACKGROUND);

        // update screen here
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        snake.Update();
        snake.Draw(renderer);
        food.Draw(renderer);

        // display UI | use the same rect to draw multiple squares which resemble the player's total length
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        scoreBlock.x = MIN_X; // set inital starting place
        scoreBlock.y = MAX_Y;
        int chunk_x {MIN_X};
        for (int i{}; i < snake.GetLength(); i++){
            SDL_RenderDrawRect(renderer, &scoreBlock); // draw first, then move
            scoreBlock.x += BLOCK_SIZE; // move right

            if ((i + 1) % 5 == 0 && i != 0){
                scoreBlock.y += BLOCK_SIZE; // move down
                scoreBlock.x = chunk_x; // reset x to current chunk x
            }
            if (scoreBlock.y == MAX_Y + 5 * BLOCK_SIZE){
                chunk_x += BLOCK_SIZE * 6;
                scoreBlock.x = chunk_x;
                scoreBlock.y = MAX_Y;
            }
        }

        // display to player
        SDL_RenderPresent(renderer);

        // clear frame
        SDL_Delay(FRAME_RATE);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // game mechanic events
        if ((snake.GetX() == food.GetX()) && (snake.GetY() == food.GetY())){
            food.Eat();
            snake.Grow(1);
            
        }
    }
    return 0;
}
#include "Food.hpp"
#include <iostream>

Food::Food(int minX, int minY, int maxX, int maxY, int size)
{
    for (int i{minX}; i < maxX; i += size)
        xValues.push_back(i);

    for (int i{minY}; i < maxY; i += size)
        yValues.push_back(i);

    Block.w = size;
    Block.h = size;
    srand(time(0));
    Pos[0] = xValues[rand() % xValues.size()];
    srand(time(0));
    Pos[1] = yValues[rand() % yValues.size()];
}

int Food::GetX() {return Pos[0];}

int Food::GetY() {return Pos[1];}

void Food::Eat()
{
    srand(time(0));
    Pos[0] = xValues[rand() % xValues.size()];
    srand(time(0));
    Pos[1] = yValues[rand() % yValues.size()];
}

void Food::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    Block.x = Pos[0];
    Block.y = Pos[1];
    SDL_RenderDrawRect(renderer, &Block);
}
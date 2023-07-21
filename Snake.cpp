#include "Snake.hpp"
#include <iostream>
// initialize
Snake::Snake(int speed, int size, int length, int minX, int minY, int maxX, int maxY, int xVel, int yVel)
{
    HeadPos[0] = (maxX - minX) / 2;
    HeadPos[1] = (maxY - minY) / 2;
    Size = size;
    Block.w = size;
    Block.h = size;
    Length = length;
    Speed = speed;
    MinPos[0] = minX;
    MinPos[1] = minY;
    MaxPos[0] = maxX;
    MaxPos[1] = maxY;
    Vel[0] = xVel;
    Vel[1] = yVel;
    Alive = true;
}

int Snake::GetX() {return HeadPos[0];}

int Snake::GetY() {return HeadPos[1];}

int Snake::GetLength() {return Length;}

// update tail and head coordinates
void Snake::Update()
{
    if (Alive){
        xTail.insert(xTail.begin(), HeadPos[0]); // update tail x
        yTail.insert(yTail.begin(), HeadPos[1]); // update tail y
        if (xTail.size() == Length - 1){ // keep size of tail limited
            xTail.pop_back();
            yTail.pop_back();
        }

        if (HeadPos[0] >= MinPos[0] && HeadPos[0] <= MaxPos[0])
            HeadPos[0] += Speed * Vel[0];
        else
            Alive = false;
        if (HeadPos[1] >= MinPos[1] && HeadPos[1] <= MaxPos[1])
            HeadPos[1] += Speed * Vel[1];
        else
            Alive = false;
        
        for (int i{}; i < Length; i++){
            if (HeadPos[0] == xTail[i] && HeadPos[1] == yTail[i]){
                Alive = false;
            }
        }
    }
}

void Snake::Grow(int value = 1)
{
    Length+= value;
}

void Snake::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    Block.x = HeadPos[0];
    Block.y = HeadPos[1];
    SDL_RenderDrawRect(renderer, &Block);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i{}; i < Length; i++){
        Block.x = xTail[i];
        Block.y = yTail[i];
        SDL_RenderDrawRect(renderer, &Block);
    }
}

void Snake::SetVel(int xValue, int yValue)
{
    Vel[0] = xValue;
    Vel[1] = yValue;
}
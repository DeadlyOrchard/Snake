#include <vector>
#include <SDL2/SDL.h>

class Snake
{
    public:
        Snake(int size, int speed, int length, int minX, int minY, int maxX, int maxY, int xVel, int yVel);
        int GetX(); // returns the x position of the head of the snake
        int GetY(); // returns the y position of the head of the snake
        int GetLength();
        void Update(); // moves snake coordinates along it's current direction
        void Grow(int value); // increases length of snake
        void Draw(SDL_Renderer *renderer); // draws snake to renderer
        void SetVel(int xValue, int yValue); // client uses this to control direction of snake

    private:
        int HeadPos[2], Speed{}, Size{}, Length{}, MinPos[2], MaxPos[2], Vel[2];
        std::vector<int> xTail, yTail; // first position in, last position out
        SDL_Rect Block; // used to display to renderer
        bool Alive; // controls whether client is in-game or in-lobby
};
#include <SDL2/SDL.h>
#include <cstdlib>
#include <vector>

class Food{
    public:
        Food(int minX, int minY, int maxX, int maxY, int size);
        int GetX();
        int GetY();
        void Eat();
        void Draw(SDL_Renderer *renderer);
    private:
        int Pos[2];
        std::vector<int> xValues, yValues;
        SDL_Rect Block;
};
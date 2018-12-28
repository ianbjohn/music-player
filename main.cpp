#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_AUDIO);

    cout << "OK" << endl;

    SDL_Quit();

    return 0;
}

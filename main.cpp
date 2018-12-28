#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

typedef struct {
    Uint8* pos;
    Uint32 length;
} AudioData;

void audio_callback(void* data, Uint8* stream, int streamLength)
{
    AudioData* audio = (AudioData* ) data;
    if (audio->length == 0)
        return;

    Uint32 length = (Uint32) streamLength;
    length = (length > audio->length ? audio->length : (Uint32) streamLength);
    SDL_memcpy(stream, audio->pos, length);
    audio->pos += length;
    audio->length -= length;
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_AUDIO);

    cout << "Welcome." << endl;

    SDL_AudioSpec spec;
    Uint8* start;
    Uint32 length;
    AudioData audio;
    SDL_AudioDeviceID device;
    char file[256];

    //main loop
    while (true) {
        cout << "What would you like to play? ";
        cin >> file;

        //load the file
        if (SDL_LoadWAV(file, &spec, &start, &length) == NULL) {
            cerr << SDL_GetError() << endl;
            break;
        }

        //set up audio callback
        audio.pos = start;
        audio.length = length;
        spec.callback = audio_callback;
        spec.userdata = &audio;

        //play the file
        device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
        if (device == 0) {
            cerr << SDL_GetError() << endl;
            break;
        }
        SDL_PauseAudioDevice(device, 0);
        while (audio.length > 0) SDL_Delay(100);
        SDL_PauseAudioDevice(device, 1);

        SDL_FreeWAV(start);
    }

    SDL_CloseAudioDevice(device);
    SDL_Quit();
    return 0;
}

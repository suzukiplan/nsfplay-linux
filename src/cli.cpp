/**
 * NSFPlay for command line
 * Copyright (c) 2024, Yoji Suzuki
 * License under GPLv3
 */
#include <stdio.h>
#include <stdint.h>
#include "./xgm/player/nsf/nsfplay.h"
#include "SDL.h"

#define SAMPLING_RATE 44100
#define SAMPLING_CH 1

static void audioCallback(void* userdata, Uint8* stream, int len)
{
    xgm::NSFPlayer* player = (xgm::NSFPlayer*)userdata;
    player->Render((xgm::INT16*)stream, len / 2);
}

FILE* fopen_utf8(const char* path, const char* mode)
{
    return fopen(path, mode);
}

int main(int argc, char* argv[])
{
    const char* path = nullptr;
    int trackNumber = 0;
    bool error = false;
    for (int i = 1; !error && i < argc; i++) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
                case 't':
                    if (argc <= ++i) {
                        error = true;
                    } else {
                        trackNumber = atoi(argv[i]);
                    }
                    break;
                default:
                    error = true;
            }
        } else {
            path = argv[i];
        }
    }
    if (error || !path) {
        puts("usage: nsfplay [-t track_number]");
        puts("               /path/to/file.nsf");
        return 1;
    }
    xgm::NSFPlayerConfig config;
    xgm::NSF nsf;
    xgm::NSFPlayer player;
    if (!nsf.LoadFile(path)) {
        puts("File load error");
        return -1;
    }
    printf("Title: %s\n",nsf.title);
    printf("Artist: %s\n",nsf.artist);
    printf("Copyright: %s\n",nsf.copyright);
    printf("Ripper: %s\n",nsf.ripper);
    config["MASTER_VOLUME"] = 256;
    config["APU2_OPTION5"] = 0;
    config["APU2_OPTION7"] = 0;
    player.SetConfig(&config);
    player.Load(&nsf);
    player.SetPlayFreq(SAMPLING_RATE);
    player.SetChannels(SAMPLING_CH);
    player.SetSong(trackNumber);
    player.Reset();
puts("foo");

    // initialize SDL sound system
    if (SDL_Init(SDL_INIT_AUDIO)) {
        puts("SDL_Init failed");
        return -1;
    }

    SDL_AudioSpec desired;
    SDL_AudioSpec obtained;
    desired.freq = SAMPLING_RATE;
    desired.format = AUDIO_S16LSB;
    desired.channels = SAMPLING_CH;
    desired.samples = 735; // desired.freq * 20 / 1000;
    desired.callback = audioCallback;
    desired.userdata = &player;
    auto audioDeviceId = SDL_OpenAudioDevice(nullptr, 0, &desired, &obtained, 0);
    if (0 == audioDeviceId) {
        puts("SDL_OpenAudioDevice failed");
        return -1;
    }
    SDL_PauseAudioDevice(audioDeviceId, 0);

    printf("Press enter to exit...\n");
    fgetc(stdin);

    SDL_CloseAudioDevice(audioDeviceId);
    SDL_Quit();
    return 0;
}

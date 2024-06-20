#include <stdio.h>
#include "./xgm/player/nsf/nsfplay.h"

FILE* fopen_utf8(const char* path, const char* mode)
{
    return fopen(path, mode);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        puts("usage: nsfplay /path/to/file.nsf");
        return 1;
    }
    xgm::NSFPlayerConfig config;
    xgm::NSF nsf;
    xgm::NSFPlayer player;
    if (!nsf.LoadFile(argv[1])) {
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
    player.SetPlayFreq(44100);
    player.SetChannels(1);
    player.SetSong(0);
    player.Reset();
    return 0;

}

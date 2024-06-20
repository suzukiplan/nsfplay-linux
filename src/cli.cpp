#include <stdio.h>
#include "./xgm/player/nsf/nsfplay.h"

FILE* fopen_utf8(const char* path, const char* mode)
{
    return fopen(path, mode);
}

int main(int argc, char* argv[])
{
    xgm::NSFPlayer player;
    xgm::NSFPlayerConfig config;
    config["MASTER_VOLUME"] = 256;
    config["APU2_OPTION5"] = 0;
    config["APU2_OPTION7"] = 0;
    player.SetConfig(&config);
    return 0;
}

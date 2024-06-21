#ifndef _NSF_H_
#define _NSF_H_
#include "../soundData.h"

#define NSF_MAX_PATH 512

namespace xgm
{
struct NSFE_Entry {
    const char* tlbl;
    const char* taut;
    INT32 time;
    INT32 fade;
    bool psfx;
};
const unsigned int NSFE_ENTRIES = 256;
const unsigned int NSFE_MIXES = 8;
const INT16 NSFE_MIXE_DEFAULT = 32767;

/**
 * NSF�t�@�C���^
 */
class NSF : public SoundDataMSP
{
  public:
    char magic[5];
    UINT8 version;
    UINT8 songs;
    UINT8 total_songs;
    UINT8 start;
    UINT16 load_address;
    UINT16 init_address;
    UINT16 play_address;
    UINT16 speed_ntsc;
    UINT8 bankswitch[8];
    UINT16 speed_pal;
    UINT8 pal_ntsc;
    UINT8 soundchip;
    bool use_vrc7;
    bool use_vrc6;
    bool use_fds;
    bool use_fme7;
    bool use_mmc5;
    bool use_n106;
    UINT8 extra[4];
    UINT8* body;
    int bodysize;
    UINT8* nsfe_image;
    NSFE_Entry nsfe_entry[NSFE_ENTRIES];
    INT16 nsfe_mixe[NSFE_MIXES];
    int vrc7_type;
    const UINT8* vrc7_patches;
    UINT16 speed_dendy;
    UINT8 regn;
    int regn_pref;
    UINT8 nsf2_bits;

    int song;
    bool playlist_mode;
    int time_in_ms, default_playtime;
    int loop_in_ms;
    int fade_in_ms, default_fadetime;
    int loop_num, default_loopnum;
    bool playtime_unknown;
    bool title_unknown;

    NSF();
    ~NSF();
    bool Load(UINT8* image, UINT32 size);
    bool LoadNSFe(UINT8* image, UINT32 size, bool nsf2);
    int GetLength();
    void SetDefaults(int playtime, int fadetime, int loopnum);
    void SetLength(int time_in_ms);
    void SetSong(int);
    int GetSong();
    int GetSongNum();
    int GetPlayTime();
    int GetLoopTime();
    int GetFadeTime();
    int GetLoopNum();
    bool UseNSFePlaytime();
};

} // namespace xgm
#endif

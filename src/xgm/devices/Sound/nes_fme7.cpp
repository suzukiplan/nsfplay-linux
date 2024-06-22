#include "nes_fme7.h"

using namespace xgm;

NES_FME7::NES_FME7()
{
    for (int c = 0; c < 2; ++c) {
        for (int t = 0; t < 3; ++t) {
            sm[c][t] = 128;
        }
    }
}

NES_FME7::~NES_FME7()
{
}

void NES_FME7::SetClock(long c)
{
    this->clock = c * 2;
}

void NES_FME7::SetRate(long r)
{
    // always 44100Hz
}

void NES_FME7::SetOption(int id, int val)
{
    if (id < OPT_END) {
        // option[id] = val;
    }
}

void NES_FME7::Reset()
{
    psg.reset(100);
    for (int i = 0; i < 16; ++i) // blank all registers
    {
        Write(0xC000, i);
        Write(0xE000, 0);
    }
    Write(0xC000, 0x07); // disable all tones
    Write(0xE000, 0x3F);
}

bool NES_FME7::Write(xgm::UINT32 adr, xgm::UINT32 val, xgm::UINT32 id)
{
    if (adr == 0xC000) {
        psg.latch(val);
        return true;
    }
    if (adr == 0xE000) {
        psg.write(val);
        return true;
    } else
        return false;
}

bool NES_FME7::Read(xgm::UINT32 adr, xgm::UINT32& val, xgm::UINT32 id)
{
    return false;
}

void NES_FME7::Tick(xgm::UINT32 clocks)
{
    // execute when render
}

xgm::UINT32 NES_FME7::Render(xgm::INT32 b[2])
{
    short l, r;
    psg.tick(&l, &r, 81);
    b[0] = l;
    b[1] = r;
    return 2;
}

void NES_FME7::SetStereoMix(int trk, xgm::INT16 mixl, xgm::INT16 mixr)
{
    if (trk < 0) return;
    if (trk > 2) return;
    sm[0][trk] = mixl;
    sm[1][trk] = mixr;
}

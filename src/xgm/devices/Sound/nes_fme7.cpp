#include "nes_fme7.h"

using namespace xgm;

const int DIVIDER = 8; // TODO this is not optimal, rewrite PSG output

NES_FME7::NES_FME7()
{
    psg = PSG_new((e_uint32)DEFAULT_CLOCK, DEFAULT_RATE);
    divider = 0;

    for (int c = 0; c < 2; ++c)
        for (int t = 0; t < 3; ++t)
            sm[c][t] = 128;
}

NES_FME7::~NES_FME7()
{
    if (psg)
        PSG_delete(psg);
}

void NES_FME7::SetClock(long c)
{
    this->clock = c * 2;
}

void NES_FME7::SetRate(long r)
{
    // rate = r ? r : DEFAULT_RATE;
    rate = DEFAULT_CLOCK / double(DIVIDER); // TODO rewrite PSG to integrate with clock
    if (psg) {
        PSG_set_rate(psg, (e_uint32)rate);
    }
}

void NES_FME7::SetOption(int id, int val)
{
    if (id < OPT_END) {
        // option[id] = val;
    }
}

void NES_FME7::Reset()
{
    for (int i = 0; i < 16; ++i) // blank all registers
    {
        Write(0xC000, i);
        Write(0xE000, 0);
    }
    Write(0xC000, 0x07); // disable all tones
    Write(0xE000, 0x3F);

    divider = 0;
    if (psg)
        PSG_reset(psg);
}

bool NES_FME7::Write(xgm::UINT32 adr, xgm::UINT32 val, xgm::UINT32 id)
{
    if (adr == 0xC000) {
        if (psg)
            PSG_writeIO(psg, 0, val);
        return true;
    }
    if (adr == 0xE000) {
        if (psg)
            PSG_writeIO(psg, 1, val);
        return true;
    } else
        return false;
}

bool NES_FME7::Read(xgm::UINT32 adr, xgm::UINT32& val, xgm::UINT32 id)
{
    // not sure why this was here - BS
    // if (psg)
    //  val = PSG_readIO (psg);

    return false;
}

void NES_FME7::Tick(xgm::UINT32 clocks)
{
    divider += clocks;
    while (divider >= DIVIDER) {
        divider -= DIVIDER;
        if (psg) PSG_calc(psg);
    }
}

xgm::UINT32 NES_FME7::Render(xgm::INT32 b[2])
{
    b[0] = b[1] = 0;

    for (int i = 0; i < 3; ++i) {
        // note negative polarity
        b[0] -= psg->cout[i] * sm[0][i];
        b[1] -= psg->cout[i] * sm[1][i];
    }
    b[0] >>= (7 - 4);
    b[1] >>= (7 - 4);

    // master volume adjustment
    const INT32 MASTER = INT32(0.64 * 256.0);
    b[0] = (b[0] * MASTER) >> 8;
    b[1] = (b[1] * MASTER) >> 8;

    return 2;
}

void NES_FME7::SetStereoMix(int trk, xgm::INT16 mixl, xgm::INT16 mixr)
{
    if (trk < 0) return;
    if (trk > 2) return;
    sm[0][trk] = mixl;
    sm[1][trk] = mixr;
}

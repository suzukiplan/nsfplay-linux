#include "nes_vrc6.h"

namespace xgm
{

NES_VRC6::NES_VRC6()
{
    SetClock(DEFAULT_CLOCK);
    SetRate(DEFAULT_RATE);

    halt = false;
    freq_shift = 0;

    for (int c = 0; c < 2; ++c)
        for (int t = 0; t < 3; ++t)
            sm[c][t] = 128;
    Reset();
}

NES_VRC6::~NES_VRC6()
{
}

void NES_VRC6::SetStereoMix(int trk, int16_t mixl, int16_t mixr)
{
    if (trk < 0) return;
    if (trk > 2) return;
    sm[0][trk] = mixl;
    sm[1][trk] = mixr;
}

void NES_VRC6::SetClock(long c)
{
    clock = c;
}

void NES_VRC6::SetRate(long r)
{
    rate = r ? r : DEFAULT_RATE;
}

void NES_VRC6::SetOption(int id, int val)
{
    if (id < OPT_END) {
        // option[id] = val;
    }
}

void NES_VRC6::Reset()
{
    freq[0] = 0;
    freq[1] = 0;
    freq[2] = 0;
    counter[0] = 0;
    counter[1] = 0;
    counter[2] = 0;
    enable[0] = 0;
    enable[1] = 0;
    enable[2] = 0;
    Write(0x9003, 0);
    for (int i = 0; i < 3; i++) {
        Write(0x9000 + i, 0);
        Write(0xa000 + i, 0);
        Write(0xb000 + i, 0);
    }
    count14 = 0;
    mask = 0;
    phase[0] = 0;
    phase[1] = 0;
    phase[2] = 0;
}

int16_t NES_VRC6::calc_sqr(int i, uint32_t clocks)
{
    static const int16_t sqrtbl[8][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}};

    if (!enable[i])
        return 0;

    if (!halt) {
        counter[i] += clocks;
        while (counter[i] > freq2[i]) {
            phase[i] = (phase[i] + 1) & 15;
            counter[i] -= (freq2[i] + 1);
        }
    }

    return (gate[i] || sqrtbl[duty[i]][phase[i]]) ? volume[i] : 0;
}

int16_t NES_VRC6::calc_saw(uint32_t clocks)
{
    if (!enable[2])
        return 0;

    if (!halt) {
        counter[2] += clocks;
        while (counter[2] > freq2[2]) {
            counter[2] -= (freq2[2] + 1);

            // accumulate saw
            ++count14;
            if (count14 >= 14) {
                count14 = 0;
                phase[2] = 0;
            } else if (0 == (count14 & 1)) // only accumulate on even ticks
            {
                phase[2] = (phase[2] + volume[2]) & 0xFF; // note 8-bit wrapping behaviour
            }
        }
    }

    // only top 5 bits of saw are output
    return phase[2] >> 3;
}

void NES_VRC6::Tick(uint32_t clocks)
{
    out[0] = calc_sqr(0, clocks);
    out[1] = calc_sqr(1, clocks);
    out[2] = calc_saw(clocks);
}

uint32_t NES_VRC6::Render(int32_t b[2])
{
    int32_t m[3];
    m[0] = out[0];
    m[1] = out[1];
    m[2] = out[2];

    // note: signal is inverted compared to 2A03

    m[0] = (mask & 1) ? 0 : -m[0];
    m[1] = (mask & 2) ? 0 : -m[1];
    m[2] = (mask & 4) ? 0 : -m[2];

    b[0] = m[0] * sm[0][0];
    b[0] += m[1] * sm[0][1];
    b[0] += m[2] * sm[0][2];
    // b[0] >>= (7 - 7);

    b[1] = m[0] * sm[1][0];
    b[1] += m[1] * sm[1][1];
    b[1] += m[2] * sm[1][2];
    // b[1] >>= (7 - 7);

    // master volume adjustment
    const int32_t MASTER = int32_t(256.0 * 1223.0 / 1920.0);
    b[0] = (b[0] * MASTER) >> 8;
    b[1] = (b[1] * MASTER) >> 8;

    return 2;
}

bool NES_VRC6::Write(uint32_t adr, uint32_t val, uint32_t id)
{
    int ch, cmap[4] = {0, 0, 1, 2};

    switch (adr) {
        case 0x9000:
        case 0xa000:
            ch = cmap[(adr >> 12) & 3];
            volume[ch] = val & 15;
            duty[ch] = (val >> 4) & 7;
            gate[ch] = (val >> 7) & 1;
            break;
        case 0xb000:
            volume[2] = val & 63;
            break;

        case 0x9001:
        case 0xa001:
        case 0xb001:
            ch = cmap[(adr >> 12) & 3];
            freq[ch] = (freq[ch] & 0xf00) | val;
            freq2[ch] = (freq[ch] >> freq_shift);
            if (counter[ch] > freq2[ch]) counter[ch] = freq2[ch];
            break;

        case 0x9002:
        case 0xa002:
        case 0xb002:
            ch = cmap[(adr >> 12) & 3];
            freq[ch] = ((val & 0xf) << 8) + (freq[ch] & 0xff);
            freq2[ch] = (freq[ch] >> freq_shift);
            if (counter[ch] > freq2[ch]) counter[ch] = freq2[ch];
            if (!enable[ch]) // if enable is being turned on, phase should be reset
            {
                if (ch == 2) {
                    count14 = 0; // reset saw
                }
                phase[ch] = 0;
            }
            enable[ch] = (val >> 7) & 1;
            break;

        case 0x9003:
            halt = val & 1;
            freq_shift =
                (val & 4) ? 8 : (val & 2) ? 4
                                          : 0;
            freq2[0] = (freq[0] >> freq_shift);
            freq2[1] = (freq[1] >> freq_shift);
            freq2[2] = (freq[2] >> freq_shift);
            if (counter[0] > freq2[0]) counter[0] = freq2[0];
            if (counter[1] > freq2[1]) counter[1] = freq2[1];
            if (counter[2] > freq2[2]) counter[2] = freq2[2];
            break;

        default:
            return false;
    }

    return true;
}

bool NES_VRC6::Read(uint32_t adr, uint32_t& val, uint32_t id)
{
    return false;
}

} // namespace xgm

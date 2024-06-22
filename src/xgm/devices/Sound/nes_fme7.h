#ifndef _NES_FME7_H_
#define _NES_FME7_H_
#include "../device.h"
#include "legacy/emu2149.h"

namespace xgm
{

class NES_FME7 : public ISoundChip
{
  public:
    enum {
        OPT_END
    };

  protected:
    // int option[OPT_END];
    INT32 sm[2][3]; // stereo mix
    INT16 buf[2];
    PSG* psg;
    int divider; // clock divider
    long clock, rate;

  public:
    NES_FME7();
    ~NES_FME7();
    virtual void Reset();
    virtual void Tick(UINT32 clocks);
    virtual UINT32 Render(INT32 b[2]);
    virtual bool Read(UINT32 adr, UINT32& val, UINT32 id = 0);
    virtual bool Write(UINT32 adr, UINT32 val, UINT32 id = 0);
    virtual void SetClock(long c);
    virtual void SetRate(long r);
    virtual void SetOption(int, int);
    virtual void SetMask(int m)
    {
        if (psg) PSG_setMask(psg, m);
    }
    virtual void SetStereoMix(int trk, xgm::INT16 mixl, xgm::INT16 mixr);
};

} // namespace xgm

#endif

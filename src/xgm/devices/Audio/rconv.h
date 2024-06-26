#ifndef _RCONV_H_
#define _RCONV_H_
#include "../device.h"

namespace xgm
{

class NES_CPU; // forward
class NES_DMC;

// RateConverter
//
// Subdivides clocks of Tick and passes to each attached IRenderable.
// Also responsible for clocking the CPU (and related devices)
// before the IRenderables.

class RateConverter : public IRenderable
{
  protected:
    IRenderable* target;
    long clock, rate;
    int mult;
    int32_t tap[2][128];
    int hri[128];
    uint32_t clocks; // render clocks pending Tick
    NES_CPU* cpu;
    NES_DMC* dmc;
    int cpu_clocks; // CPU clocks pending Tick
    int cpu_rest;   // extra clock accumulator (instructions will get ahead by a few clocks)
    bool fast_skip;

    void ClockCPU(int c);

  public:
    RateConverter();
    virtual ~RateConverter();
    void Attach(IRenderable* t);
    void Reset();
    void SetClock(long clock);
    void SetRate(long rate);
    virtual void Tick(uint32_t clocks_); // ticks get executed during Render
    virtual uint32_t Render(int32_t b[2]);
    virtual void Skip(); // Does ticks in lieu of Render
    inline uint32_t FastRender(int32_t b[2]);

    // call TickCPU before each Tick
    void TickCPU(int t) { cpu_clocks += t; }

    void SetCPU(NES_CPU* c) { cpu = c; }
    void SetDMC(NES_DMC* d) { dmc = d; }
    void SetFastSkip(bool s) { fast_skip = s; }
};

} // namespace xgm
#endif

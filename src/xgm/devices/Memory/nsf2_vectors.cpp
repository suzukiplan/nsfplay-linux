#include "nsf2_vectors.h"
#include "../CPU/nes_cpu.h"

namespace xgm
{

NSF2_Vectors::NSF2_Vectors()
{
}

NSF2_Vectors::~NSF2_Vectors()
{
}

void NSF2_Vectors::Reset()
{
}

bool NSF2_Vectors::Read(uint32_t adr, uint32_t& val, uint32_t id)
{
    if (adr < 0xFFFA) return false;
    if (adr > 0xFFFF) return false;
    val = vectors[adr - 0xFFFA];
    return true;
}

bool NSF2_Vectors::Write(uint32_t adr, uint32_t val, uint32_t id)
{
    if (adr == 0x2000) {
        cpu->EnableNMI(val & 0x80);
        return true;
    }

    if (adr < 0xFFFE) return false;
    if (adr > 0xFFFF) return false;
    vectors[adr - 0xFFFA] = val;
    return true;
}

void NSF2_Vectors::ForceVector(int vector, uint32_t adr)
{
    if (vector < 0 || vector > 2) return;
    vectors[(vector * 2) + 0] = adr & 0xFF;
    vectors[(vector * 2) + 1] = (adr >> 8) & 0xFF;
}

void NSF2_Vectors::SetCPU(NES_CPU* cpu_)
{
    cpu = cpu_;
}

} // namespace xgm

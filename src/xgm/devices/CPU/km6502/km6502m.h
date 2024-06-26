#define BUILD_M6502 1
#define BUILD_M65C02 0
#define BUILD_HUC6280 0

#include "km6502.h"

#define C_FLAG K6502_C_FLAG
#define Z_FLAG K6502_Z_FLAG
#define I_FLAG K6502_I_FLAG
#define D_FLAG K6502_D_FLAG
#define B_FLAG K6502_B_FLAG
#define R_FLAG K6502_R_FLAG
#define V_FLAG K6502_V_FLAG
#define N_FLAG K6502_N_FLAG
#define T_FLAG 0

#define BASE_OF_ZERO 0x0000

#define VEC_RESET 0xFFFC
#define VEC_NMI 0xFFFA
#define VEC_INT 0xFFFE

#define VEC_BRK VEC_INT

#define IRQ_INIT K6502_INIT
#define IRQ_RESET K6502_RESET
#define IRQ_NMI K6502_NMI
#define IRQ_BRK K6502_BRK
#define IRQ_INT K6502_INT

#ifdef STATIC_CONTEXT6502
extern struct K6502_Context STATIC_CONTEXT6502;
#define __THIS__ STATIC_CONTEXT6502
#define __CONTEXT void
#define __CONTEXT_ /* none */
#define __THISP    /* none */
#define __THISP_   /* none */
#else
#define __THIS__ (*pc)
#define __CONTEXT struct K6502_Context* pc
#define __CONTEXT_ struct K6502_Context *pc,
#define __THISP pc
#define __THISP_ pc,
#endif

#define K_EXEC K6502_Exec

#if USE_USERPOINTER
#define __THIS_USER_ __THIS__.user,
#else
#define __THIS_USER_
#endif

#if USE_CALLBACK
#if USE_INLINEMMC
static Uword Inline K_READ(__CONTEXT_ Uword adr)
{
    return __THIS__.ReadByte[adr >> USE_INLINEMMC](__THIS_USER_ adr);
}
static void Inline K_WRITE(__CONTEXT_ Uword adr, Uword value)
{
    __THIS__.WriteByte[adr >> USE_INLINEMMC](__THIS_USER_ adr, value);
}
#else
static Uword Inline K_READ(__CONTEXT_ Uword adr)
{
    return __THIS__.ReadByte(__THIS_USER_ adr);
}
static void Inline K_WRITE(__CONTEXT_ Uword adr, Uword value)
{
    __THIS__.WriteByte(__THIS_USER_ adr, value);
}
#endif
#else
static Uword Inline K_READ(__CONTEXT_ Uword adr)
{
    return K6502_ReadByte(__THIS_USER_ adr);
}
static void Inline K_WRITE(__CONTEXT_ Uword adr, Uword value)
{
    K6502_WriteByte(__THIS_USER_ adr, value);
}
#endif
#ifndef K_READNP
#define K_READNP K_READ
#define K_WRITENP K_WRITE
#endif
#ifndef K_READZP
#if !USE_DIRECT_ZEROPAGE
#define K_READZP K_READ
#define K_WRITEZP K_WRITE
#else
static Uword Inline K_READZP(__CONTEXT_ Uword adr)
{
    return __THIS__.zeropage[adr];
}
static void Inline K_WRITEZP(__CONTEXT_ Uword adr, Uword value)
{
    __THIS__.zeropage[adr] = value;
}
#endif
#endif

#include "km6502ft.h"
#include "km6502cd.h"
#include "km6502ct.h"
#include "km6502ot.h"
#include "km6502ex.h"

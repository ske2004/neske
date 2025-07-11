/* PC-Engine phys memory map, denoted by pg number.
 * PC-Engine uses a 21bit phys memory bus. So, do bsr 13 to get pg number.
 *
 * $00:$7F ROM
 * $80:$F7 Unused (ret $FF)
 * $F8:$FB RAM (only 1 pg, $2000 bytes, rest is mirrored)
 * $FC:$FE Unused (ret $FF)
 * $FF:$FF Hardware pg [see HwPage.H]
 */
#include "Basics.H"
#include "Bin.H"
#include "Hu6.H"
#include "Dbg.H"
#include "Arr.H"
#include "HwPage.H"
#include "Vce.H"
#include "Vdc.H"
#include <cstdio>

struct Pce : IBus
{
  PceBin &rom;
  Clk clk;
  Hu6 cpu;
  Vce vce;
  Vdc vdc;
  HwPage hwpage;
  Arr<U8, 0x2000> ram; // TODO: what is init ram state?

  Pce(PceBin &rom);

  auto Read(U32 addr) -> U8 override;
  auto Write(U32 addr, U8 data) -> U0 override;
  auto Run()->U0;
};

auto Pce::Read(U32 addr) -> U8
{
  U32 pg = ADR_BNK(addr);
  addr = addr&BNK_MASK;
  if (pg>=0x00 && pg<=0x7F) return rom.Get(addr);
  if (pg>=0xF8 && pg<=0xFB) return ram[addr];
  if (pg==0xFF) {
    clk.ExtraCycle();
    return hwpage.Read(addr);
  }
  return 0xFF;
}

auto Pce::Write(U32 addr, U8 data) -> U0
{
  U32 pg = ADR_BNK(addr);
  addr = addr&BNK_MASK;
  if (pg>=0x00 && pg<=0x7F) rom.Set(addr, data);
  if (pg>=0xF8 && pg<=0xFB) ram[addr] = data;
  if (pg==0xFF) {
    clk.ExtraCycle();
    hwpage.Write(addr, data);
  }
}

Pce::Pce(PceBin &rom) : 
  rom(rom),
  ram({}),
  clk([this](){ hwpage.Cycle(clk); }),
  cpu(*this, this->clk),
  hwpage(vce, vdc)
{
}

auto Pce::Run()->U0
{
  Dbg::Info("PCE: run");
  cpu.Run();
}



#include "Cheats.hpp"
#include "Types.h"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

u32 ptr_addr;

// Checks address values to determine if the right data is loaded into the memory region
bool isInBattle()
{
    u32 check1;
    u32 check2;
    if (!READ32(playerBattlePointer_addr, ptr_addr)) return false;
    if (!READ32(ptr_addr, check1)) return false;
    if (!READ32(enemyBattlePointer_addr, ptr_addr)) return false;
    if (!READ32(ptr_addr, check2)) return false;
    return (check1 == 0x004CC33C && check2 == 0x004CBF94);
}

// Overwrites current HP amount with max HP value
void infHPBattleFunc(MenuEntry *entry)
{
    static u32 maxHP_addr = digimon_addr + 0x24;
    u32 maxHP;
    u32 currentHP;
    if (isInBattle())
    {
        if (!READ32(playerBattlePointer_addr, ptr_addr)) return;
        if (!READ32(maxHP_addr, maxHP)) return;
        if (!READ32(ptr_addr + 0x170, currentHP)) return;
        if (currentHP < maxHP)
            WRITE16(ptr_addr + 0x170, maxHP);
    }
}

// Overwrites current MP amount with max MP value
void infMPBattleFunc(MenuEntry *entry)
{
    static u32 maxMP_addr = digimon_addr + 0x2C;
    u32 maxMP;
    u32 currentMP;
    if (isInBattle())
    {
        if (!READ32(playerBattlePointer_addr, ptr_addr)) return;
        if (!READ32(maxMP_addr, maxMP)) return;
        if (!READ32(ptr_addr + 0x178, currentMP)) return;
        if (currentMP < maxMP)
            WRITE16(ptr_addr + 0x178, maxMP);
    }
}

// Sets SP amount to 100 to allow infinite Special move use
void infSPBattleFunc(MenuEntry *entry)
{ 
    u8 currentSP;

    if (isInBattle())
    {
        if (!READ32(playerBattlePointer_addr, ptr_addr)) return;
        if (!READ8(ptr_addr + 0x1B0, currentSP)) return;
        if (currentSP < 100)
            WRITE8(ptr_addr + 0x1B0, 100);
    }
}

// Sets enemy's HP to 0 for instant kill
void instantEnemyDeathFunc(MenuEntry *entry)
{
    if (isInBattle() && entry->Hotkeys[0].IsPressed())
    {
        if (!READ32(enemyBattlePointer_addr, ptr_addr)) return;
        WRITE32(ptr_addr + 0x170, 0);
    }
}

// Sets enemy's HP to 1 at battle start to allow single-hit kill
void oneHitKOFunc(MenuEntry *entry)
{
    u32 currentHP;

    if (isInBattle())
    {
        if (!READ32(enemyBattlePointer_addr, ptr_addr)) return;
        if (!READ32(ptr_addr + 0x170, currentHP)) return;
        if (currentHP > 1)
            WRITE32(ptr_addr + 0x170, 1);
    }
}

// Sets enemy's MP to 0 so they cannot attack
void enemyNoMPFunc(MenuEntry *entry)
{
    u32 currentMP;

    if (isInBattle())
    {
        if (!READ32(enemyBattlePointer_addr, ptr_addr)) return;
        if (!READ32(ptr_addr + 0x178, currentMP)) return;
        if (currentMP > 0)
            WRITE32(ptr_addr + 0x178, 0);
    }
}
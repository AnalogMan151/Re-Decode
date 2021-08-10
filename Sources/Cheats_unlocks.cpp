#include "Cheats.hpp"
#include "Types.h"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

// Mem copies bitmask to unlock all accessories
void unlockAccessoriesFunc(MenuEntry *entry)
{
    static u32 accessories_addr = tamer_addr + 0x2240;
    static u8 data[22] = { 0x11, 0x95, 0x0D, 0xFE, 0xEB, 0x9A, 0xC5, 0xEF, 
                           0x14, 0xBE, 0xB8, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x7F };

    if (Process::Patch(accessories_addr, data, 22))
        MessageBox("Accessory Access Granted!", DialogType::DialogOk, ClearScreen::Both)();
    else    
        MessageBox("Patching failed!", DialogType::DialogOk, ClearScreen::Both)();
}

// Mem copies bitmask to unlock all skills
void unlockSkillsFunc(MenuEntry *entry)
{
    static u32 skills_addr = digimon_addr + 0x69C;
    static u8 data[8] = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01 };

    if (Process::Patch(skills_addr, data, 8))
        MessageBox("All Skills Mastered!", DialogType::DialogOk, ClearScreen::Both)();
    else
        MessageBox("Patching failed!", DialogType::DialogOk, ClearScreen::Both)();
}

// Mem copies bitmask to unlock all digivolutions
void unlockFieldGuideFunc(MenuEntry *entry)
{
    static u32 fieldGuide_addr = tamer_addr + 0x2458;
    static u8 data[32] = { 0xFE, 0xFF, 0xFD, 0xFF, 0xFA, 0xA1, 0xEF, 0xEF, 
                           0x7C, 0x3D, 0xBE, 0x9F, 0xFE, 0xC7, 0x77, 0x3F, 
                           0x18, 0x7D, 0xD0, 0x7F, 0xC2, 0x75, 0xA1, 0xD0, 
                           0xFD, 0x3F, 0xFF, 0x3F, 0xFF, 0xFF, 0xB5, 0x00 };

    if (Process::Patch(fieldGuide_addr, data, 32))
        MessageBox("Memory patch completed!", DialogType::DialogOk, ClearScreen::Both)();
    else
        MessageBox("Patching failed!", DialogType::DialogOk, ClearScreen::Both)();
}

// Mem copies bitmask to unlock all cards (does not grant any quantity)
void unlockAllCardsFunc(MenuEntry *entry)
{
    static u32 cardBitMask_addr = tamer_addr + 0x23B8;
    static u8 data[74] = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                           0xFF, 0x1F };

    if (Process::Patch(cardBitMask_addr, data, 74))
        MessageBox("Cards injected successfully!", DialogType::DialogOk, ClearScreen::Both)();
    else
        MessageBox("Failed to draw from the deck", DialogType::DialogOk, ClearScreen::Both)();
}
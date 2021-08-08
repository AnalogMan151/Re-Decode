#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

using namespace CTRPluginFramework;
using StringVector = std::vector<std::string>;

#define code_addr 0x00100000
// Game Animation Speed (float): 0x885C
// Speed: Enemy (float): 0x1FDCE8
// Speed: Running (float): 0x34B8B8
// Speed: Walking (float): 0x34B8BC
// Movement Speed Multiplier (float): 0x360504
// Max Training Boost Multiplier (float): 0x4B5D0

#define readonly_addr 0x004A1000
// Tiaga's Model (Utf8 string): 0xCD8
// Rina's model (Utf8 string): 0xD48

#define global_addr 0x004DD000
// Render Distance #1 (float): 0x8118
// Render Distance #2 (float): 0x811C
// Action sequence (u32): 0x8B20
// Player Character/Gender (u32): 0x204BC
// Training Boost Duration (u32): 0x21C48
// Training Boost Multiplier(float): 0x21C4C
// Bitflag of stats being boosted (u8): 0x21C50
// Evolution Target ID (u32): + 0x23170
// FPS (u8): 0x599D4

#define playerBattlePointer_addr (global_addr + 0x8408)
// Offsets from pointer value:
    // Current HP (u32): 0x170
    // Current MP (u32): 0x178
    // SP Guage (u32): 0x1B0

#define enemyBattlePointer_addr (global_addr + 0x229CC)
// Offsets from pointer value:
    // Current HP (u32): 0x170
    // Current MP (u32): 0x178
    // SP Guage (u32): 0x1B0

#define tamer_addr (global_addr + 0x1E68C)
// Tamer Name (Utf16 string)(0x10): 0x0
// Playtime in seconds (u32): 0x24
// Bits (u32): 0x28
// MB (u32): 0x2C
// Decode Level (u32): 0x1E34
// Decode XP (u32): 0x1E38
// Bitmask of obtained accessories (0x18): 0x2240
// Bitmask of discovered cards (0x4A): 0x23B8
// Bitmask of discovered evolutions (0x20): 0x2458
// Card quantities (024C): 0x36D4

#define inventory_addr (global_addr + 0x1EBD4)
// Item 1 Type (u32): 0x0
// Item 1 Amount (u32): 0x4
// ...
// Item 20 Type (u32): 0x98
// Item 20 Amount (u32): x9C

#define storage_addr (global_addr + 0x1EDB4)
// Item 1 Type (u32): 0x0
// Item 1 Amount (u32): 0x4
// ...
// Item 11 Type (u32): 0x50
// Item 11 Amount (u32): 0x54

#define digimon_addr (global_addr + 0x1FE18)
// Name (Utf16 string)(0x10): 0x0
// Species ID (u32): 0x14
// Current HP (u32): 0x20
// Max HP (u32): 0x24
// Current MP (u32): 0x28
// Max MP (u32): 0x2C
// Attack (u16): 0x30
// Defense (u16): 0x32
// Speed (u16): 0x34
// Brains (u16): 0x36
// Weight (u32): 0x38
// Nature (u8): 0x3C
// Lives (u8): 0x3D
// Happiness (float): 0x40
// Discipline (float): 0x44
// Poop/Corruption (u8): 0x48
// Sleep Timer (u32): 0x510
// Health Status (u8): 0x518
// Hunger Timer (u32): 0x51C
// Exhaustion (u8): 0x530
// Fullness (u8): 0x538
// isHungry Flag (u8): 0x539
// Care Mistakes (u32): 0x53C
// Battles (u32): 0x540
// hasToPoop Flag (u8): 0x549
// Poop Timer (u32): 0x550
// Lifetime (u32): 0x55C
// Evolution Timer (u32): 0x560
// Bitmask of learned skills (0x8): 0x69C

#define heap_addr 0x08000000
// Camera Properties: 0xA0C80

#define camera_addr (heap_addr + 0xA0C80)
// Camera X (float): 0xD8
// Camera Y (float): 0xDC
// Camera Z (float): 0xE0
// Zoom (float): 0xE4
// Current Pitch (float): 0xE8
// Current Yaw (float): 0xEC
// Max Yaw (float): 0xF0
// Min Yaw (float): 0xF4
// Unknwon (float): 0xF8

#define assets_addr 0x14000000
// ?? Player Run Speed?? (float): 0x17264B8
// ?? Player Walk Speed?? (float): 0x17264BC

/*
u8 digimonList[179] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,18,19,20,21,
                       22,23,24,25,26,27,28,29,30,31,33,35,36,37,38,39,40,
                       45,47,48,49,50,51,53,54,55,56,57,58,59,61,62,63,66,
                       67,68,69,70,72,74,75,76,77,81,82,83,84,85,87,88,89,
                       90,91,92,95,97,98,99,100,101,102,103,104,105,106,110,
                       111,112,113,114,116,117,118,120,121,122,123,124,125,131,
                       132,136,138,139,140,141,142,148,150,151,152,153,154,155,
                       156,157,158,161,166,167,168,170,172,173,174,176,181,183,
                       188,190,191,192,194,195,196,197,198,199,200,201,202,203,
                       204,205,208,209,210,211,212,213,214,215,216,217,218,219,
                       220,221,224,225,226,227,228,229,230,231,232,233,234,235,
                       236,237,238,239,240,242,244,245,247};
*/

enum BOOSTED_TRAINING_FLAGS
{
    FLAG_NONE   = 0x0,
    FLAG_HP     = 0x1,
    FLAG_MP     = 0x2,
    FLAG_ATK    = 0x4,
    FLAG_DEF    = 0x8,
    FLAG_SPD    = 0x10,
    FLAG_BRN    = 0x20
};

enum NATURES
{
    Lively, Brave, Hardy, Relaxed, Clever, 
    Quiet, Calm, Strategist, Timid, Combi_A, 
    Combi_B, Schemer, Burst, Build, Cunning
};

enum ACTIONS
{
    TIME_WAS_FAST       = 0x1,
    TIME_WAS_SLOW       = 0x2,
    LOSE_LIFE           = 0x4,
    EVOLVE              = 0x8,
    DIE                 = 0x10,
    POOP                = 0x20,
    SLEEP_DEPRIVED      = 0x40,
    STARVED             = 0x80,
    ACCIDENT            = 0x100
};

// Convenience Patches
void setMoneyFunc(MenuEntry *entry);
void setMoneyKBFunc(MenuEntry *entry);
void setDecodeLVLFunc(MenuEntry *entry);
void mapDPAD2CStickFunc(MenuEntry *menu);
void enable60FPSFunc(MenuEntry *entry);
void enhanceRenderDistance(MenuEntry *entry);
void setRunSpeedFunc(MenuEntry *entry);
void setRunSpeedKBFunc(MenuEntry *entry);
void setTrainingMultiFunc(MenuEntry *entry);
void setTrainingMultiKBFunc(MenuEntry *entry);
void maxKnownCards(MenuEntry *entry);

// Battle Hacks
void infHPBattleFunc(MenuEntry *entry);
void infMPBattleFunc(MenuEntry *entry);
void infSPBattleFunc(MenuEntry *entry);
void instantEnemyDeathFunc(MenuEntry *entry);
void oneHitKOFunc(MenuEntry *entry);
void enemyNoMPFunc(MenuEntry *entry);

// Stat Adjustments
void setMaxHPFunc(MenuEntry *entry);
void setMaxMPFunc(MenuEntry *entry);
void setATKFunc(MenuEntry *entry);
void setDEFFunc(MenuEntry *entry);
void setSPDFunc(MenuEntry *entry);
void setBRNFunc(MenuEntry *entry);

// Care Modifiers
void freezeSleepFunc(MenuEntry *entry);
void freezeHungerFunc(MenuEntry *entry);
void freezePoopFunc(MenuEntry *entry);
void neverExhaustedFunc(MenuEntry *entry);
void neverUnhealthyFunc(MenuEntry *entry);
void maxLivesFunc(MenuEntry *entry);
void setDisciplineMeterFunc(MenuEntry *entry);
void setHappinessMeterFunc(MenuEntry *entry);
void setPoopMeterFunc(MenuEntry *entry);
void setWeightFunc(MenuEntry *entry);
void setNatureFunc(MenuEntry *entry);
void setCareMistakeFunc(MenuEntry *entry);
void instantDigivolveFunc(MenuEntry *entry);
void freezeDigimonFunc(MenuEntry *entry);
void killDigimonFunc(MenuEntry *entry);

// Unlockables
void unlockFieldGuideFunc(MenuEntry *entry);
void unlockAccessoriesFunc(MenuEntry *entry);
void unlockSkillsFunc(MenuEntry *entry);
void unlockAllCardsFunc(MenuEntry *entry);

// Fun Mods
void controlCameraZoom(MenuEntry *entry);;
void setAnimationSpeedFunc(MenuEntry *entry);
void setAnimationSpeedKBFunc(MenuEntry *entry);
void choosePlayerFunc(MenuEntry *menu);
void setPlayerNameKBFunc(MenuEntry *entry);
void setDigiNameKBFunc(MenuEntry *entry);
void replacePartnerDigimonFunc(MenuEntry *entry);

#endif
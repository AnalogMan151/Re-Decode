#include "Cheats.hpp"
#include "Types.h"
#include "Helpers.hpp"

static u32 money = -1;
static float runSpeedMultiplier = 1.5f;
static float boostTrainingMultiplier = 1.0f;

extern MenuEntry *g_setMoneyFunc;
extern MenuEntry *g_setRunSpeedFunc;
extern MenuEntry *g_setTrainingMultiFunc;

using namespace CTRPluginFramework;

void setMoneyFunc(MenuEntry *entry)
{
    static u32 bits_addr = tamer_addr + 0x28;

    if (!entry->IsActivated())
    {
        money = -1;
        return;
    }

    if (entry-> WasJustActivated() && money == -1)
        READ32(bits_addr, money);
    else if (entry -> IsActivated())
        WRITE32(bits_addr, money);
}

// Experience by level
static u32 decodeLVXP[31] = {
       0,     15,     50,    125,    300,    480,    680,    920,   1200,  1550, 
    2000,   2800,   4000,   5200,   6400,   8000,  10000,  13500,  17000,  21000, 
    25000,  30000,  35000,  40000,  45000,  50000,  60000,  75000, 100000, 140000, 200000
};


void setDecodeLVLFunc(MenuEntry *entry)
{
    static u32 decodeLV_addr = tamer_addr + 0x1E34;
    static u32 decodeXP_addr = tamer_addr + 0x1E38;
    u8 input;

    Keyboard keyboard("Init");

    if (!READ8(decodeLV_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("Decode Level: %d", input);

    keyboard.SetMaxLength(2);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 0 && input <= 30) {
            if (!WRITE8(decodeLV_addr, input)) goto error;
            if (!WRITE32(decodeXP_addr, decodeLVXP[input])) goto error;
            MessageBox("Modification complete", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (0-30)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
    MessageBox("Error occured in write operation", DialogType::DialogOk, ClearScreen::Bottom)();
}

void mapDPAD2CStickFunc(MenuEntry *menu)
{
    if (Controller::IsKeyDown(CStickUp))
        Controller::InjectKey(DPadUp);
    if (Controller::IsKeyDown(CStickDown))
        Controller::InjectKey(DPadDown);
    if (Controller::IsKeyDown(CStickLeft))
        Controller::InjectKey(DPadLeft);
    if (Controller::IsKeyDown(CStickRight))
        Controller::InjectKey(DPadRight);
}

void enable60FPSFunc(MenuEntry *entry)
{
    static u32 FPS_addr= global_addr + 0x599D4;

    if (!entry->IsActivated())
    {
        WRITE8(FPS_addr, 2);
        return;
    }

    if (entry->WasJustActivated())
        WRITE8(FPS_addr, 1);
}

void setRunSpeedFunc(MenuEntry *entry)
{
    static u32 runSpeed_addr = code_addr + 0x360504;
    float tmp;

    if (!entry->IsActivated())
    {
        WRITEFLOAT(runSpeed_addr, 1.0f);
        return;
    }

    if (!READFLOAT(runSpeed_addr, tmp) || tmp == runSpeedMultiplier) return;
    WRITEFLOAT(runSpeed_addr, runSpeedMultiplier);
}

void setTrainingMultiFunc(MenuEntry *entry)
{
    static u32 trainingBoostDuration_addr = global_addr + 0x21C48;
    static u32 trainingBoostMultiplier_addr = global_addr + 0x21C4C;
    static u32 boostedStats_addr = global_addr + 0x21C50;
    static u32 maxBoostMultiplier_addr = code_addr + 0x4B5D0;

    if (!entry->IsActivated())
    {
        if (!WRITE32(trainingBoostDuration_addr, 0x0)) return;
        if (!WRITEFLOAT(trainingBoostMultiplier_addr, 0x0)) return;
        if (!WRITE8(boostedStats_addr, FLAG_NONE)) return;
        WRITEFLOAT(maxBoostMultiplier_addr, 2.f);
    }

    if (!WRITE32(trainingBoostDuration_addr, 150000)) return; // Duration value just needs to be > 1
    if (!WRITEFLOAT(trainingBoostMultiplier_addr, boostTrainingMultiplier)) return;
    if (!WRITE8(boostedStats_addr, FLAG_HP | FLAG_MP | FLAG_ATK | FLAG_DEF | FLAG_SPD | FLAG_BRN)) return; 
    WRITEFLOAT(maxBoostMultiplier_addr, boostTrainingMultiplier);


}

void enhanceRenderDistance(MenuEntry *entry)
{
    // Render Distance 1 is how far away until the event disappears from view
    // Render Distance 2 is how close until the event appears in view
    static u32 render1_addr = global_addr + 0x8118;
    static u32 render2_addr = global_addr + 0x811C;

    if (!entry->IsActivated())
    {
        if (!WRITEFLOAT(render1_addr, 250.f)) return;
        WRITEFLOAT(render2_addr, 125.f);
    }

    if (entry->WasJustActivated())
    {
        if (!WRITEFLOAT(render1_addr, 1000.f)) return;
        WRITEFLOAT(render2_addr, 1000.f);
    }

}

// Keyboards

void setMoneyKBFunc(MenuEntry *entry)
{
    Keyboard keyboard("Init");
    static u32 bit_addr = tamer_addr + 0x28;
    u32 input;

    if (!READ32(bit_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("Bit amount: %d", input);

    keyboard.SetMaxLength(7);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 0 && input <= 9999999)
        {
            money = input;
            g_setMoneyFunc->Enable();
        }
        else 
            MessageBox("Enter a value within the range of 0-9999999", DialogType::DialogOk, ClearScreen::Bottom)();
    }
    return;

    error:
    MessageBox("Error occured in transfer", DialogType::DialogOk, ClearScreen::Bottom)();
}

void setRunSpeedKBFunc(MenuEntry *entry)
{
    float input;

    Keyboard keyboard("Set run speed multiplier (ex. 1.5)");

    if (keyboard.Open(input) != -1)
    {
        runSpeedMultiplier = input;
        g_setRunSpeedFunc->Enable();
        MessageBox("Overclock applied!", DialogType::DialogOk, ClearScreen::Bottom)();
    }
    return;
}

void setTrainingMultiKBFunc(MenuEntry *entry)
{
    float input;

    Keyboard keyboard("Set training multiplier (ex. 3.5)");

    if (keyboard.Open(input) != -1)
    {
        boostTrainingMultiplier = input;
        g_setTrainingMultiFunc->Enable();
        MessageBox("Function Optimized Successfully", DialogType::DialogOk, ClearScreen::Bottom)();
    }
    return;
}

void maxKnownCards(MenuEntry *entry)
{
    static u32 cardBitmask_addr = tamer_addr + 0x23B8;
    static u32 cardQuantity_addr = tamer_addr + 0x36D4;
    u8 byte;

    if (MessageBox("Grant 99 of all currently discovered cards?", DialogType::DialogYesNo, ClearScreen::Both)())
    {
        for (int i = 0; i++, i < 588;)
        {
            if (!READ8(cardBitmask_addr, byte)) goto error;
            if (byte >> (((i+1) %8) & 1))
                if (!WRITE8(cardQuantity_addr + i, 99)) goto error;
        }
        MessageBox("Card data successfully unpacked!", DialogType::DialogOk, ClearScreen::Both)();
    }
    return;

    error:
        MessageBox("Fuzzing card data failed", DialogType::DialogOk, ClearScreen::Both)();
}
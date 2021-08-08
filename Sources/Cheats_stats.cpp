#include "Cheats.hpp"
#include "Types.h"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

void setMaxHPFunc(MenuEntry *entry)
{
    Keyboard keyboard("Init");

    static u32 maxHP_addr = digimon_addr + 0x24;
    u32 input;

    if (!READ32(maxHP_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("Max HP: %d", input);

    keyboard.SetMaxLength(5);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 1 && input <= 99999) {
            if (!WRITE32(maxHP_addr, input)) goto error;
            MessageBox("HP buffer altered successfully", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (1-99999)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error in accessing buffer", DialogType::DialogOk, ClearScreen::Bottom)();
}

void setMaxMPFunc(MenuEntry *entry)
{
    static u32 maxMP_addr = digimon_addr + 0x2C;
    u32 input;

    Keyboard keyboard("Init");

    if (!READ32(maxMP_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("Max MP: %d", input);

    keyboard.SetMaxLength(5);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 1 && input <= 99999) {
            if (!WRITE32(maxMP_addr, input)) goto error;
            MessageBox("MP cache altered successfully", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (1-99999)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error in accessing buffer", DialogType::DialogOk, ClearScreen::Bottom)();
}

void setATKFunc(MenuEntry *entry)
{
    static u32 ATK_addr = digimon_addr + 0x30;
    u16 input;

    Keyboard keyboard("Init");

    if (!READ16(ATK_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("ATK: %d", input);

    keyboard.SetMaxLength(3);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 1 && input <= 999) {
            if (!WRITE16(ATK_addr, input)) goto error;
            MessageBox("Brute force attack altered successfully", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (1-999)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error in effecting brute force ability", DialogType::DialogOk, ClearScreen::Bottom)();
}

void setDEFFunc(MenuEntry *entry)
{
    static u32 DEF_addr = digimon_addr + 0x32;
    u16 input;

    Keyboard keyboard("Init");

    if (!READ16(DEF_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("DEF: %d", input);

    keyboard.SetMaxLength(3);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 1 && input <= 999) {
            if (!WRITE16(DEF_addr, input)) goto error;
            MessageBox("Firewall capability altered successfully", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (1-999)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error in effecting firwall", DialogType::DialogOk, ClearScreen::Bottom)();
}

void setSPDFunc(MenuEntry *entry)
{
    static u32 SPD_addr = digimon_addr + 0x34;
    u16 input;

    Keyboard keyboard("Init");

    if (!READ16(SPD_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("SPD: %d", input);

    keyboard.SetMaxLength(3);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 1 && input <= 999) {
            if (!WRITE16(SPD_addr, input)) goto error;
            MessageBox("Clock speed tuned successfully", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (1-999)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error in tuning clock speed", DialogType::DialogOk, ClearScreen::Bottom)();
}

void setBRNFunc(MenuEntry *entry)
{
    static u32 BRN_addr = digimon_addr + 0x36;
    u16 input;

    Keyboard keyboard("Init");

    if (!READ16(BRN_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("BRN: %d", input);

    keyboard.SetMaxLength(3);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 1 && input <= 999) {
            if (!WRITE16(BRN_addr, input)) goto error;
            MessageBox("Processing power adjusted successfully", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (1-999)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error in adjusting processing power", DialogType::DialogOk, ClearScreen::Bottom)();
}
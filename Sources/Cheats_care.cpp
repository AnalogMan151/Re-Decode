#include "Cheats.hpp"
#include "Types.h"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

// Freezes life and evolution timer to post-pone evolution and death
void freezeDigimonFunc(MenuEntry *entry)
{
    static u32 lifetime_addr = digimon_addr + 0x55C;
    static u64 lifetime_evolution;

    if (entry->WasJustActivated())
        READ64(lifetime_addr, lifetime_evolution);

    WRITE64(lifetime_addr, lifetime_evolution);
}

// Freezes sleep timer to post-pone bed time
void freezeSleepFunc(MenuEntry *entry)
{
    static u32 sleepTimer_addr = digimon_addr + 0x510;
    static u32 timer;

    if (entry->WasJustActivated())
        if (!READ32(sleepTimer_addr, timer)) return;
    
    WRITE32(sleepTimer_addr, timer);
}

// Sets isHungry flag to 0 and sets fullness to 1 for infinite feeding.
void freezeHungerFunc(MenuEntry *entry)
{
    static u32 hunger_addr = digimon_addr + 0x538;

    WRITE16(hunger_addr, 1);
}

// Sets hastoPoop flag to 0 and sets Digested value to 0
void freezePoopFunc(MenuEntry *entry)
{
    static u32 poop_addr = digimon_addr + 0x548;

    WRITE16(poop_addr, 0);
}


// Sets exhaustion amount to 0 for infninite training
void neverExhaustedFunc(MenuEntry *entry)
{
    static u32 exhaustion_addr = digimon_addr + 0x530;

    WRITE16(exhaustion_addr, 0);
}


// Sets health status flag to 0 to clear Sickness or Injury
void neverUnhealthyFunc(MenuEntry *entry)
{
    static u32 healthStatus_addr = digimon_addr + 0x518;

    // (0:None, 1:Injured, 2:Sick)
    WRITE8(healthStatus_addr, 0);
}

// Sets Lives to 3
void maxLivesFunc(MenuEntry *entry)
{
    static u32 lives_addr = digimon_addr + 0x3D;

    WRITE8(lives_addr, 3);
}

// Changes nature of your Digimon with keyboard input
void setNatureFunc(MenuEntry *entry)
{
    static u32 nature_addr = digimon_addr + 0x3C;
    int choice;

    Keyboard keyboard("Select Nature");
    keyboard.Populate({"Lively", "Brave", "Hardy", "Relaxed", "Clever", 
                       "Quiet", "Calm", "Strategist", "Timid", "Combi A", 
                       "Combi B", "Schemer", "Burst", "Build", "Crafty"});
    choice = keyboard.Open();
    if (choice == -1) return;
    if (!WRITE8(nature_addr, choice)) goto error;
    MessageBox("Nature set successfully", DialogType::DialogOk, ClearScreen::Bottom)();
    return;

    error:
        MessageBox("Nature could not be changed!", DialogType::DialogOk, ClearScreen::Bottom)();
}

// Set amount of discipline from 0-100% with keyboard input
void setDisciplineMeterFunc(MenuEntry *entry)
{
    static u32 discipline_addr = digimon_addr + 0x44;
    float inputf;
    u8 input;

    Keyboard keyboard("Init");

    if (!READFLOAT(discipline_addr, inputf)) goto error;

    keyboard.GetMessage() = Utils::Format("Discipline Meter: %d", (u32)inputf);

    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 0 && input <= 100) {
            if (!WRITEFLOAT(discipline_addr, (float)input)) goto error;
            MessageBox("Discipline adjusted", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (0 - 100)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error injecting obedience", DialogType::DialogOk, ClearScreen::Bottom)();
}

// Set amount of happiness from 0-100% with keyboard input
void setHappinessMeterFunc(MenuEntry *entry)
{
    static u32 happiness_addr = digimon_addr + 0x40;
    float inputf;
    u8 input;

    Keyboard keyboard("Init");

    if (!READFLOAT(happiness_addr, inputf)) goto error;

    keyboard.GetMessage() = Utils::Format("Happiness Meter: %d", (u32)inputf);

    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 0 && input <= 100) {
            if (!WRITEFLOAT(happiness_addr, (float)input)) goto error;
            MessageBox("Happiness adjusted", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (0 - 100)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
     MessageBox("Error injecting Serotonin", DialogType::DialogOk, ClearScreen::Bottom)();
}

// Sets amount of times poop accidents have occured with keyboard input
void setPoopMeterFunc(MenuEntry *entry)
{
    static u32 poopMeter_addr = digimon_addr + 0x48;
    u8 input;

    Keyboard keyboard("Init");

    if (!READ8(poopMeter_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("Poop Meter: %d", input);

    keyboard.SetMaxLength(2);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 0 && input <= 16) {
            if (!WRITE8(poopMeter_addr, input)) goto error;
            MessageBox("Corruption adjusted", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (0-16)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error in handling corruption", DialogType::DialogOk, ClearScreen::Bottom)();
}

// Sets weight value of Digimon with keyboard input
void setWeightFunc(MenuEntry *entry)
{
    static u32 weight_addr = digimon_addr + 0x38;
    u8 input;
    u8 weight;

    Keyboard keyboard("Init");

    if (!READ8(weight_addr, weight)) goto error;

    keyboard.GetMessage() = Utils::Format("Weight: %d", weight);

    keyboard.SetMaxLength(2);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 0 && input <= 99) {
            if (!WRITE8(weight_addr, input)) goto error;
            if (input > weight)
                MessageBox("Decompression complete", DialogType::DialogOk, ClearScreen::Bottom)();
            else if (input < weight)
                MessageBox("Compression complete", DialogType::DialogOk, ClearScreen::Bottom)();
            else
                MessageBox("Size unchanged", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (0-99)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error occured in (de)compressing", DialogType::DialogOk, ClearScreen::Bottom)();
}

// Sets the number of care mistakes with keyboard input
void setCareMistakeFunc(MenuEntry *entry)
{
    static u32 careMistakes_addr = digimon_addr + 0x53C;
    u8 input;

    Keyboard keyboard("Init");

    if (!READ8(careMistakes_addr, input)) goto error;

    keyboard.GetMessage() = Utils::Format("Care Mistakes: %d", input);

    keyboard.SetMaxLength(2);
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(input) != -1)
    {
        if (input >= 0 && input <= 20) {
            if (!WRITE8(careMistakes_addr, input)) goto error;
            MessageBox("Memory altered successfully", DialogType::DialogOk, ClearScreen::Bottom)();
        } else {
            MessageBox("Invalid input (0-20)", DialogType::DialogOk, ClearScreen::Bottom)();
        }
    }
    return;

    error:
        MessageBox("Error in handling corruption", DialogType::DialogOk, ClearScreen::Bottom)();
}

// Sets Digivolve timer to 0 to trigger a digivolve. If no digivolve requirements are met nothing will happen.
void instantDigivolveFunc(MenuEntry *entry)
{
    static u32 evolutionTimer_addr = digimon_addr + 0x560;
    if (entry->Hotkeys[0].IsDown())
        WRITE32(evolutionTimer_addr, 0);
}

// Sets life timer to 0 to instantly have Digmon die
void killDigimonFunc(MenuEntry *entry)
{
    static u32 lifetime_addr = digimon_addr + 0x55C;

    bool answer = MessageBox("Kill Partner", "Are you sure?", DialogType::DialogYesNo, ClearScreen::Both)();

    if (answer) {
        if (WRITE32(lifetime_addr, 0))
            MessageBox("Operation complete", DialogType::DialogOk, ClearScreen::Both)();
        else
            MessageBox("Assassination failed!", DialogType::DialogOk, ClearScreen::Both)();
    }
}
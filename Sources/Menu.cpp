#include "Menu.hpp"
#include "Cheats.hpp"
#include "Unicode.h"
#include "Helpers.hpp"

MenuEntry *g_setMoneyFunc = Entry("Freeze Bits [KB]", setMoneyFunc, setMoneyKBFunc);
MenuEntry *g_setRunSpeedFunc = Entry("Change Run Speed [KB]", setRunSpeedFunc, setRunSpeedKBFunc);
MenuEntry *g_setTrainingMultiFunc = Entry("Set Training Multiplier [KB]", setTrainingMultiFunc, setTrainingMultiKBFunc);
MenuEntry *g_setAnimationSpeedFunc = Entry("Change Game Animation Speed [KB]", "Time passes as normal, only animations are sped up", setAnimationSpeedFunc, setAnimationSpeedKBFunc);

using namespace CTRPluginFramework;

void InitMenu(PluginMenu &Menu)
{
    if (!IsOnWhiteList() || static_cast<u32>(Process::GetTitleID()) != 0x000AFC00)
    {
        Menu += Entry("Access Denied: Unauthorized User", nullptr);
        return;
    }
    
    MenuFolder *QoL = new MenuFolder("Convenience Patches");
    *QoL += g_setMoneyFunc;
    if (System::IsNew3DS())
    {
        *QoL += Entry("Map C-Stick to D-Pad", mapDPAD2CStickFunc);
        *QoL += Entry("Enable 60 FPS (See Note)", "Unstable, may crash during video scenes", enable60FPSFunc);
    }
    *QoL += Entry("Increase Render Distance x4", enhanceRenderDistance);
    *QoL += g_setRunSpeedFunc;
    *QoL += g_setTrainingMultiFunc;
    *QoL += Entry("Max Card Quantities", "Only changes amount for discovered cards", nullptr, maxKnownCards);
    *QoL += Entry("Hack Decode Level", nullptr, setDecodeLVLFunc);
    Menu += QoL;

    MenuFolder *Battle = new MenuFolder("Battle Hacks");
    *Battle += Entry("Infinite HP", infHPBattleFunc);
    *Battle += Entry("Infinite MP", infMPBattleFunc);
    *Battle += Entry("Infinite SP", infSPBattleFunc);
    *Battle += EntryWithHotkey("Enemy Instant Death (See Note)", "Okay, what was that??\nDeath.\nWhat kind?\nInstant.\nThere was no sound, he just died!", instantEnemyDeathFunc, { Hotkey(Key::L + Key::R, "Instant Death") });
    *Battle += Entry("One-Hit KO", oneHitKOFunc);
    *Battle += Entry("Enemy has no MP", enemyNoMPFunc);
    Menu += Battle;

    MenuFolder *Stats = new MenuFolder("Stat Adjustments");
    *Stats += Entry("Set Max HP", nullptr, setMaxHPFunc);
    *Stats += Entry("Set Max MP", nullptr, setMaxMPFunc);
    *Stats += Entry("Set ATK", nullptr, setATKFunc);
    *Stats += Entry("Set DEF", nullptr, setDEFFunc);
    *Stats += Entry("Set SPD", nullptr, setSPDFunc);
    *Stats += Entry("Set BRN", nullptr, setBRNFunc);
    Menu += Stats;

    MenuFolder *Care = new MenuFolder("Care Modifiers");
    *Care += Entry("Freeze Sleep", freezeSleepFunc);
    *Care += Entry("Freeze Hunger & Fullness", freezeHungerFunc);
    *Care += Entry("Freeze Poop", freezePoopFunc);
    *Care += Entry("Never Exhausted", neverExhaustedFunc);
    *Care += Entry("Never Sick/Injured", neverUnhealthyFunc);
    *Care += Entry("Max Lives", maxLivesFunc);
    *Care += Entry("Freeze Digimon Aging", "Also stops digivolution", freezeDigimonFunc);
    *Care += EntryWithHotkey("Instant Digivolve (See Note)", instantDigivolveFunc, { Hotkey(Key::L + Key::R + Key::A, "Instant Digivolve") });
    *Care += Entry("Set Happiness Meter", nullptr, setHappinessMeterFunc);
    *Care += Entry("Set Discipline Meter", nullptr, setDisciplineMeterFunc);
    *Care += Entry("Set Poop Meter", nullptr, setPoopMeterFunc);
    *Care += Entry("Set Weight", nullptr, setWeightFunc);
    *Care += Entry("Set Nature", nullptr, setNatureFunc);
    *Care += Entry("View/Edit Care Mistakes", nullptr, setCareMistakeFunc);
    *Care += Entry("Kill Partner Digimon", nullptr, killDigimonFunc);
    Menu += Care;

    MenuFolder *Unlock = new MenuFolder("Unlockables");
    *Unlock += Entry("Complete Evolution List", nullptr, unlockFieldGuideFunc);
    *Unlock += Entry("Unlock All Accessories", nullptr, unlockAccessoriesFunc);
    *Unlock += Entry("Learn All Skills", nullptr, unlockSkillsFunc);
    *Unlock += Entry("Reveal All Cards", "This only unlocks the card for viewing, doesn't grant any amount of the card", nullptr, unlockAllCardsFunc);
    Menu += Unlock;

    MenuFolder *Fun = new MenuFolder("Fun Mods");
    if (System::IsNew3DS())
        *Fun += EntryWithHotkey("Alter Camera Zoom (See Note)", controlCameraZoom, { Hotkey(Key::ZL, "Zoom In"), Hotkey(Key::ZR, "Zoom Out") });
    else
        *Fun += EntryWithHotkey("Alter Camera Zoom (See Note)", controlCameraZoom, { Hotkey(Key::L + Key::R + Key::DPadLeft, "Zoom In"), Hotkey(Key::L + Key::R + Key::DPadRight, "Zoom Out") });
    *Fun += g_setAnimationSpeedFunc;
    *Fun += Entry("Override Player Character", nullptr, choosePlayerFunc);
    *Fun += Entry("Change Player Name", nullptr, setPlayerNameKBFunc);
    *Fun += Entry("Change Partner Name", nullptr, setDigiNameKBFunc);
    *Fun += Entry("Change Partner", nullptr, replacePartnerDigimonFunc);
    Menu += Fun;

    Menu += Entry("Additional Info", "Save often. While tested it's better safe than sorry.\n\n"
                                     "Entries with [KB] can be customized with the keyboard icon.\n\n"
                                     "Some cheats require loading a save, read the message boxes to know which ones.\n\n"
                                     "Cheats with hot keys can have the keys changed with the gamepad icon.");
}
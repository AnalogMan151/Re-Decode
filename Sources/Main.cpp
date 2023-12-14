#include <CTRPluginFramework.hpp>
#include <3ds.h>
#include "CSVC.h"
#include <vector>
#include "Menu.hpp"

/* Beta Tester Whitelist */
std::vector<std::string> approvedCodes =
{
    
};

std::string about = "Cheat plugin for Digimon World RE:Digitize: Decode\n"
                       "Infiltrated by AnalogMan\n\n"
                       "Special thanks to Team Operation Decoded for their English translation, without which I would not be able to fully enjoy this game.\n"
                       "Additional extra thanks to Romsstar and SydMontague for being friendly and helping me break through the the Digital World's defenses yet again (those fools!).\n\n"
                       "One more mention: I fully blame Jared#0199 on Discord for the ridiculous crunch I put into this plugin for without them I would not have been motivated enough to get back into 3DS development.\n\n"
                       "Please enjoy wreaking havoc over these 1's and 0's.";

namespace CTRPluginFramework
{
    // This function is called on the plugin starts, before main
    void PatchProcess(FwkSettings &Settings)
    {
        // Customize the general interface
        Settings.AllowActionReplay = true;
        Settings.AllowSearchEngine = true;
        Settings.TryLoadSDSounds = false;

        Settings.MainTextColor = Color(Color::White);
        Settings.WindowTitleColor = Color(Color::White);;
        Settings.MenuSelectedItemColor = Color(Color::White);
        Settings.MenuUnselectedItemColor = Color(Color::White);;
        Settings.BackgroundMainColor = Color(0x2E2F35FF);
        Settings.BackgroundSecondaryColor = Color(0x252A3BFF);
        Settings.BackgroundBorderColor = Color(0x4C567FFF);
        Settings.CursorFadeValue = -0.3f;
        
        // Input keyboard customization
        Settings.Keyboard.Background = Color(0x2E2F35FF);
        Settings.Keyboard.KeyBackground = Color(0x2E2F35FF);
        Settings.Keyboard.KeyBackgroundPressed = Settings.Keyboard.KeyBackground.Blend(Color(0xFF1A697F), Color::BlendMode::Alpha).Fade(.1f);;
        Settings.Keyboard.KeyText = Color(Color::White);
        Settings.Keyboard.KeyTextPressed = Color(Color::White);
        Settings.Keyboard.KeyTextDisabled = Color(0x2E2F35FF);
        Settings.Keyboard.Cursor = Color(Color::White);
        Settings.Keyboard.Input = Color(Color::White);
        
        // List keyboard customization
        Settings.CustomKeyboard.BackgroundMain = Color(0x2E2F35FF);
        Settings.CustomKeyboard.BackgroundSecondary = Color(0x252A3BFF);
        Settings.CustomKeyboard.BackgroundBorder = Color(0x4C567FFF);
        Settings.CustomKeyboard.KeyBackground = Color(0x313341FF);
        Settings.CustomKeyboard.KeyBackgroundPressed = Settings.CustomKeyboard.KeyBackground.Blend(Color(0xFF1A697F), Color::BlendMode::Alpha).Fade(.1f);;
        Settings.CustomKeyboard.KeyText = Color(Color::White);
        Settings.CustomKeyboard.KeyTextPressed = Color(Color::White);
        Settings.CustomKeyboard.ScrollBarBackground = Color(0x0F0F10FF);
        Settings.CustomKeyboard.ScrollBarThumb = Color(0x0546AFFF);
    }

    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void    OnProcessExit(void)
    {

    }
    
    int main(void)
    {	
        PluginMenu *Menu = new PluginMenu("Re:Decode", 1, 2, 0, about);

        Menu->ShowWelcomeMessage(false);
        Menu->SynchronizeWithFrame(true);
        Menu->SetHexEditorState(true);
        
        InitMenu(*Menu);
        
        Menu->Run();
        delete Menu;
        return (0);
    }
}
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
    void PatchProcess(FwkSettings &Settings)
    {
		// Customize the general interface
		Settings.AllowActionReplay = true;
		Settings.AllowSearchEngine = true;
	}

    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void    OnProcessExit(void)
    {

    }
	
    int main(void)
    {	
		PluginMenu *Menu = new PluginMenu("Re:Decode", 1, 0, 0, about);

		Menu->ShowWelcomeMessage(false);
		Menu->SynchronizeWithFrame(true);
		Menu->SetHexEditorState(true);
		
        InitMenu(*Menu);
		
		Menu->Run();
		delete Menu;
        return (0);
    }
}
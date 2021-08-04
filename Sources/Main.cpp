#include "CTRPluginFramework.hpp"
#include <3ds.h>
#include "CSVC.h"
#include <vector>
#include "Menu.hpp"

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
		PluginMenu *Menu = new PluginMenu("Re:Decode", 0, 1, 0, "Cheat plugin for Digimon World Re:Digitize: Decode");

		Menu->ShowWelcomeMessage(false);
		Menu->SynchronizeWithFrame(true);
		Menu->SetHexEditorState(true);
		
        InitMenu(*Menu);
		
		Menu->Run();
		delete Menu;
        return (0);
    }
}
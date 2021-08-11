#include "Cheats.hpp"
#include "Types.h"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

extern MenuEntry *g_setAnimationSpeedFunc;
static float animationSpeedMultiplier = 1.5f;
enum genders { male, female };

// Changes speed at which animations play. Does not affect in-game clock or Digimon timers
void setAnimationSpeedFunc(MenuEntry *entry)
{
    static u32 animationSpeed_addr = code_addr + 0x885C;
    float tmp;

    if (!entry->IsActivated()) 
    {
        WRITEFLOAT(animationSpeed_addr, 5.0f);
        return;
    }

    if (!READFLOAT(animationSpeed_addr, tmp) || tmp == 5.0f * animationSpeedMultiplier) return;
    WRITEFLOAT(animationSpeed_addr, 5.0f * animationSpeedMultiplier);
}

// Adjusts camera's zoom and height to allow further control
void controlCameraZoom(MenuEntry *entry)
{
    static u32 zoom_addr = camera_addr + 0xE4;
    static u32 camY_addr = camera_addr + 0xDC;
    float zoom;
    float camY;

    // X pos default: 10.0f
    // Y pos default: 11.5f
    // Z pos default: 0.0f
    // Zoom default: 40.0f
    // Min Yaw default: -0.112739f (looking up at sky)
    // Max Yaw default: 0.239791f (looking down at ground)

    // Resets camera to default when cheat is disabled
    if (!entry->IsActivated())
    {
        WRITEFLOAT(zoom_addr, 40.f);
        WRITEFLOAT(camY_addr, 11.5f);
        return;
    }

    if (entry->Hotkeys[0].IsDown())
    {
        if (!READFLOAT(zoom_addr, zoom)) goto error;
        if (!READFLOAT(camY_addr, camY)) goto error;

        // Set limit to how close the camera gets
        if (zoom <= 28.f) return;
        if (!WRITEFLOAT(zoom_addr, zoom - 2.f)) goto error;
        if (!WRITEFLOAT(camY_addr, camY - .6f)) goto error;

    }
    if (entry->Hotkeys[1].IsDown())
    {
        if (!READFLOAT(zoom_addr, zoom)) goto error;
        if (!READFLOAT(camY_addr, camY)) goto error;

        // Set limit to how far the camera gets
        if (zoom >= 300.f) return;
        if (!WRITEFLOAT(zoom_addr, zoom + 2.f)) goto error;
        if (!WRITEFLOAT(camY_addr, camY + .6f)) goto error;
    }
    return;

    error:
        MessageBox("Could not hijack surveillance systems", DialogType::DialogOk, ClearScreen::Both)();
}

// Swaps player model texture with various NPC textures. Requires a reload of the save to apply.
void choosePlayerFunc(MenuEntry *menu)
{
    static u32 playerChar_addr = global_addr + 0x204BC;
    static u32 tiagaModel_addr = readonly_addr + 0xCD8;
    static u32 rinaModel_addr = readonly_addr + 0xD48;

    Keyboard keyboard("Select Character");
    keyboard.Populate({"Taiga", "Rina", "Lili", "Ahiko", "Niko", "Yuuya", "Mirei", "Dr. Petrov"});
    int input = keyboard.Open();
    switch(input) 
    {
        case 0:
            // Taiga was selected
            if (!WRITE8(playerChar_addr, male)) goto error;
            if (!WRITESTRING(tiagaModel_addr, std::string("Tamer/pc01.res\0", 15))) goto error;
            break;
        case 1:
            // Rina was selected
            if (!WRITE8(playerChar_addr, female)) goto error;
            if (!WRITESTRING(rinaModel_addr, std::string("Tamer/pc02.res\0", 15))) goto error;
            break;
        case 2:
            // Lili was selected
            if (!WRITE8(playerChar_addr, female)) goto error;
            if (!WRITESTRING(rinaModel_addr, "Tamer/Npc10.res")) goto error;
            break;
        case 3:
            // Ahiko was selected
            if (!WRITE8(playerChar_addr, female)) goto error;
            if (!WRITESTRING(rinaModel_addr, "Tamer/Npc01.res")) goto error;
            break;
        case 4:
            // Niko was selected
            if (!WRITE8(playerChar_addr, male)) goto error;
            if (!WRITESTRING(tiagaModel_addr, "Tamer/Npc02.res")) goto error;
            break;
        case 5:
            // Yuuya was selected
            if (!WRITE8(playerChar_addr, male)) goto error;
            if (!WRITESTRING(tiagaModel_addr, "Tamer/Npc03.res")) goto error;
            break;
        case 6:
            // Mirei was selected
            if (!WRITE8(playerChar_addr, female)) goto error;
            if (!WRITESTRING(rinaModel_addr, "Tamer/Npc04.res")) goto error;
            break;
        case 7:
            // Dr. Petrov was selected
            if (!WRITE8(playerChar_addr, male)) goto error;
            if (!WRITESTRING(tiagaModel_addr, "Tamer/Npc05.res")) goto error;
            break;
        case -1:
        default:
            //  User cancelled
            return;   
    }

    MessageBox("Identity Overridden Successfully!\nSave and reload.", DialogType::DialogOk, ClearScreen::Both)();
    return;

    error:
        MessageBox("Identity Theft Failed!", DialogType::DialogOk, ClearScreen::Both)();
}

// Changes Partner Digimon's nickname
void setDigiNameKBFunc(MenuEntry *entry)
{
    std::string input;

    Keyboard keyboard("Init");

    if (!READSTRING(digimon_addr, input, 16, StringFormat::Utf16)) goto error;

    keyboard.GetMessage() = "Digimon Name: " + input;

    keyboard.SetMaxLength(8);
    if (keyboard.Open(input) != -1)
    {
        if (!Process::WriteString(digimon_addr, std::string(8,'\0'), StringFormat::Utf16)) goto error;
        if (!Process::WriteString(digimon_addr, input, StringFormat::Utf16)) goto error;
        MessageBox("ID hijacked successfully", DialogType::DialogOk, ClearScreen::Bottom)();
    }
    return;

    error:
    MessageBox("Error forging name", DialogType::DialogOk, ClearScreen::Bottom)();
}

// Changes player characters nickname
void setPlayerNameKBFunc(MenuEntry *entry)
{
    std::string input;

    Keyboard keyboard("Init");

    if (!READSTRING(tamer_addr, input, 16, StringFormat::Utf16)) goto error;

    keyboard.GetMessage() = "Player Name: " + input;

    keyboard.SetMaxLength(8);
    if (keyboard.Open(input) != -1)
    {
        if (!Process::WriteString(tamer_addr, std::string(8,'\0'), StringFormat::Utf16)) goto error;
        if (!Process::WriteString(tamer_addr, input, StringFormat::Utf16)) goto error;
        MessageBox("ID hijacked successfully", DialogType::DialogOk, ClearScreen::Bottom)();
    }
    return;

    error:
    MessageBox("Error forging name", DialogType::DialogOk, ClearScreen::Bottom)();
}

// Keyboard function to work in conjunction with setAnimationSpeedFunc()
void setAnimationSpeedKBFunc(MenuEntry *entry)
{
    float input;

    Keyboard keyboard("Set animation speed multiplier (ex. 1.5)");

    if (keyboard.Open(input) != -1)
    {
        animationSpeedMultiplier = input;
        g_setAnimationSpeedFunc->Enable();
        MessageBox("Turbo mode activated!", DialogType::DialogOk, ClearScreen::Bottom)();
    }
    return;
}

// String Vector list of all Digimon and their IDs separated into their evoluition groups
const std::vector<DigimonList> freshOptions =
{
    { "Dodomon", 1 },
    { "Botamon", 2 },
    { "Jarimon", 3 },
    { "Yuramon", 4 },
    { "Poyomon", 5 },
    { "Pabumon", 195 },
    { "Punimon", 244 }
};

const std::vector<DigimonList> inTrainingOptions =
{
    { "Wanyamon", 6 },
    { "Koromon", 7 },
    { "Gigimon", 8 },
    { "Budmon", 9 },
    { "Tokomon", 10 },
    { "Motimon", 196 },
    { "Tsunomon", 245 }
};

const std::vector<DigimonList> rookieOptions = 
{
    { "Agumon", 15 },
    { "Impmon", 20 },
    { "Gaomon", 18 },
    { "Gabumon", 31 },
    { "Kamemon", 16 },
    { "Candlemon", 12 },
    { "Guilmon", 21 },
    { "Gomamon", 152 },
    { "Chuumon", 13 },
    { "Tentomon", 35 },
    { "Dorumon", 27 },
    { "Hagurumon", 11 },
    { "Patamon", 22 },
    { "Palmon", 157 },
    { "DemiDevimon", 23 },
    { "Biyomon", 36 },
    { "Veemon", 28 },
    { "Salamon", 170 },
    { "Betamon", 197 },
    { "Lalamon", 19 },
    { "Lucemon", 198 },
    { "Renamon", 199 },
    { "Wormmon", 200 },
    { "BlackAgumon", 30 },
    { "BlackGabumon", 24 },
    { "Tsukaimon", 14 },
    { "Psychemon", 25 },
    { "SnowAgumon", 29 },
    { "Solarmon", 33 },
    { "Goburimon", 26 }
};

const std::vector<DigimonList> championOptions = 
{
    { "Ikkakumon", 153 },
    { "Woodmon", 201 },
    { "Airdramon", 38 },
    { "ExVeemon", 174 },
    { "Angemon", 54 },
    { "Ogremon", 202 },
    { "Guardromon", 150 },
    { "Gaogamon", 49 },
    { "Kabuterimon", 66 },
    { "Garurumon", 39 },
    { "Kyubimon", 203 },
    { "Growlmon", 53 },
    { "Greymon", 70 },
    { "Kuwagamon", 176 },
    { "Centarumon", 181 },
    { "Sunflowmon", 48 },
    { "Seadramon", 156 },
    { "GeoGreymon", 47 },
    { "Sukamon", 68 },
    { "Stingmon", 82 },
    { "Tyrannomon", 172 },
    { "Gatomon", 56 },
    { "Devimon", 57 },
    { "Togemon", 158 },
    { "Dorugamon", 204 },
    { "Numemon", 50 },
    { "Birdramon", 67 },
    { "Bakemon", 40 },
    { "Veedramon", 205 },
    { "Vegiemon", 69 },
    { "Meramon", 37 },
    { "Leomon", 51 },
    { "BlackGarurumon", 61 },
    { "Gururumon", 62 },
    { "Growlmon (Orange)", 55 },
    { "BlackGrowlmon", 58 },
    { "IceDevimon", 59 },
    { "Geremon", 63 },
    { "BlackGatomon", 45 }
};

const std::vector<DigimonList> ultimateOptions = 
{
    { "MegaKabuterimon", 99 },
    { "Andromon", 151 },
    { "Myotismon", 81 },
    { "AeroVeedramon", 208 },
    { "Etemon", 101 },
    { "Angewomon", 90 },
    { "Okuwamon", 209 },
    { "Garudamon", 100 },
    { "Gigadramon", 210 },
    { "GrapLeomon", 211 },
    { "Cherrymon", 188 },
    { "SkullGreymon", 212 },
    { "Zudomon", 154 },
    { "Taomon", 213 },
    { "Digitamamon", 183 },
    { "SkullMeramon", 214 },
    { "DoruGreymon", 215 },
    { "Paildramon", 216 },
    { "IceLeomon", 217 },
    { "Piximon", 218 },
    { "BlueMeramon", 91 },
    { "Vademon", 219 },
    { "MagnaAngemon", 83 },
    { "MachGaogamon", 77 },
    { "Mamemon", 220 },
    { "MegaSeadramon", 85 },
    { "Megadramon", 97 },
    { "WarGrowlmon", 87 },
    { "MetalGreymon", 98 },
    { "MetalTyrannomon", 173 },
    { "MetalMamemon", 221 },
    { "Monzaemon", 74 },
    { "RizeGreymon", 75 },
    { "Lilamon", 76 },
    { "Lillymon", 168 },
    { "Lucemon FM", 72 },
    { "LadyDevimon", 84 },
    { "WereGarurumon", 89 },
    { "WaruMonzaemon", 190 },
    { "MetalGreymon (Virus)", 142 },
    { "B-WarGrowlmon", 88 },
    { "WarGrowlmon (Orange)", 95 },
    { "B-WereGarurumon", 92 }
};

const std::vector<DigimonList> megaOptions = 
{
    { "Alphamon", 224 },
    { "UlforceVeedramon", 225 },
    { "UlforceVeedramon X", 226 },
    { "Imperialdramon FM", 227 },
    { "Imperialdramon PM", 228 },
    { "Vikemon", 155 },
    { "WarGreymon", 103 },
    { "WarGreymon X", 120 },
    { "Examon", 136 },
    { "Ophanimon", 229 },
    { "Omegamon", 116 },
    { "Omegamon X", 166 },
    { "Chaosdramon", 230 },
    { "Chaosmon", 110 },
    { "GrandKuwagamon", 231 },
    { "SaberLeomon", 232 },
    { "Sakuyamon", 233 },
    { "ShineGreymon", 117 },
    { "ZeedGarurumon", 131 },
    { "Seraphimon", 141 },
    { "Darkdramon", 111 },
    { "Titamon", 247 },
    { "Gallantmon", 121 },
    { "Gallantmon X", 167 },
    { "Hi-Andromon", 234 },
    { "Barbamon", 106 },
    { "BanchoLeomon", 112 },
    { "Piedmon", 235 },
    { "VictoryGreymon", 132 },
    { "Puppetmon", 236 },
    { "PlatinumNumemon", 114 },
    { "PrinceMamemon", 237 },
    { "HerculesKabuterimon", 138 },
    { "Beelzemon", 105 },
    { "Beelzemon X", 238 },
    { "Phoenixmon", 139 },
    { "Boltmon", 239 },
    { "Magnamon", 191 },
    { "Magnamon X", 240 },
    { "MarineAngemon", 102 },
    { "MirageGaogamon", 118 },
    { "Machinedramon", 194 },
    { "MetalEtemon", 140 },
    { "MetalGarurumon", 122 },
    { "MetalSeadramon", 242 },
    { "RustTyrannomon", 192 },
    { "Lilithmon", 104 },
    { "Rosemon", 113 },
    { "Rosemon X", 161 },
    { "BlackWarGreymon", 124 },
    { "ChaosGallantmon", 123 },
    { "BlackMetalGarurumon", 125 },
    { "BlackWarGreymon X", 148 }
};

// Keyboard that lists all the digimon and writes target EVO value and evolution action to trigger a forced evolution
void replacePartnerDigimonFunc(MenuEntry *entry)
{
    static u32 evoTarget_addr = global_addr + 0x23170;
    static u32 action_addr = global_addr + 0x8B20;
    StringVector options;
    int choice;
    int input;

    Keyboard keyboard("Select Group");
    keyboard.Populate({"Fresh", "In-Training", "Rookie", "Champion", "Ultimate", "Mega"});
    input = keyboard.Open();
    keyboard.GetMessage() = "Select Digimon";
    switch(input) 
    {
        case 0:
            // Fresh was selected
            if (options.empty())
                for (const DigimonList &m : freshOptions)
                    options.push_back(m.name);
            keyboard.Populate(options);
            choice = keyboard.Open();

            if (choice >= 0) {
                bool answer = MessageBox(Utils::Format("Are you sure you want %s?", freshOptions[choice].name), DialogType::DialogYesNo, ClearScreen::Bottom)();
                if (!answer) return;
                if (!WRITE32(evoTarget_addr, freshOptions[choice].id)) goto error;
                if (!WRITE8(action_addr, EVOLVE)) goto error;
            }
            break;
        case 1:
            // In-Training was selected
            if (options.empty())
                for (const DigimonList &m : inTrainingOptions)
                    options.push_back(m.name);            

            keyboard.Populate(options);
            choice = keyboard.Open();

            if (choice >= 0) {
                bool answer = MessageBox(Utils::Format("Are you sure you want %s?", inTrainingOptions[choice].name), DialogType::DialogYesNo, ClearScreen::Bottom)();
                if (!answer) return;
                if (!WRITE32(evoTarget_addr, inTrainingOptions[choice].id)) goto error;
                if (!WRITE8(action_addr, EVOLVE)) goto error;
            }
            break;
        case 2:
            // Rookie was selected
            if (options.empty())
                for (const DigimonList &m : rookieOptions)
                    options.push_back(m.name);

            keyboard.Populate(options);
            choice = keyboard.Open();

            if (choice >= 0) {
                bool answer = MessageBox(Utils::Format("Are you sure you want %s?", rookieOptions[choice].name), DialogType::DialogYesNo, ClearScreen::Bottom)();
                if (!answer) return;
                if (!WRITE32(evoTarget_addr, rookieOptions[choice].id)) goto error;
                if (!WRITE8(action_addr, EVOLVE)) goto error;
            }
            break;
        case 3:
            // Champion was selected
            if (options.empty())
                for (const DigimonList &m : championOptions)
                    options.push_back(m.name);

            keyboard.Populate(options);
            choice = keyboard.Open();

            if (choice >= 0) {
                bool answer = MessageBox(Utils::Format("Are you sure you want %s?", championOptions[choice].name), DialogType::DialogYesNo, ClearScreen::Bottom)();
                if (!answer) return;
                if (!WRITE32(evoTarget_addr, championOptions[choice].id)) goto error;
                if (!WRITE8(action_addr, EVOLVE)) goto error;
            }
            break;
        case 4:
            // Ultimate was selected
            if (options.empty())
                for (const DigimonList &m : ultimateOptions)
                    options.push_back(m.name);

            keyboard.Populate(options);
            choice = keyboard.Open();

            if (choice >= 0) {
                bool answer = MessageBox(Utils::Format("Are you sure you want %s?", ultimateOptions[choice].name), DialogType::DialogYesNo, ClearScreen::Bottom)();
                if (!answer) return;
                if (!WRITE32(evoTarget_addr, ultimateOptions[choice].id)) goto error;
                if (!WRITE8(action_addr, EVOLVE)) goto error;
            }
            break;
        case 5:
            // Mega was selected
            if (options.empty())
                for (const DigimonList &m : megaOptions)
                    options.push_back(m.name);

            keyboard.Populate(options);
            choice = keyboard.Open();

            if (choice >= 0) {
                bool answer = MessageBox(Utils::Format("Are you sure you want %s?", megaOptions[choice].name), DialogType::DialogYesNo, ClearScreen::Bottom)();
                if (!answer) return;
                if (!WRITE32(evoTarget_addr, megaOptions[choice].id)) goto error;
                if (!WRITE8(action_addr, EVOLVE)) goto error;
            }
            break;
        case -1:
        default:
            // User closed keyboard
            return;   
    }

    if (choice == -1) return;

    MessageBox("Digimon ID Hacked!!", DialogType::DialogOk, ClearScreen::Both)();
    return;

    error:
        MessageBox("Digimon Swap Failed!", DialogType::DialogOk, ClearScreen::Both)();
}
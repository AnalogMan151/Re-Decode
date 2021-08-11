#include "Cheats.hpp"

using namespace CTRPluginFramework;

// Hold START for 1.5 seconds to Run or Stop OSD
void toggleOverlayFunc(MenuEntry *entry)
{
    static HoldKey sHold(Key::Start, Seconds(1.5f));
    static bool showOSD = false;

    if (sHold())
        showOSD = !showOSD;
    
    if (showOSD)
        OSD::Run(Terminal);
    else
        OSD::Stop(Terminal);
}

// Searches through Digimon groups for matching ID and returns name string
std::string findDigimon(u32 id)
{
    for (int i = 0; i < freshOptions.size(); i++)
        if (freshOptions[i].id == id)
            return freshOptions[i].name;
    for (int i = 0; i < inTrainingOptions.size(); i++)
        if (inTrainingOptions[i].id == id)
            return inTrainingOptions[i].name;
    for (int i = 0; i < rookieOptions.size(); i++)
        if (rookieOptions[i].id == id)
            return rookieOptions[i].name;
    for (int i = 0; i < championOptions.size(); i++)
        if (championOptions[i].id == id)
            return championOptions[i].name;
    for (int i = 0; i < ultimateOptions.size(); i++)
        if (ultimateOptions[i].id == id)
            return ultimateOptions[i].name;
    for (int i = 0; i < megaOptions.size(); i++)
        if (megaOptions[i].id == id)
            return megaOptions[i].name;
    return "Unknown";                
}

// Searches Digimon Raise structs for fullness limit
u8 getFullnessLimit(u32 id)
{
    u16 digiDefineID;
    u8 fullnessLimit;
    for (int i = 0; i < 248; i++)
    {
        if (!READ16(digimonDefine_addr + (0x9C * i), digiDefineID)) return 0;
        if (digiDefineID == id)
        {
            if (!READ8((digimonRaise_addr + (0x3C * i)) + 0x8, fullnessLimit)) return 0;
            return fullnessLimit;
        }
    }
    return 0;
}

// Draws and populates the terminal OSD with info
bool Terminal(const Screen& screen)
{
    int x = 206;
    int y = 10;
    Color color= Color(Color::Green);
    Color color_warning(Color::Red);

    std::string name;
    u32 id = 0;
    static u32 prevID = 0;
    static std::string digimon;
    u32 life = 0;
    u32 evolve = 0;
    u32 poop1 = 0;
    u32 poop2 = 0;
    u8 hasToPoop = 0;
    u32 sleep = 0;
    float discipline = 0.f;
    float happiness = 0.f;
    u8 care = 0;
    u8 poopMeter = 0;
    u8 fullness = 0;
    static u8 fullnessLimit = 0;
    u8 isHungry = 0;

    READSTRING(digimon_addr, name, 16, StringFormat::Utf16);
    READ32(digimon_addr + 0x14, id);
    READ32(digimon_addr + 0x55C, life);
    READ32(digimon_addr + 0x560, evolve);
    READ32(digimon_addr + 0x54C, poop1);
    READ32(digimon_addr + 0x550, poop2);
    READ8(digimon_addr + 0x549, hasToPoop);
    READ32(digimon_addr + 0x510, sleep);
    if (sleep > 0xFF000000)
        sleep = 0;
    READFLOAT(digimon_addr + 0x44, discipline);
    READFLOAT(digimon_addr + 0x40, happiness);
    READ8(digimon_addr + 0x53C, care);
    READ8(digimon_addr + 0x48, poopMeter);
    READ8(digimon_addr + 0x538, fullness);
    READ8(digimon_addr + 0x539, isHungry);

    if (prevID != id)
    {
        digimon = findDigimon(id);
        fullnessLimit = getFullnessLimit(id);
        prevID = id;
    }

    if (!screen.IsTop)
        return false;
    
    // Draw background window
    screen.DrawRect(x, y, 186, 90, Color(Color::Green), true);
    screen.DrawRect(x+1, y+7, 184, 82, Color(Color::Black), true);

    // Draw background window icon
    screen.DrawPixel(x+3, y+1, Color(Color::Black));
    screen.DrawPixel(x+4, y+2, Color(Color::Black));
    screen.DrawPixel(x+5, y+3, Color(Color::Black));
    screen.DrawPixel(x+4, y+4, Color(Color::Black));
    screen.DrawPixel(x+3, y+5, Color(Color::Black));

    // Draw foreground window
    screen.DrawRect(x+5, y-5, 186, 90, Color(Color::Green), true);
    screen.DrawRect(x+6, y+2, 184, 82, Color(Color::Black), true);

    // Draw foreground window icon
    screen.DrawPixel(x+8, y-4, Color(Color::Black));
    screen.DrawPixel(x+9, y-3, Color(Color::Black));
    screen.DrawPixel(x+10, y-2, Color(Color::Black));
    screen.DrawPixel(x+9, y-1, Color(Color::Black));
    screen.DrawPixel(x+8, y, Color(Color::Black));
    screen.DrawRect(x+12, y, 5, 1, Color(Color::Black), false);

    // Draw close button
    screen.DrawPixel(x+186, y-3, Color(Color::Black));
    screen.DrawPixel(x+187, y-2, Color(Color::Black));
    screen.DrawPixel(x+186, y-1, Color(Color::Black));
    screen.DrawPixel(x+188, y-3, Color(Color::Black));
    screen.DrawPixel(x+188, y-1, Color(Color::Black));

    x += 7;
    y += 2;

    y = screen.Draw("root$ cat ~/.status/" + name, x, y, color);
    y = screen.Draw(Utils::Format("ID: [%3d] ", id) + digimon, x, y, color);

    std::string life_evolveStr = Utils::Format("Life:%3dm %2ds  Evolve:%3dm %2ds", life/3600, (life%3600)/60, evolve/3600, (evolve%3600)/60);
    y = screen.Draw(life_evolveStr, x, y, color);
    
    std::string poop_sleepStr;
    if (hasToPoop)
        poop_sleepStr = Utils::Format("Poop:%3dm %2ds  Sleep:%4dm %2ds", (poop1 + poop2)/3600, ((poop1 + poop2)%3600)/60, sleep/3600, (sleep%3600)/60);
    else
        poop_sleepStr = Utils::Format("Poop: No Need  Sleep:%4dm %2ds", sleep/3600, (sleep%3600)/60);
    y = screen.Draw(poop_sleepStr, x, y, color);
    screen.Draw(Utils::Format("Disc: %d%%", (u32)discipline), x, y, color);
    y = screen.Draw(Utils::Format("Happy: %3d%%", (u32)happiness), x+90, y, color);
    y = screen.Draw(Utils::Format("Care Mistakes: %d", care), x, y, color);
    screen.Draw("Fullness:   ", x, y, color);
    screen.Draw(Utils::Format("/%d", fullnessLimit), x+84, y, color);
    y = screen.Draw(Utils::Format("%3d", fullness), x+66, y, isHungry ? color_warning : color);
    screen.Draw(Utils::Format("Poop Meter: %2d/16", poopMeter), x, y, color);

    return true;
}
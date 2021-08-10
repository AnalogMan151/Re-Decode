#include "Cheats.hpp"
#include "Overlay.hpp"
#include <math.h>

using namespace CTRPluginFramework;

void terminalOverlay(void)
{
    static u32 x = 20, y = 20;
    Process::Pause();
    const Screen& screen = OSD::GetTopScreen();

    screen.DrawRect(0, 0, 400, 240, Color::Black, true); // Background
    OSD::SwapBuffers();
    while(!Controller::IsKeyPressed(Key::R)) {
    if(Controller::IsKeyDown(Key::DPadRight)) { // move to the right
        ++x;
        screen.DrawRect(0, 0, 400, 240, Color::Black, true);
        screen.DrawRect(x, 20, 50, 50, Color::White, true); // draw the white square
        OSD::SwapBuffers();
    }
    if(Controller::IsKeyDown(Key::DPadLeft)) { // move to the left
        --x;
        screen.DrawRect(0, 0, 400, 240, Color::Black, true);
        screen.DrawRect(x, 20, 50, 50, Color::White, true); // draw the white square
        OSD::SwapBuffers();
    }
    Controller::Update();
    }
    Process::Play();
}

void toggleOverlayFunc(MenuEntry *entry)
{
    static HoldKey bHold(Key::B, Seconds(2.f));
    static bool showOSD = false;

    if (!entry->IsActivated())
    {
        OSD::Stop(Terminal);
        return;
    }

    if (bHold())
        showOSD = !showOSD;
    
    if (showOSD)
        OSD::Run(Terminal);
    else
        OSD::Stop(Terminal);
}

std::string findDigimon(u8 id)
{
    for (int i = 0; i < freshOptions.size(); i++)
        if (freshOptions[i].value == id)
            return freshOptions[i].name;
    for (int i = 0; i < inTrainingOptions.size(); i++)
        if (inTrainingOptions[i].value == id)
            return inTrainingOptions[i].name;
    for (int i = 0; i < rookieOptions.size(); i++)
        if (rookieOptions[i].value == id)
            return rookieOptions[i].name;
    for (int i = 0; i < championOptions.size(); i++)
        if (championOptions[i].value == id)
            return championOptions[i].name;
    for (int i = 0; i < ultimateOptions.size(); i++)
        if (ultimateOptions[i].value == id)
            return ultimateOptions[i].name;
    for (int i = 0; i < megaOptions.size(); i++)
        if (megaOptions[i].value == id)
            return megaOptions[i].name;
    return "Unknown";                
}

bool Terminal(const Screen& screen)
{
    int x = 206;
    int y = 10;
    Color color= Color(Color::Green);
    Color color_warning(Color::Red);

    std::string name;
    u8 id = 0;
    std::string digimon;
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
    u8 isHungry = 0;

    READSTRING(digimon_addr, name, 16, StringFormat::Utf16);
    READ8(digimon_addr + 0x14, id);
    digimon = findDigimon(id);
    READ32(digimon_addr + 0x55C, life);
    READ32(digimon_addr + 0x560, evolve);
    READ32(digimon_addr + 0x54C, poop1);
    READ32(digimon_addr + 0x550, poop2);
    READ8(digimon_addr + 0x549, hasToPoop);
    READ32(digimon_addr + 0x510, sleep);
    READFLOAT(digimon_addr + 0x44, discipline);
    READFLOAT(digimon_addr + 0x40, happiness);
    READ8(digimon_addr + 0x53C, care);
    READ8(digimon_addr + 0x48, poopMeter);
    READ8(digimon_addr + 0x538, fullness);
    READ8(digimon_addr + 0x539, isHungry);

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
    screen.Draw("/40", x+84, y, color);
    y = screen.Draw(Utils::Format("%2d", fullness), x+72, y, isHungry ? color_warning : color);
    screen.Draw(Utils::Format("Poop Meter: %2d/16", poopMeter), x, y, color);

    return true;
}

// Add function to OSD call stack


// Remove function from OSD call stack
// OSD::Stop(OSDFunction);
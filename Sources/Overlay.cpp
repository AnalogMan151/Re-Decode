#include "Cheats.hpp"

using namespace CTRPluginFramework;

static bool full = true;

// Hold START for 1.5 seconds to Run or Stop OSD
void toggleOverlayFunc(MenuEntry *entry)
{
    static HoldKey stHold(Key::Start, Seconds(1.5f));
    static HoldKey seHold(Key::Select, Seconds(1.5f));
    static bool showOSD = false;

    if (stHold())
    {
        if (showOSD && !full)
            full = true;
        else
            showOSD = !showOSD;
        full = true;
    }

    if (seHold())
    {
        if (showOSD && full)
            full = false;
        else
            showOSD = !showOSD;
        full = false;
    }
    
    if (showOSD)
        OSD::Run(Terminal);
    else
        OSD::Stop(Terminal);
}

// Draws and populates the terminal OSD with info
bool Terminal(const Screen& screen)
{
    int x = 206;
    int y = 10;
    Color color= Color(0x33FF33FF);
    Color color_warning(0xFFBB00FF);
    Color bg = Color(0x282828FF);
    static Clock timer;

    std::string nickName;
    u32 id = 0;
    u32 dName_off = 0;
    std::string digimonName;
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
    u8 fullnessLimit = 0;
    u8 isHungry = 0;

    READSTRING(digimon_addr, nickName, 16, StringFormat::Utf16);
    READ32(digimon_addr + 0x14, id);
    READ32(((assets_addr + 0x1806ADC) + id * 8) + 4, dName_off);
    READSTRING(((assets_addr + 0x1806ADC) + id * 8) + dName_off, digimonName, 40, StringFormat::Utf16);
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
    READ8((digimonRaise_addr + (0x3C * (id-1))) + 0x8, fullnessLimit);
    READ8(digimon_addr + 0x539, isHungry);

    if (!screen.IsTop)
        return false;
    
    if (full)
    {
        // Draw background window
        screen.DrawRect(x, y, 186, 90, color, true);
        screen.DrawRect(x+1, y+7, 184, 82, bg, true);

        // Draw background window icon
        screen.DrawPixel(x+3, y+1, Color(Color::Black));
        screen.DrawPixel(x+4, y+2, Color(Color::Black));
        screen.DrawPixel(x+5, y+3, Color(Color::Black));
        screen.DrawPixel(x+4, y+4, Color(Color::Black));
        screen.DrawPixel(x+3, y+5, Color(Color::Black));

        // Draw foreground window
        screen.DrawRect(x+5, y-5, 186, 90, color, true);
        screen.DrawRect(x+6, y+2, 184, 82, bg, true);

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

        y = screen.Draw("root$ cat ~/.status/" + nickName, x, y, color, bg);
        y = screen.Draw(Utils::Format("ID: [%3d] ", id) + digimonName, x, y, color, bg);

        std::string life_evolveStr = Utils::Format("Life: %d:%02d:%02d  Evolve: %d:%02d:%02d",
            life/216000, (life%216000)/3600, (life%3600)/60, 
            evolve/216000, (evolve%216000)/3600, (evolve%3600)/60);
        y = screen.Draw(life_evolveStr, x, y, color, bg);
        
        std::string poop_sleepStr;
        if (hasToPoop)
            poop_sleepStr = Utils::Format("Poop:   %2d:%02d  Sleep:    %2d:%02d", (poop1 + poop2)/3600, ((poop1 + poop2)%3600)/60, sleep/3600, (sleep%3600)/60);
        else
            poop_sleepStr = Utils::Format("Poop: No Need  Sleep:    %2d:%02d", sleep/3600, (sleep%3600)/60);
        y = screen.Draw(poop_sleepStr, x, y, color, bg);
        screen.Draw(Utils::Format("Disc: %d%%", (u32)discipline), x, y, color, bg);
        y = screen.Draw(Utils::Format("Happy:  %d%%", (u32)happiness), x+90, y, color, bg);
        y = screen.Draw(Utils::Format("Care Mistakes: %d", care), x, y, color, bg);
        screen.Draw("Fullness:   ", x, y, color, bg);
        screen.Draw(Utils::Format("/%d", fullnessLimit), x+84, y, color, bg);
        y = screen.Draw(Utils::Format("%3d", fullness), x+66, y, isHungry ? color_warning : color, bg);
        screen.Draw(Utils::Format("Poop Meter: %2d/16", poopMeter), x, y, color, bg);
    }
    else
    {
        // Draw minimilistic ticker info
        if (hasToPoop)
        {
            screen.Draw(Utils::Format("L|%d:%02d:%02d E|%d:%02d:%02d S|%02d:%02d P|%02d:%02d F|%03d CM|%02d",
                life / 216000, (life % 216000) / 3600, (life % 3600) / 60,
                evolve / 216000, (evolve % 216000) / 3600, (evolve % 3600) / 60, 
                sleep / 3600, (sleep % 3600) / 60, (poop1+poop2) / 3600, ((poop1 + poop2) % 3600) /60,
                fullness, care), 116, 0, color, bg);
        }
        else
        {
            screen.Draw(Utils::Format("L|%d:%02d:%02d E|%d:%02d:%02d S|%02d:%02d P|--:-- F|%03d CM|%02d",
                life / 216000, (life % 216000) / 3600, (life % 3600) / 60,
                evolve / 216000, (evolve % 216000) / 3600, (evolve % 3600) / 60, 
                sleep / 3600, (sleep % 3600) / 60, fullness, care), 116, 0, color, bg);
        }
    }
    return true;
}
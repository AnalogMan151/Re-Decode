#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include <memory>
#include <string>
#include <stdexcept>

extern std::vector<std::string> approvedCodes;

using namespace CTRPluginFramework;

using FuncPointer = void(*)(MenuEntry *);

MenuEntry *Entry(const std::string &name, const std::string &note)
{
    MenuEntry   *entry = new MenuEntry(name, note);
    return (entry);
}

MenuEntry *Entry(const std::string &name, FuncPointer gamefunc)
{
    MenuEntry   *entry = new MenuEntry(name, gamefunc);
    return (entry);
}

MenuEntry *Entry(const std::string &name, FuncPointer gamefunc, FuncPointer menuFunc)
{
    MenuEntry   *entry = new MenuEntry(name, gamefunc, menuFunc);
    return (entry);
}

MenuEntry *Entry(const std::string &name, const std::string &note, FuncPointer gamefunc)
{
    MenuEntry   *entry = new MenuEntry(name, gamefunc, note);
    return (entry);
}

MenuEntry *Entry(const std::string &name, const std::string &note, FuncPointer gamefunc, FuncPointer menuFunc)
{
    MenuEntry   *entry = new MenuEntry(name, gamefunc, menuFunc, note);
    return (entry);
}

MenuEntry *Entry(u32 radio, const std::string &name, FuncPointer gamefunc)
{
    MenuEntry   *entry = new MenuEntry(radio, name, gamefunc);
    return (entry);
}

MenuEntry *Entry(u32 radio, const std::string &name, FuncPointer gamefunc, FuncPointer menuFunc)
{
    MenuEntry   *entry = new MenuEntry(radio, name, gamefunc, menuFunc);
    return (entry);
}

MenuEntry *Entry(u32 radio, const std::string &name, const std::string &note, FuncPointer gamefunc)
{
    MenuEntry   *entry = new MenuEntry(radio, name, gamefunc, note);
    return (entry);
}

MenuEntry *Entry(u32 radio, const std::string &name, const std::string &note, FuncPointer gamefunc, FuncPointer menuFunc)
{
    MenuEntry   *entry = new MenuEntry(radio, name, gamefunc, menuFunc, note);
    return (entry);
}

MenuEntry *EntryWithHotkey(const std::string &name, FuncPointer gamefunc, const std::vector<Hotkey> &hotkeys)
{
    MenuEntry   *entry = new MenuEntry(name, gamefunc);

    for (const Hotkey &hk : hotkeys)
    {
        entry->Hotkeys += hk;
    }

    return (entry);
}

MenuEntry *EntryWithHotkey(const std::string &name, FuncPointer gamefunc, FuncPointer menuFunc, const std::vector<Hotkey> &hotkeys)
{
    MenuEntry   *entry = new MenuEntry(name, gamefunc, menuFunc);

    for (const Hotkey &hk : hotkeys)
    {
        entry->Hotkeys += hk;
    }

    return (entry);
}

MenuEntry *EntryWithHotkey(const std::string &name, const std::string &note, FuncPointer gamefunc, const std::vector<Hotkey> &hotkeys)
{
    MenuEntry   *entry = new MenuEntry(name, gamefunc, note);

    for (const Hotkey &hk : hotkeys)
    {
        entry->Hotkeys += hk;
    }

    return (entry);
}

MenuEntry *EntryWithHotkey(const std::string &name, const std::string &note, FuncPointer gamefunc, FuncPointer menuFunc, const std::vector<Hotkey> &hotkeys)
{
    MenuEntry   *entry = new MenuEntry(name, gamefunc, menuFunc, note);

    for (const Hotkey &hk : hotkeys)
    {
        entry->Hotkeys += hk;
    }

    return (entry);
}

MenuEntry *EntryWithHotkey(u32 radio, const std::string &name, FuncPointer gamefunc, const std::vector<Hotkey> &hotkeys)
{
    MenuEntry   *entry = new MenuEntry(radio, name, gamefunc);

    for (const Hotkey &hk : hotkeys)
    {
        entry->Hotkeys += hk;
    }

    return (entry);
}

MenuEntry *EntryWithHotkey(u32 radio, const std::string &name, FuncPointer gamefunc, FuncPointer menuFunc, const std::vector<Hotkey> &hotkeys)
{
    MenuEntry   *entry = new MenuEntry(radio, name, gamefunc, menuFunc);

    for (const Hotkey &hk : hotkeys)
    {
        entry->Hotkeys += hk;
    }

    return (entry);
}

MenuEntry *EntryWithHotkey(u32 radio, const std::string &name, const std::string &note, FuncPointer gamefunc, const std::vector<Hotkey> &hotkeys)
{
    MenuEntry   *entry = new MenuEntry(radio, name, gamefunc, note);

    for (const Hotkey &hk : hotkeys)
    {
        entry->Hotkeys += hk;
    }

    return (entry);
}

MenuEntry *EntryWithHotkey(u32 radio, const std::string &name, const std::string &note, FuncPointer gamefunc, FuncPointer menuFunc, const std::vector<Hotkey> &hotkeys)
{
    MenuEntry   *entry = new MenuEntry(radio, name, gamefunc, menuFunc, note);

    for (const Hotkey &hk : hotkeys)
    {
        entry->Hotkeys += hk;
    }

    return (entry);
}

bool IsOnWhiteList(void)
{
    FriendKey FKey;
    u64 FCode;
  
    if (approvedCodes.size() == 0)
        return true;

    frdInit();
    FRD_GetMyFriendKey(&FKey);
    FRD_PrincipalIdToFriendCode(FKey.principalId, &FCode);

    std::string FriendCode = std::string(12 - std::to_string(FCode).length(), '0') + std::to_string(FCode);
    
    return !(std::find(approvedCodes.begin(), approvedCodes.end(), FriendCode) == approvedCodes.end());
}
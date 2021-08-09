#ifndef HOTKEYHELPERS_HPP
#define HOTKEYHELPERS_HPP

#include <CTRPluginFramework/Menu/MenuEntry.hpp>

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
#endif
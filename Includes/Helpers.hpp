#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "Helpers/AutoRegion.hpp"
#include "Helpers/HoldKey.hpp"
#include "Helpers/KeySequence.hpp"
#include "Helpers/MenuEntryHelpers.hpp"
#include "Helpers/OSDManager.hpp"
#include "Helpers/QuickMenu.hpp"
#include "Helpers/Strings.hpp"
#include "Helpers/Wrappers.hpp"

using namespace CTRPluginFramework;
using FuncPointer = void(*)(MenuEntry *);

// Read & Write Helpers
#define WRITE8(address, value) Process::Write8(address, value)
#define WRITE16(address, value) Process::Write16(address, value)
#define WRITE32(address, value) Process::Write32(address, value)
#define WRITE64(address, value) Process::Write64(address, value)
#define WRITEFLOAT(address, value) Process::WriteFloat(address, value)
#define WRITEDOUBLE(address, value) Process::WriteDouble(address, value)
#define WRITESTRING(address, value) Process::WriteString(address, value)
#define READ8(address, value) Process::Read8(address, value)
#define READ16(address, value) Process::Read16(address, value)
#define READ32(address, value) Process::Read32(address, value)
#define READ64(address, value) Process::Read64(address, value)
#define READFLOAT(address, value) Process::ReadFloat(address, value)
#define READDOUBLE(address, value) Process::ReadDouble(address, value)
#define READSTRING(address, value, size, format) Process::ReadString(address, value, size, format)

// Useful Functions
bool IsOnWhiteList(void);

#endif

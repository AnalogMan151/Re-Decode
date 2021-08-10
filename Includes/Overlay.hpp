#ifndef OVERLAY_H
#define OVERLAY_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

using namespace CTRPluginFramework;

void terminalOverlay(void);
void toggleOverlayFunc(MenuEntry *entry);
bool Terminal(const Screen& screen);

#endif
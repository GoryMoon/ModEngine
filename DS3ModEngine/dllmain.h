#pragma once

#include "stdafx.h"
#include <iostream>
#include <strsafe.h>
#include <tchar.h>

#include "dinput8/dinputWrapper.h"
#include "Game.h"
#include "StackWalker/StackWalker.h"
#include "HideThreadFromDebugger.h"
#include "LooseParams.h"
#include "NetworkBlocker.h"
#include "ModLoader.h"
#include "GameplayPatcher.h"

std::string Msg1 = "Modengine dll by katalash";
std::string Msg2 = "alternate save file used and network access blocked";
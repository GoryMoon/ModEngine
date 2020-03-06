#pragma once

#include <windows.h>
#include <cstdio>

// DX11
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

// IMGUI Related Files
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

// Hooks
#include "ImGuiHook/d3d11hook.h"

#include "globals.h"
#include "Kiero/kiero.h"
#include "MinHook/include/MinHook.h"
#include "ImGuiHook/InputHook.h"
#include "ImGuiHook/hooks.h"
#include "ImGuiHook/menu.h"
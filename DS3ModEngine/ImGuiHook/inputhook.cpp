#include "stdafx.h"

using namespace ImGui;

namespace InputHook
{
	WNDPROC oWndProc;

	void Init(const HWND hWindow)
	{
		oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWindow, GWLP_WNDPROC, static_cast<__int3264>(reinterpret_cast<LONG_PTR>(WndProc))));
	}

	void Remove(const HWND hWindow)
	{
		SetWindowLongPtr(hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
	}

	LRESULT APIENTRY WndProc(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}

		return CallWindowProc(oWndProc, hwnd, msg, wParam, lParam);
	}
}

#include "stdafx.h"

using namespace kiero;

namespace Hooks
{
	HRESULT Init()
	{
		if (init(RenderType::D3D11) == Status::Success)
		{
			auto status = kiero::bind(8, reinterpret_cast<void**>(&D3d11Hook::oD3D11Present), D3d11Hook::PresentHook);
			if (status == Status::Success) status = kiero::bind(73, reinterpret_cast<void**>(&D3d11Hook::oD3D11DrawIndexed), D3d11Hook::DrawIndexedHook);
			if (status == Status::Success) status = kiero::bind(42, reinterpret_cast<void**>(&D3d11Hook::oD3D11CreateQuery), D3d11Hook::CreateQueryHook);
			if (status == Status::Success) status = kiero::bind(69, reinterpret_cast<void**>(&D3d11Hook::oD3D11PSSetShaderResources), D3d11Hook::PSSetShaderResourcesHook);
			if (status == Status::Success) status = kiero::bind(111, reinterpret_cast<void**>(&D3d11Hook::oD3D11ClearRenderTargetViewHook), D3d11Hook::ClearRenderTargetViewHook);

			if (status == Status::Success)
			{	
				wprintf(L"[ModEngine] D3D hooks installed\r\n");

				do
				{
					Sleep(100);
				}
				while (!(GetAsyncKeyState(Globals::uninjectKey) & 0x1));
			}
			else
			{
				wprintf(L"[ModEngine] D3D hook installations failed\r\n");
			}

			D3d11Hook::Release();
			kiero::shutdown();
			MH_Uninitialize();
			InputHook::Remove(Globals::mainWindow);

			Beep(220, 100);

			FreeLibraryAndExitThread(Globals::mainModule, 0);
			return S_OK;
		}
		return S_FALSE;
	}
}

#include "stdafx.h"

namespace D3d11Hook
{
	static ID3D11Device* d3d11Device = NULL;
	static ID3D11DeviceContext* d3d11Context = NULL;
	static ID3D11RenderTargetView* d3d11RenderTarget = NULL;

	D3D11PresentHook oD3D11Present;
	D3D11DrawIndexedHook oD3D11DrawIndexed;
	D3D11CreateQueryHook oD3D11CreateQuery;
	D3D11PSSetShaderResourcesHook oD3D11PSSetShaderResources;
	D3D11ClearRenderTargetViewHook oD3D11ClearRenderTargetViewHook;

	bool shutdown = false;

	HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, const UINT syncInterval, const UINT flags)
	{
		static bool init = false; // Initialized only once

		if (GetAsyncKeyState(Globals::openMenuKey) & 0x1)
		{
			Menu::isOpen ? Menu::isOpen = false : Menu::isOpen = true;
		}

		if (!init)
		{
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(d3d11Device), reinterpret_cast<void**>(&d3d11Device))))
			{
				d3d11Device->GetImmediateContext(&d3d11Context);
				ImGui::CreateContext();

				ImGuiIO& io = ImGui::GetIO();
				ImGui::StyleColorsDark();
				ImFontAtlas* fonts = io.Fonts;
				/*
				 * Example font loading, needs the "ModEngine/Fonts/" folders, or what you want in the game folder.
				 * Then put the font files in there and you can load them as following.
				{
					ImFontConfig cfg = ImFontConfig();
					cfg.GlyphMinAdvanceX = 5.0f;
					cfg.OversampleH = 5;
					cfg.OversampleV = 5;
					fonts->AddFontFromFileTTF("ModEngine/Fonts/RobotoMono-Light.ttf", 14, &cfg, fonts->GetGlyphRangesDefault());
				}
				{
					ImFontConfig cfg = ImFontConfig();
					cfg.MergeMode = true;
					cfg.GlyphMinAdvanceX = 7.0f;
					cfg.OversampleH = 5;
					cfg.OversampleV = 5;
					fonts->AddFontFromFileTTF("ModEngine/Fonts/NotoSansCJKtc-Light.otf", 16, &cfg, fonts->GetGlyphRangesJapanese());
				}
				fonts->Build();
				*/
				io.IniFilename = nullptr; // Disable ImGui config file

				// Create swap chain render target view
				ID3D11Texture2D* backBuffer;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBuffer));
				d3d11Device->CreateRenderTargetView(backBuffer, nullptr, &d3d11RenderTarget);
				backBuffer->Release();
				
				ImGui_ImplWin32_Init(Globals::mainWindow);
				ImGui_ImplDX11_Init(d3d11Device, d3d11Context);

				ImGui_ImplDX11_CreateDeviceObjects();
				
				InputHook::Init(Globals::mainWindow);
			}

			init = true;
		}

		if (shutdown == false)
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			Menu::Init();
			
			d3d11Context->OMSetRenderTargets(1, &d3d11RenderTarget, nullptr);
			
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}

		return oD3D11Present(pSwapChain, syncInterval, flags);
	}

	void __stdcall DrawIndexedHook(ID3D11DeviceContext* pContext, const UINT indexCount, const UINT startIndexLocation, const INT baseVertexLocation)
	{
		return oD3D11DrawIndexed(pContext, indexCount, startIndexLocation, baseVertexLocation);
	}

	void __stdcall CreateQueryHook(ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery)
	{
		if (pQueryDesc->Query == D3D11_QUERY_OCCLUSION)
		{
			D3D11_QUERY_DESC oqueryDesc = CD3D11_QUERY_DESC();
			(&oqueryDesc)->MiscFlags = pQueryDesc->MiscFlags;
			(&oqueryDesc)->Query = D3D11_QUERY_TIMESTAMP;

			return oD3D11CreateQuery(pDevice, &oqueryDesc, ppQuery);
		}

		return oD3D11CreateQuery(pDevice, pQueryDesc, ppQuery);
	}

	UINT pssrStartSlot;
	D3D11_SHADER_RESOURCE_VIEW_DESC descr;

	void __stdcall PSSetShaderResourcesHook(ID3D11DeviceContext* pContext, const UINT startSlot, const UINT numViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
	{
		pssrStartSlot = startSlot;

		for (UINT j = 0; j < numViews; j++)
		{
			ID3D11ShaderResourceView* pShaderResView = ppShaderResourceViews[j];
			if (pShaderResView)
			{
				pShaderResView->GetDesc(&descr);

				if ((descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFER) || (descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFEREX))
				{
					continue; //Skip buffer resources
				}
			}
		}

		return oD3D11PSSetShaderResources(pContext, startSlot, numViews, ppShaderResourceViews);
	}

	void __stdcall ClearRenderTargetViewHook(ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView, const FLOAT colorRgba[4])
	{
		return oD3D11ClearRenderTargetViewHook(pContext, pRenderTargetView, colorRgba);
	}

	void Release()
	{
		shutdown = true;
		d3d11Device->Release();
		d3d11Context->Release();
		d3d11RenderTarget->Release();
	}
}

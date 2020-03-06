#pragma once

namespace D3d11Hook
{
	typedef HRESULT (__stdcall* D3D11PresentHook)(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);
	typedef void (__stdcall* D3D11DrawIndexedHook)(ID3D11DeviceContext* pContext, UINT indexCount, UINT startIndexLocation, INT baseVertexLocation);
	typedef void (__stdcall* D3D11CreateQueryHook)(ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery);
	typedef void (__stdcall* D3D11PSSetShaderResourcesHook)(ID3D11DeviceContext* pContext, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
	typedef void (__stdcall* D3D11ClearRenderTargetViewHook)(ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView, const FLOAT colorRgba[4]);

	extern D3D11PresentHook					oD3D11Present;
	extern D3D11DrawIndexedHook				oD3D11DrawIndexed;
	extern D3D11CreateQueryHook				oD3D11CreateQuery;
	extern D3D11PSSetShaderResourcesHook	oD3D11PSSetShaderResources;
	extern D3D11ClearRenderTargetViewHook	oD3D11ClearRenderTargetViewHook;

	extern HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);
	extern void __stdcall DrawIndexedHook(ID3D11DeviceContext* pContext, UINT indexCount, UINT startIndexLocation, INT baseVertexLocation);
	extern void __stdcall CreateQueryHook(ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery);
	extern void __stdcall PSSetShaderResourcesHook(ID3D11DeviceContext* pContext, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
	extern void __stdcall ClearRenderTargetViewHook(ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView, const FLOAT colorRgba[4]);

	extern void Release();
}

#include "stdafx.h"

#include <d3d11.h>
#include "Renderer.h"

namespace Easy3D
{
	Renderer::Renderer()
	{
	}


	Renderer::~Renderer()
	{
	}

	void Renderer::SetRenderTarget(int aNumberOfRenderTargets, ID3D11RenderTargetView** someRenderTargets
		, ID3D11DepthStencilView* aDepthStencil)
	{
		Engine::GetInstance()->GetContext()->OMSetRenderTargets(aNumberOfRenderTargets, someRenderTargets, aDepthStencil);
	}

}
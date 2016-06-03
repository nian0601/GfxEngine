#pragma once
#include "FullscreenQuad.h"

struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace Easy3D
{
	class Renderer : public FullscreenQuad
	{
	public:
		Renderer();
		~Renderer();

		void SetRenderTarget(int aNumberOfRenderTargets, ID3D11RenderTargetView** someRenderTargets, ID3D11DepthStencilView* aDepthStencil);
	};
}
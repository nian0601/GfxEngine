#pragma once
#include <CUString.h>
#include "FullscreenQuad.h"
#include <Matrix.h>
#include "ModelData.h"
#include <Vector.h>

struct ID3DX11EffectVariable;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace Easy3D
{
	class Effect;
	class Texture;
	class Renderer : public FullscreenQuad
	{
	public:
		Renderer();
		~Renderer();

		void SetEffect(Effect* aEffect);
		void SetTexture(const CU::String<50>& aName, Texture* aTexture);
		void SetMatrix(const CU::String<50>& aName, const CU::Matrix44<float>& aMatrix);
		void SetVector(const CU::String<50>& aName, const CU::Vector3<float>& aVector);
		void SetVector(const CU::String<50>& aName, const CU::Vector4<float>& aVector);

		void AddRenderTarget(Texture* aTexture);
		void ClearRenderTarget(Texture* aTexture, const CU::Vector4<float>& aColor);
		void SetDepthStencil(Texture* aTexture);
		void ClearDepthStencil(Texture* aTexture);
		void ApplyRenderTargetAndDepthStencil();

		void RenderFullScreen(const CU::String<30>& aTechnique);
		void RenderModel(const ModelData& aData, const CU::String<30>& aTechnique);

	private:
		ID3DX11EffectVariable* GetEffectVariable(const CU::String<50>& aName);

		Effect* myCurrentEffect;

		int myRenderTargetCount;
		ID3D11RenderTargetView* myRenderTargets[4];
		ID3D11DepthStencilView* myDepthStencil;
	};
}
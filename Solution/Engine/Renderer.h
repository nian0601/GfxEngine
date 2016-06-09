#pragma once

#include "Backbuffer.h"
#include <CUMap.h>
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
		Renderer(EffectID aFullscreenEffect);
		~Renderer();

		void SetEffect(EffectID aEffect);
		void SetTexture(const CU::String<64>& aName, Texture* aTexture);
		void SetMatrix(const CU::String<64>& aName, const CU::Matrix44<float>& aMatrix);
		void SetVector(const CU::String<64>& aName, const CU::Vector3<float>& aVector);
		void SetVector(const CU::String<64>& aName, const CU::Vector4<float>& aVector);
		void SetRawData(const CU::String<64>& aName, int aDataSize, const void* someData);

		void SetClearColor(const CU::Vector4<float>& aColor);

		void AddRenderTarget(Texture* aTexture);
		void ClearRenderTarget(Texture* aTexture);
		void SetDepthStencil(Texture* aTexture);
		void ClearDepthStencil(Texture* aTexture);
		void SetBackbufferAsTarget();
		void ApplyRenderTargetAndDepthStencil();

		void RenderFullScreen(const CU::String<30>& aTechnique);
		void RenderModel(ModelID aModelID);

	private:
		ID3DX11EffectVariable* GetEffectVariable(const CU::String<64>& aName);
		void RenderModelData(const ModelData& someData);
		void RenderGPUData(const GPUData& someData);

		EffectID myCurrentEffect;
		float myClearColor[4];

		int myRenderTargetCount;
		ID3D11RenderTargetView* myRenderTargets[4];
		ID3D11DepthStencilView* myDepthStencil;
		Backbuffer myBackbuffer;

		CU::Map<EffectID, CU::Map<CU::String<64>, ID3DX11EffectVariable*>> myEffectVariables;
	};
}
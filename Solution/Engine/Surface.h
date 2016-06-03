#pragma once

#include <GrowingArray.h>
#include <string>

struct ID3D11ShaderResourceView;
struct ID3DX11EffectShaderResourceVariable;

namespace Easy3D
{
	class Effect;

	class Surface
	{
	public:
		Surface();
		~Surface();

		void AddTexture(const CU::String<50>& aTeturePath, const CU::String<30>& aResourceName);
		void GetShaderResources(Effect* aEffect);

		void Activate();
		void Deactivate();

	private:
		CU::GrowingArray<CU::String<30>> myShaderResourceNames;
		CU::GrowingArray<ID3D11ShaderResourceView*> myResourceViews;
		CU::GrowingArray<ID3DX11EffectShaderResourceVariable*> myShaderVariables;
	};
}
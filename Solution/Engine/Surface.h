#pragma once

#include <GrowingArray.h>
#include <string>

struct ID3D11ShaderResourceView;
struct ID3DX11EffectShaderResourceVariable;

namespace Frost
{
	class Effect;

	class Surface
	{
	public:
		Surface();
		~Surface();

		void AddTexture(const std::string& aTeturePath, const std::string& aResourceName);
		void GetShaderResources(Effect* aEffect);

		void Activate();
		void Deactivate();

	private:
		CU::GrowingArray<std::string> myShaderResourceNames;
		CU::GrowingArray<ID3D11ShaderResourceView*> myResourceViews;
		CU::GrowingArray<ID3DX11EffectShaderResourceVariable*> myShaderVariables;
	};
}
#pragma once

#include <GrowingArray.h>

struct ID3D11ShaderResourceView;
struct ID3DX11EffectShaderResourceVariable;

namespace Easy3D
{
	class Effect;
	class Texture;

	class Surface
	{
	public:
		Surface();
		~Surface();

		void AddTexture(const CU::String<50>& aTexturePath, const CU::String<50>& aResourceName);

		int TextureCount() const;
		Texture* GetTexture(int aIndex) const;
		const CU::String<50>& GetResourceName(int aIndex) const;

	private:
		CU::GrowingArray<CU::String<50>> myShaderResourceNames;
		CU::GrowingArray<Texture*> myTextures;
	};

	inline int Surface::TextureCount() const
	{
		return myTextures.Size();
	}

	inline Texture* Surface::GetTexture(int aIndex) const
	{
		return myTextures[aIndex];
	}

	inline const CU::String<50>& Surface::GetResourceName(int aIndex) const
	{
		return myShaderResourceNames[aIndex];
	}
}
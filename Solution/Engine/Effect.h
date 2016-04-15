#pragma once

struct ID3DX11Effect;
struct ID3DX11EffectTechnique;
struct ID3DX11EffectMatrixVariable;

namespace Frost
{
	class Effect
	{
	public:
		Effect();
		~Effect();

		void Init(const std::string& aFilePath);

		ID3DX11Effect* GetEffect() const;
		ID3DX11EffectTechnique* GetTechnique(const std::string& aTechniqueName) const;


		void SetWorldMatrix(const CU::Matrix44<float>& aWorldMatrix);
		void SetViewMatrix(const CU::Matrix44<float>& aViewMatrix);
		void SetProjectionMatrix(const CU::Matrix44<float>& aProjectionMatrix);
		void SetViewProjectionMatrix(const CU::Matrix44<float>& aMatrix);

	private:
		void LoadMatrix(ID3DX11EffectMatrixVariable*& aMatrix, const std::string& aVariableName, bool aForceFind = true);

		ID3DX11Effect* myEffect;

		ID3DX11EffectMatrixVariable* myProjectionMatrix;
		ID3DX11EffectMatrixVariable* myViewMatrix;
		ID3DX11EffectMatrixVariable* myWorldMatrix;
		ID3DX11EffectMatrixVariable* myViewProjectionMatrix;

		std::string myFileName;
		std::string myFilePath;
	};
}
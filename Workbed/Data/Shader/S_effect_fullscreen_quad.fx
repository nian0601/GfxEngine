#include "S_u_variables.fx"

PixelShader_FullscreenQuad VS(VertexShader_FullscreenQuad aInput)
{
	PixelShader_FullscreenQuad output = (PixelShader_FullscreenQuad)0;

	output.Tex = aInput.Tex;
	output.Pos = aInput.Pos;

	return output;
}


float4 PS(PixelShader_FullscreenQuad aInput) : SV_Target
{
	return float4(0.f, 0.f, 1.f, 1.f);
}

technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
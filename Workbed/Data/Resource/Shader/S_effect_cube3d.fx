#include "S_u_variables.fx"


PixelShader_ColoredCube VS(VertexShader_ColoredCube aInput)
{
	PixelShader_ColoredCube output = (PixelShader_ColoredCube)0;
	output.Position = mul(aInput.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	output.Color = aInput.Color;
	return output;
}

float4 PS(PixelShader_ColoredCube aInput) : SV_Target
{
	return aInput.Color;
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
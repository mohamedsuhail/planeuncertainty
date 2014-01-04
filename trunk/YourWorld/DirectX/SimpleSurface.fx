float4x4 WorldViewProj : WorldViewProjection; //worldviewprojection matrix

struct VertexInput
{
	float3 Position: POSITION0;
	float3 Normal : NORMAL0;
};

struct VertexOutput
{ 
	float4 Position: POSITION0;
	float4 Normal: NORMAL0;
};

VertexOutput mainVertexShader(VertexInput Input) 
{
	VertexOutput Output = (VertexOutput)0;
	Output.Normal = float4(Input.Normal,1);
	Output.Position = mul(float4(Input.Position,1),WorldViewProj);
	return Output;
}

float4 mainPS(VertexOutput Input) : COLOR 
{
	return float4(0,0,0,1);
}	


Technique tech0
{
	pass p0 
	{
		CullMode = None;
		VertexShader = compile vs_3_0 mainVertexShader();
		PixelShader = compile ps_3_0 mainPS();
	}
}
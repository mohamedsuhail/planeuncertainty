float4x4 World: World;
texture Sprite;

sampler2D SpriteSampler = sampler_state
{
	Texture = <Sprite>;
	FILTER = MIN_MAG_MIP_POINT;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

struct VertexInput
{ 
	float2 Position : POSITION0;
	float2 TextureCoord : TEXCOORD0;
};

struct VertexOutput
{
	float4 Position : POSITION0;
	float2 TextureCoord : TEXCOORD0;
};

VertexOutput mainVertexShader(VertexInput Input)
{
	VertexOutput Output = (VertexOutput)0;
	float4 Position = float4(Input.Position.x,Input.Position.y,0,1);
	Output.Position = mul(Position, World);
	Output.TextureCoord = Input.TextureCoord;
	return Output;
}

float4 mainPS(VertexOutput Input) : COLOR
{ 

	return tex2D(SpriteSampler, Input.TextureCoord);
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
/**
	@file fur.fx
	@brief ÉtÉ@Å[
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
float4x4	g_mWorldViewProjection	: WorldViewProjection;
texture		g_DiffuseTexture		: DiffuseTexture;

float4		g_f3furColor;
float		g_fFurDistance;
int			g_nFurNumber;
texture		g_FurMap;

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler DiffuseTextureSampler = sampler_state
{
    Texture = <g_DiffuseTexture>;    
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler FurMapSampler = sampler_state
{
    Texture = <g_FurMap>;    
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

//--------------------------------------------------------------------------------------
// struct
//--------------------------------------------------------------------------------------
struct INPUT
{
	float4 pos		: POSITION;
	float3 normal	: NORMAL;
	float3 uv		: TEXCOORD0;
};
struct OUTPUT
{
	float4 pos		: POSITION;
	float3 uv		: TEXCOORD0;
};


//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
OUTPUT main_VS(INPUT IN) 
{
	OUTPUT OUT;

	float3 P = IN.pos.xyz + (IN.normal * (g_fFurDistance * g_nFurNumber));
	
	OUT.pos = mul(float4(P, 1.0f), g_mWorldViewProjection);
	OUT.uv = IN.uv;
    
	return OUT;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 main_PS( OUTPUT IN): COLOR
{
	float4 OUT = { 0.f, 0.f, 0.f, 1.f };
/*
	float4 diffuseTexture = tex2D( FurMapSampler, (IN.uv) );
	OUT.xyz = g_f3furColor.xyz * diffuseTexture.xyz;
	OUT.a *= 0.1;
 */ 
	float4 diffuseTexture = tex2D( FurMapSampler, (IN.uv) );
	OUT.xyz = g_f3furColor.xyz;
	OUT.a = diffuseTexture.a * 0.1;

	return OUT;
}

//-----------------------------------
technique render
{	
    pass P0
    {		
		VertexShader = compile vs_2_0 main_VS();
		PixelShader  = compile ps_2_0 main_PS();

		AlphaBlendEnable = true;
		SrcBlend = srcalpha;
		DestBlend = one;
    }
}
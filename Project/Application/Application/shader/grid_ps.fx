/**
	@file grid_ps.fx
	@brief グリッド描画
*/
/*
//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
//semantic
texture2D		g_DiffuseTexture: register(t0);

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler DiffuseTextureSampler =
sampler_state
{
	Texture = <g_DiffuseTexture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

*/
//--------------------------------------------------------------------------------------
// struct
//--------------------------------------------------------------------------------------
struct INPUT
{
	float4 pos		: SV_POSITION;
	float4 color	: TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 main(INPUT IN) : SV_Target
{
	float4 color;
	color = IN.color;

	return color;
}



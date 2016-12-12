/**
	@file grid_vs.fx
	@brief ƒOƒŠƒbƒh•`‰æ
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
cbuffer cbPerObject : register(b0)
{
	matrix		g_mWorldViewProjection	: packoffset(c0);
};

//--------------------------------------------------------------------------------------
// struct
//--------------------------------------------------------------------------------------
struct INPUT
{
	float4 pos		: POSITION;
	/*
	float4 nomal	: NORMAL;
	float4 color	: COLOR;
	float2 uv		: UV;
	*/
};
struct OUTPUT
{
	float4 pos		: SV_POSITION;
	float4 color	: TEXCOORD0;
};

//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
OUTPUT main( INPUT IN )
{
	OUTPUT OUT;

	OUT.pos = mul(IN.pos, g_mWorldViewProjection);
//	OUT.color = IN.color;
	OUT.color.xyzw = 1.0;

	return OUT;
}


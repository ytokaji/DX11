/**
	@file grid_vs.fx
	@brief グリッド描画
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
//semantic
float4x4	g_mWorldViewProjection	: WorldViewProjection;


//--------------------------------------------------------------------------------------
// struct
//--------------------------------------------------------------------------------------
struct INPUT
{
	float4 pos		: POSITION;
	float4 color	: TEXCOORD0;
};
struct OUTPUT
{
	float4 pos		: SV_Position;
	float4 color	: TEXCOORD0;
};

//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
OUTPUT main( INPUT IN )
{
	OUTPUT OUT;

	OUT.pos = mul(IN.pos, g_mWorldViewProjection);
	OUT.color = IN.color;

	return OUT;
}


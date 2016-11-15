/**
	@file デフォルト.fx
	@brief 標準３Dモデル描画
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
//semantic
float4x4	g_mWorldViewProjection	: WorldViewProjection;
texture		g_DiffuseTexture		: DiffuseTexture;

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


//--------------------------------------------------------------------------------------
// struct
//--------------------------------------------------------------------------------------
struct INPUT
{
	float4 pos		: POSITION;
	float3 uv		: TEXCOORD0;
};
struct OUTPUT
{
	float4 pos		: POSITION;
	float4 WPos		: TEXCOORD0;
	float3 uv		: TEXCOORD1;
};
struct PS_OUTPUT
{
   float4 color1 : COLOR0;
   float4 color2 : COLOR1;
};


//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
OUTPUT main_VS( INPUT IN
                )
{
	OUTPUT OUT;

    OUT.pos = mul( IN.pos, g_mWorldViewProjection );
	OUT.WPos = OUT.pos;
    OUT.uv = IN.uv;

	return OUT;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
PS_OUTPUT main_PS( OUTPUT IN )
{
	PS_OUTPUT OUT;
	OUT.color1 = tex2D( DiffuseTextureSampler, IN.uv );
	OUT.color2 = IN.WPos.z / IN.WPos.w;

	return OUT;
}


//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------
technique render
{
    pass P0
    {
        VertexShader = compile vs_2_0 main_VS();
        PixelShader = compile ps_2_0 main_PS();
    }
}



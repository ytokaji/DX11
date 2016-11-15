/**
	@file gaussian.fx
	@brief ガウシアンフィルタ
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
float4x4	g_mWorldViewProjection	: WorldViewProjection;

float4	g_f4UVOffset;
float2	g_2fWindowRatio;
float	g_fOffset;
float4	g_f4weight;

texture		tex;

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler TextureSampler = sampler_state
{
    Texture = <tex>;    
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
	float4 texCoord0 : TEXCOORD0;
	float4 texCoord1 : TEXCOORD1;
	float4 texCoord2 : TEXCOORD2;
	float4 texCoord3 : TEXCOORD3;
};

//-----------------------------------------------------------------------------
// func
//-----------------------------------------------------------------------------
OUTPUT texcoord_VS(INPUT IN,
					float4 i_f4UVOffset,
					float4 i_f4UVOffset1,
					float2 i_f2Offset
) 
{
	OUTPUT OUT;

    OUT.pos = IN.pos;

	OUT.texCoord0.xy = saturate(IN.uv.xy + i_f4UVOffset.xy);
	OUT.texCoord1.xy = saturate(IN.uv.xy + i_f4UVOffset.zw);
	OUT.texCoord2.xy = saturate(IN.uv.xy + i_f4UVOffset1.xy);
	OUT.texCoord3.xy = saturate(IN.uv.xy + i_f4UVOffset1.zw);

	OUT.texCoord0.zw = saturate(OUT.texCoord0.xy + i_f2Offset.xy);
	OUT.texCoord1.zw = saturate(OUT.texCoord1.xy + i_f2Offset.xy);
	OUT.texCoord2.zw = saturate(OUT.texCoord2.xy + i_f2Offset.xy);
	OUT.texCoord3.zw = saturate(OUT.texCoord3.xy + i_f2Offset.xy);

	return OUT;
}

//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
OUTPUT main_VS1(INPUT IN) 
{
	OUTPUT OUT;

	float4 f4UvOff1 = { g_f4UVOffset.x*g_2fWindowRatio.x, 0.f, g_f4UVOffset.y*g_2fWindowRatio.x, 0.f };
	float4 f4UvOff2 = { g_f4UVOffset.z*g_2fWindowRatio.x, 0.f, g_f4UVOffset.w*g_2fWindowRatio.x, 0.f };
	float2 f2Offset = { g_fOffset*g_2fWindowRatio.x, 0.f };

	OUT = texcoord_VS(IN,
					f4UvOff1,
					f4UvOff2,
					f2Offset
					);
					
	return OUT;
}
OUTPUT main_VS2(INPUT IN) 
{
	OUTPUT OUT;

	float4 f4UvOff1 = { 0.f, g_f4UVOffset.x*g_2fWindowRatio.y, 0.f, g_f4UVOffset.y*g_2fWindowRatio.y };
	float4 f4UvOff2 = { 0.f, g_f4UVOffset.z*g_2fWindowRatio.y, 0.f, g_f4UVOffset.w*g_2fWindowRatio.y };
	float2 f2Offset = { 0.f, g_fOffset*g_2fWindowRatio.y };

	OUT = texcoord_VS(IN,
					f4UvOff1,
					f4UvOff2,
					f2Offset
					);
					
	return OUT;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 main_PS( OUTPUT IN): COLOR
{
	float4 OUT = { 0.f, 0.f, 0.f, 1.f };

	OUT = g_f4weight.x  * ( tex2D( TextureSampler, IN.texCoord0.xy ) + tex2D( TextureSampler, IN.texCoord3.zw ) );
	OUT += g_f4weight.y  * ( tex2D( TextureSampler, IN.texCoord1.xy ) + tex2D( TextureSampler, IN.texCoord2.zw ) );
	OUT += g_f4weight.z  * ( tex2D( TextureSampler, IN.texCoord2.xy ) + tex2D( TextureSampler, IN.texCoord1.zw ) );
	OUT += g_f4weight.w  * ( tex2D( TextureSampler, IN.texCoord3.xy ) + tex2D( TextureSampler, IN.texCoord0.zw ) );
	
	return OUT; 
}

//-----------------------------------
technique render
{
    pass P0
    {		
		VertexShader = compile vs_2_0 main_VS1();
		PixelShader  = compile ps_2_0 main_PS();
    }
    pass P1
    {		
		VertexShader = compile vs_2_0 main_VS2();
		PixelShader  = compile ps_2_0 main_PS();
    }
}
/**
	@file brightness.fx
	@brief ãPìxíäèo
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
texture		frameTex	:	FrameBuffer;
float g_fBrightnessBias;
float2	g_2fWindowRatio;

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler frameTexSampler = sampler_state
{ 
    Texture = <frameTex>;
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
	float4 pos			: POSITION;
	float2 texCoord0	: TEXCOORD0;
	float2 texCoord1	: TEXCOORD1;
	float2 texCoord2	: TEXCOORD2;
	float2 texCoord3	: TEXCOORD3;
};

//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
OUTPUT main_VS( INPUT IN )
{
	OUTPUT OUT;

    OUT.pos = IN.pos;
	const float2 f2Offset = { 1*g_2fWindowRatio.x, 1*g_2fWindowRatio.y };
	
	OUT.texCoord0.xy = saturate(IN.uv.xy + float2( -f2Offset.x, -f2Offset.y ));
	OUT.texCoord1.xy = saturate(IN.uv.xy + float2( -f2Offset.x, f2Offset.y ));
	OUT.texCoord2.xy = saturate(IN.uv.xy + float2( f2Offset.x, -f2Offset.y ));
	OUT.texCoord3.xy = saturate(IN.uv.xy + float2( f2Offset.x, f2Offset.y));

	return OUT;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 main_PS( OUTPUT  IN
			) : COLOR
{
	float4 OUT = { 0.f, 0.f, 0.f, 1.f };

	OUT  = tex2D( frameTexSampler, IN.texCoord0 ) * 0.25f;
	OUT += tex2D( frameTexSampler, IN.texCoord1 ) * 0.25f;
	OUT += tex2D( frameTexSampler, IN.texCoord2 ) * 0.25f;
	OUT += tex2D( frameTexSampler, IN.texCoord3 ) * 0.25f;

	float fBrightness = 0.299f*OUT.r + 0.587f*OUT.g + 0.114f*OUT.b;
	clip( fBrightness - g_fBrightnessBias );

	return OUT;
}

//-----------------------------------------------------------------------------
// technique
//-----------------------------------------------------------------------------
technique render
{
    pass p0
    {
        VertexShader = compile vs_2_0 main_VS();
        PixelShader = compile ps_2_0 main_PS();
    }
}

/**
	@file poly2d.fx
	@brief ‚QDƒXƒvƒ‰ƒCƒg•`‰æ
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
texture tex;
texture frameTex		:	FrameBuffer;
texture depthTex		:	FrameBufferDepth;

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler samplerTex = sampler_state
{ 
    Texture = (tex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};
sampler frameTexsampler = sampler_state
{ 
    Texture = (frameTex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};
sampler frameDepthTexsampler = sampler_state
{ 
    Texture = (depthTex);
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
	float3 uv		: TEXCOORD0;
};

//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
OUTPUT main_VS( INPUT IN )
{
	OUTPUT OUT;

    OUT.pos = IN.pos;
    OUT.uv = IN.uv;

	return OUT;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 normal_main_PS( OUTPUT  IN
			) : COLOR
{
	float4 color = tex2D( samplerTex, IN.uv );
	return color;
}

//-----------------------------------------------------------------------------
float4 add_main_PS( OUTPUT  IN
			) : COLOR
{
	float4 color = tex2D( frameTexsampler, IN.uv );
	color += tex2D( samplerTex, IN.uv );
	return color;
}

//-----------------------------------------------------------------------------
// technique
//-----------------------------------------------------------------------------
technique normal
{
    pass p0
    {
        VertexShader = compile vs_2_0 main_VS();
        PixelShader = compile ps_2_0 normal_main_PS();
    }
}
technique add
{
    pass p0
    {
        VertexShader = compile vs_2_0 main_VS();
        PixelShader = compile ps_2_0 add_main_PS();
    }
}

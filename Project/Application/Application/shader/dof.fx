/**
	@file dof.fx
	@brief îÌé äEê[ìx
*/

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
float4x4	g_mWorldViewProjection	: WorldViewProjection;

float g_fFocusDistance;		//<! Focus Distance
float g_fFocusRange;		//!< Focus Range
float g_fNear = 1.f;		//!< Near
float g_fFar = 1.01f;		//!< Far / ( Far - Near )

texture		blurTex;
texture		frameTex	:	FrameBuffer;
texture		depthTex	:	FrameBufferDepth;

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler blurTextSampler = sampler_state
{
    Texture = <blurTex>;    
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};
sampler frameTexSampler = sampler_state
{ 
    Texture = <frameTex>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};
sampler depthTexSampler = sampler_state
{ 
    Texture = <depthTex>;
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
float4 main_PS( OUTPUT  IN
			) : COLOR
{
	float4 OUT = { 0.f, 0.f, 0.f, 1.f };
//	OUT    = tex2D( depthTexSampler, IN.uv ).r;

	float4 orig = tex2D( frameTexSampler,	IN.uv );
	float4 blur = tex2D( blurTextSampler,	IN.uv );
	float z    = tex2D( depthTexSampler, IN.uv ).r;

	float fSceneZ	= ( -g_fNear * g_fFar ) / ( z - g_fFar );

	float fBlur = saturate( abs( fSceneZ - g_fFocusDistance ) / g_fFocusRange );

//	orig = float4(1.0f,0.0f,0.0f,1.0f );
//	blur = float4(0.0f,0.0f,1.0f,1.0f );
	OUT = lerp( orig, blur, saturate(fBlur) );
/*
	float ZCenter = tex2D( depthTexSampler, IN.uv ).r;
	float len = min( 1.0f, distance( 0.5, ZCenter ) );
	OUT = lerp( tex2D( frameTexSampler, IN.uv ), tex2D( blurTextSampler, IN.uv ), len );
*/
	return OUT; 
}

//-----------------------------------
technique render
{
    pass P0
    {		
		VertexShader = compile vs_2_0 main_VS();
		PixelShader  = compile ps_2_0 main_PS();
    }
}
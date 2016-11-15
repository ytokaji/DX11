/**
	@file water.fx
	@brief 水面シェーダ
*/

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
//semantic
float4x4	g_mWorld				: World;
float4x4	g_mWorldView			: WorldView;
float4x4	g_mWorldViewProjection	: WorldViewProjection;
float3		g_f3CameraPosition		: CameraPositon;

//ps
float4		g_f4Color;				//!< 基本色味RGB
float3		g_f3SpecularColor;		//!< スペキュラ色味RGB
float2		g_f2RefrParams;			//!< 屈折のゆらぎの強さU,V(RefrScale)
float2		g_f2ReflParams;			//!< 反射のゆらぎの強さU,V(ReflScale)
float2		g_f2SpecularPower;		//!< スペキュラの強さ,しぼり
float		g_fReflBias;			//!< 反射効果のバイアス0～1(Fresnel.x)
float		g_fFresnelPower;		//!< フレネルの強さ(Fresnel.y)
float2		g_f2FrameBufferSize;	//!< 1.0/解像度
float2		g_f2WaveOffset;			//!< ＵＶオフセット
float3		g_f3WaterLightDir;		//!< 水面ライト方向

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
texture normalMap;
sampler normalMapSamp = sampler_state
{ 
    Texture = (normalMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture frameBuffer;
sampler frameBufferSamp = sampler_state
{ 
    Texture = (frameBuffer);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture reflectTex;
sampler reflectTexSamp = sampler_state
{ 
    Texture = (reflectTex);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


//-----------------------------------------------------------------------------
// vertex shader
//-----------------------------------------------------------------------------
void main_VS(	float4 i_Pos			: POSITION
			,	float3 i_Normal			: NORMAL
			,	float3 i_Tex			: TEXCOORD0
			,	out float4 o_Pos		: POSITION
			,	out float2 o_Uv			: TEXCOORD0
			,	out float2 o_Uv2		: TEXCOORD1
			,	out float4 o_WorldPos	: TEXCOORD2
			)
{	
	o_Pos = mul( i_Pos, g_mWorldViewProjection );
	o_WorldPos = mul( i_Pos, g_mWorld );

	// ノーマル用UV
	o_Uv	= i_Tex + float2(0.3,0.3);
	o_Uv2	= (i_Tex * -1.f + 1.f) + float2(0.7,0.7);
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 main_PS(	float2 i_fUv			: TEXCOORD0
			,	float2 i_fUv2			: TEXCOORD1
			,	float4 i_fWorldPos		: TEXCOORD2
			,	float4 i_fFogParams		: TEXCOORD3
			,	float4 i_fVpos			: VPOS 
		) : COLOR0
{
	float4 OUT = { 0.f, 0.f, 0.f, 1.f };

	// ゆらぎ算出
	float3 normal;
	normal.xy = ( tex2D( normalMapSamp, (i_fUv+g_f2WaveOffset) ).xw * 2.f ) - 1.f;
	normal.z  = sqrt( 1.f - ( normal.x * normal.x + normal.y * normal.y ) );
	float3 normal2;
	normal2.xy = ( tex2D( normalMapSamp, (i_fUv2+g_f2WaveOffset) ).xw * 2.f ) - 1.f;
	normal2.z  = sqrt( 1.f - ( normal2.x * normal2.x + normal2.y * normal2.y ) );
	normal = normalize(normal + normal2);

	// UV計算
	const float2 refrBump = normal.xy * g_f2RefrParams;
	const float2 reflBump = normal.xy * g_f2ReflParams;
	float2 vProj = float2( i_fVpos.x * g_f2FrameBufferSize.x, i_fVpos.y * g_f2FrameBufferSize.y);

	// 屈折
	float2 BumpUV = vProj + refrBump;
	BumpUV = saturate(BumpUV);
	
	float4 f4Refraction = tex2D(frameBufferSamp, BumpUV);
	f4Refraction.rgb = lerp( f4Refraction.rgb, g_f4Color.rgb, g_f4Color.a );
	
	// 反射
	BumpUV = vProj + reflBump.xy;
	float4 f4Reflection = tex2D( reflectTexSamp, BumpUV );
	f4Reflection.rgb = lerp( f4Reflection.rgb, g_f4Color.rgb, g_f4Color.a );

	const float3x3 mat = float3x3 ( float3(1,0,0), float3(0,0,1), float3(0,1,0) );
	const float3 V = normalize( mul( (g_f3CameraPosition.xyz - i_fWorldPos.xyz), mat ) );

	// スペキュラ
	float3 L = g_f3WaterLightDir;
	float3 cDiffuse = saturate( dot( normal, L ) );
	float3 vReflectionTS = normalize( 2 * dot( V, normal ) * normal - V );
	half RdotL = saturate( dot( vReflectionTS, L ) );
	float3 cSpecular = saturate( pow(RdotL, g_f2SpecularPower.y) ) * g_f3SpecularColor;
	float3 vSpec = (float3(1.f, 1.f, 1.f) + cDiffuse) * cSpecular;
	f4Reflection.rgb += vSpec * g_f2SpecularPower.x;

	//フレネル
	const half NdotV		= saturate( dot( V, normalize( float3( reflBump, 1 ) ) ) );
    half fresnelRefl = g_fReflBias + (1.0-g_fReflBias)*pow(NdotV, g_fFresnelPower);
	OUT = lerp( f4Refraction, f4Reflection, fresnelRefl );

	return OUT; 
}


//-----------------------------------------------------------------------------
// technique
//-----------------------------------------------------------------------------
technique render
{
    pass p0
    {
        VertexShader = compile vs_3_0 main_VS();
        PixelShader = compile ps_3_0 main_PS();
    }
}

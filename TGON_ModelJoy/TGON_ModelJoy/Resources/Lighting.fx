//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Specular_Lighting
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Specular_Lighting_Pass_0_Model : ModelData = "D:\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

struct VS_INPUT
{
    float4 mPosition : POSITION;
    float3 mNormal : NORMAL;
};


struct VS_OUTPUT
{
   float4 mPosition : POSITION;
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir : TEXCOORD2;
   float3 mReflection : TEXCOORD3;
};


float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;


float4 gWorldLightPosition
<
   string UIName = "gWorldLightPosition";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 500.00, 500.00, -500.00, 1.00 );
float4 gWorldCameraPosition : ViewPosition;


VS_OUTPUT Specular_Lighting_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;


   Output.mPosition = mul( Input.mPosition, gWorldMatrix );


   float3 lightDir = Output.mPosition.xyz - gWorldLightPosition.xyz; 
   lightDir = normalize(lightDir);
   
   
   float3 viewDir = normalize( Output.mPosition.xyz -
         gWorldCameraPosition.xyz );
   Output.mViewDir = viewDir;
   
   
   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   worldNormal = normalize( worldNormal );



   Output.mPosition = mul( Output.mPosition, gViewMatrix );
   Output.mPosition = mul( Output.mPosition, gProjectionMatrix );

   
   // diffuse light
   Output.mDiffuse = dot(-lightDir, worldNormal);

   // specular light
   Output.mReflection = reflect( lightDir, worldNormal );

   return Output;
}
struct PS_INPUT
{
   float3 mDiffuse : TEXCOORD1;
   float3 mViewDir : TEXCOORD2;
   float3 mReflection : TEXCOORD3;
};


float4 Specular_Lighting_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
   float3 diffuse = saturate(Input.mDiffuse);
   
   float3 reflection = normalize( Input.mReflection );
   float3 viewDir = normalize( Input.mViewDir );
   float3 specular = 0;
   
   if ( diffuse.x > 0 )
   {
      specular = saturate( dot( reflection, -viewDir ));
      specular = pow( specular, 20.0f );
   }
   
   float3 ambient = 0.0f;
   ambient.r = 0.3;
 
   return float4( ambient+diffuse+specular , 1);
}
//--------------------------------------------------------------//
// Technique Section for Specular_Lighting
//--------------------------------------------------------------//
technique Specular_Lighting
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Specular_Lighting_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Specular_Lighting_Pass_0_Pixel_Shader_ps_main();
   }

}


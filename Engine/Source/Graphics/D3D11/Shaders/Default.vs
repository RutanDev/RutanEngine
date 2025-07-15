struct VSInput
{
    float3 position: POSITION;
    float4 color: COLOR0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float4 color    : COLOR0;
};

cbuffer CameraMatrix : register(b0)
{
    float4x4 c_ProjectionView;
};

cbuffer ModelMatrix : register(b1)
{
    float4x4 c_Transform;
};

VSOutput Main(VSInput input)
{
    VSOutput output = (VSOutput)0;
	
    // TODO: Temp until c_Transform works
    float4x4 transform = {1,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          0,0,0,1};
    float4x4 MVP = mul(transform, c_ProjectionView);

    output.position = mul(MVP, float4(input.position, 1.0f));
    output.color = input.color;
    return output;
}
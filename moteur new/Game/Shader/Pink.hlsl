float4x4 worldViewProj;

struct VS_INPUT {
    float4 position : POSITION;
};

struct VS_OUTPUT {
    float4 position : POSITION;
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output;

    output.position = mul(input.position, worldViewProj);

    return output;
}

float4 mainPS() : COLOR{
    return float4(1.0f, 0.41f, 0.70f, 1.0f);
}

technique Default
{
    pass P0 {
        VertexShader = null; //compile vs_3_0 main();
        PixelShader = compile ps_3_0 mainPS();
    }
}
float4x4 worldViewProj;

struct VS_INPUT {
    float4 position : POSITION;
};

struct VS_OUTPUT {
    float4 position : POSITION;
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output;

    // Transformer la position du sommet dans l'espace projeté
    output.position = mul(input.position, worldViewProj);

    return output;
}

float4 mainPS() : COLOR{
    return float4(1.0f, 0.0f, 0.0f, 1.0f); // Rouge
}

technique Render {
    pass P0 {
        VertexShader = compile vs_2_0 main();
        PixelShader = compile ps_2_0 mainPS();
    }
}
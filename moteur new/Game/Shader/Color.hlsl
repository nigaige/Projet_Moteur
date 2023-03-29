// Vertex shader
struct VS_INPUT {
    float4 position : POSITION;
};

struct VS_OUTPUT {
    float4 position : POSITION;
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output;
    output.position = input.position;
    return output;
}

// Pixel shader
/*
float Time = 1.0f;

float speed = 10.0f;
*/

struct PS_INPUT {
    float4 position : POSITION;
};

struct PS_OUTPUT {
    float4 color : COLOR;
};

PS_OUTPUT ps_main(PS_INPUT input) {
    PS_OUTPUT output;

    output.color = float4(1.0f, 0.f, 0.f, 1.0f);
    return output;
}


technique Default
{
	pass p0
	{
		VertexShader = null;
		PixelShader = compile ps_3_0 ps_main();
	}
}
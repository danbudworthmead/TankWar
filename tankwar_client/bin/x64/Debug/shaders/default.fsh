#version 330

// very simple pixel shader that just samples a texture

in vec2 vUV;
in vec4 vColor;
in vec4 vColorToAlpha;

out vec4 outColour;

uniform sampler2D diffuseTexture;

void main()
{
	vec4 texColor = texture2D(diffuseTexture, vUV);
	if( distance(vColorToAlpha.rgb, texColor.rgb) < 0.15 )
	{
		discard;
	}
	outColour = texColor * vColor;
}

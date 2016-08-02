#version 330

// very simple vertex shader that just transforms an object-space
// position into clip space and passes along a texture coordinate

in vec4 Position;
in vec4 Color;
in vec2 UV;

out vec2 vUV;
out vec4 vColor;
out vec4 vColorToAlpha;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform vec4 tintColor;
uniform vec4 colorToAlpha;
uniform vec2 uvScale;
uniform vec2 uvOffset;

void main()
{
	vUV = UV * uvScale + uvOffset;
	vColor = Color * tintColor;
	vColorToAlpha = colorToAlpha;
	gl_Position = Projection * View * Model * Position;
}

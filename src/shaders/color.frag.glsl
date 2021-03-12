#version 330 core
out vec4 gl_FragColor;

in vec3 inColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	gl_FragColor = texture(ourTexture, TexCoord);
}
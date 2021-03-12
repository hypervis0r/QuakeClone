#version 330 core
out vec4 gl_FragColor;

//in vec3 inColor;
in vec2 TexCoord;

uniform vec4 inColor;
uniform sampler2D ourTexture;

void main()
{
	gl_FragColor = mix(texture(ourTexture, TexCoord), inColor, 0.2f);
}
#version 330 core

out vec4 FragColor;
in vec2 outTexCoord;

uniform sampler2D font_texture;

void main()
{   
	vec2 texCoord = vec2(outTexCoord.x, outTexCoord.y); 
	float font_alpha = texture2D(font_texture, texCoord).r;
	FragColor = vec4(0.0,0.0,0.1, font_alpha);
}
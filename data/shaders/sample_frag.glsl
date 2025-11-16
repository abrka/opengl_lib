#version 330 core

out vec4 FragColor;
in vec3 fragWorldPosition;
in vec2 outTexCoord;

uniform sampler2D font_texture;

void main()
{   
	vec2 texCoord = vec2(outTexCoord.x, 1.0 - outTexCoord.y); 
	texCoord *= 10.0;
	vec4 font_color = texture2D(font_texture, texCoord);
	FragColor = vec4(font_color.rrr, 1.0);
}
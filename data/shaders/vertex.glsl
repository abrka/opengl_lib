#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 fragWorldPosition;
out vec2 outTexCoord;

uniform mat4 uModel;

void main()
{
										
	fragWorldPosition = (uModel * vec4(aPos, 1.0)).xyz;
	outTexCoord = aTexCoord;
	gl_Position = uModel * vec4(aPos, 1.0);
}
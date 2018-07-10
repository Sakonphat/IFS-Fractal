#version 330 core

in vec3 Position;
in vec3 Normal;

uniform vec3 Kd; 	
uniform vec3 Ld; 		
uniform float Shininess;
uniform vec3 LightPosition; 		
uniform mat4 ViewMatrix;

out vec4 Color0;

void main( void )
{
	Color0 = vec4(Kd, 1.0);
}

#version 130


uniform vec3 Color; 	
out vec4 Color0;

void main( void )
{
	Color0 = vec4(Color, 1.0);
}

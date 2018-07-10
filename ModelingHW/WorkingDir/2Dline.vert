#version 130 


in vec3 VertexPosition;
uniform mat4 MVP;



void main( void )
{
	gl_Position = MVP * vec4(VertexPosition,1.0f);
}

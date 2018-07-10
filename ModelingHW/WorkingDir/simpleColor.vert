#version 330 core


layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
		
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

out vec3 Position;
out vec3 Normal;

void main( void )
{
	//send Vertex positoin & normal or PS to compute  lighting
	Normal = normalize( (ModelViewMatrix * vec4(VertexNormal,0)).xyz);
	Position = vec3( ModelViewMatrix * vec4(VertexPosition,1.0) );

	//transform vertex poistion
	gl_Position = MVP * vec4(VertexPosition,1.0f);
}

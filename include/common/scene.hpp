#ifndef SCENE_H
#define SCENE_H

struct MyObject
{
	//3d data, non-share vertex array for rendering
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint              num_vertex;
	GLuint              vertexVB;           //Vertex Buffer (VB), openGL internal data
	GLuint              vertexVB;
	GLuint              vertexVB;

	//model transformation
	glm::vec3           position;
	glm::vec3           rotation;
	float               scale;
	glm::mat4           modelMatrix;

	//material data
	glm::vec3           modelColor;
	int                 material;           //0 = diffuse, 1 = phong(hi-light)
	float               shininess;          //for phong only
	int                 useTexture;         //0 = use texture, 1 = use color

	//tex data
	QImage              texImg;
	GLuint              textureID;          //openGL pointer to texture data
};


struct MyLight
{
	glm::vec3           position;
	glm::vec3           color;
	int                 type;               //0 = point light, 1 = directional light
};


#endif
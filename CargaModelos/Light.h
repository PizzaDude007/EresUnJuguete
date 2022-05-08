#pragma once

#include <glew.h>
#include <glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
			GLfloat aIntensity, GLfloat dIntensity);
	void setAmbienIntensity(GLfloat aIntensity) { ambientIntensity = aIntensity; }
	void setDiffuseIntensity(GLfloat dIntensity) { diffuseIntensity = dIntensity; }

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};


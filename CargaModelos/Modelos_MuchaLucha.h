#pragma once
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//glm::mat4 frijolito();
//glm::mat4 personaLuchador();
//glm::mat4 personaLuchador(float x, float y, float z);

class Modelos_MuchaLucha
{
public:
	Modelos_MuchaLucha();
	void RenderModels(GLuint color, GLuint model);
	~Modelos_MuchaLucha();
private:
	Model ML_Ring_M = Model();
	GLuint uniformModel = 0;
	GLuint uniformColor = 0;
};
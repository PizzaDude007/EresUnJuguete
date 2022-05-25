#pragma once
#include<glew.h>
#include<glfw3.h>
#include <glm.hpp>

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include"Model.h"

#include "Shader_light.h"

class Toroide
{
public:
	Toroide(double radioMin, double radioMax, int resolucion);
	~Toroide();
	void CrearToroide(std::vector<Mesh*> *meshList);

private:

	double alpha, betha;
	const float PI = 3.14159265f;
	std::vector<float> puntos;
	std::vector<unsigned int> indicesT;
	int conIndices, resolution;
	double radioMinimo, radioMaximo;

};



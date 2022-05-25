#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "definition.h"
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <stdlib.h>
#include "Mesh.h"

class Torus_P
{
public:
	Torus_P();
	Torus_P(int ladosCilindro, int ladosCirculo, float grosor);
	void init();
	void load();
	void render();
	void changeParams(int ladosCilindro, int ladosCirculo, float grosor);
	~Torus_P();

private:
	int i, j, k, ladosCilindro, ladosCirculo;
	float grosor;
	unsigned int indiceCount;
	GLfloat s, t, x, y, z, mod;
	const double twopi = 2 * 3.14159265358979323846;

	std::vector<VertexColor> vertices;
	std::vector<GLuint>indices;

	GLuint VAO, VBO, EBO;

	//Mesh * toro;
};
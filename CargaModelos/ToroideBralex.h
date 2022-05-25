/*
 * toroide.h
 */


#ifndef TOROIDE_H_
#define TOROIDE_H_
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include "definition.h"




class ToroideBralex
{
public:
	ToroideBralex(double alpha,double betha);
	void CrearToroide();
	void init();
	void load();
	void render();
	virtual ~ToroideBralex();

private:
	std::vector<VertexColor> vertexC;
	std::vector<GLuint> index;
	double radio1, radio2;
	const float PI = 3.14159265f;
	int conIndices=0;
	//MODEL_MODE mode;

	GLuint VAO, VBO, EBO;
};


#endif /* TOROIDE_H_ */
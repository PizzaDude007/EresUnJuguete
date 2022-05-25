#include "ToroideBralex.h"



ToroideBralex::ToroideBralex(double radio1, double radio2): 
	radio1(radio1), radio2(radio2), VAO(0), VBO(0), EBO(0) {
}

ToroideBralex::~ToroideBralex()
{

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
}

void ToroideBralex::init() {
	
	//float radio2 = 1.5f;
	//float radio1 = 0.7f;
	float ancho = radio2-radio1;
	float alpha, betha;
	//CREACION DEL TOROIDE
	for (int i = 0; i < 100; i++) { //Num C = 100, numC: Numero de caras del circulo interno (el que recorre al externo)
		for (int j = 0; j <= 100; j++) { //Num T = 100, numT: es el nuero de caras del circulo externo
			for (int k = 1; k >= 0; k--) { //num C
				alpha = (i + k) % 100 + 0.5; //alpha = (i + k) % numC + 0.5;
				betha = j % 100; //betha = j % numt
				
				//x = (1 + .1 * cos(s * 2 * PI / numc)) * cos(t * 2 * PI / numt)
				float X = (radio2 + ancho * cos(alpha * 2 * PI / 100)) * cos(betha * 2 * PI / 100); //S es alpha, t es betha

				//y = (1 + .1 * cos(s * 2 * PI / numc)) * sin(t * 2 * PI / numt)
				float Z = (radio2 + ancho * cos(alpha * 2 * PI / 100)) * sin(betha * 2 * PI / 100);//S es alpha, t es betha

				//z = .1 * sin(s * 2 * PI / numc);
				float Y = ancho * sin(alpha * 2 * PI / 100);//S es alpha, t es betha

				VertexColor v = VertexColor(glm::vec3(X, Y, Z), glm::sphericalRand(1.0));
				vertexC.push_back(v);
				
				//triangulo pegado anterior
				index.push_back(conIndices - 1);
				index.push_back(conIndices);
				index.push_back(conIndices + 1);

				//triangulo actual
				index.push_back(conIndices);
				conIndices++;
				index.push_back(conIndices);
				conIndices++;
				index.push_back(conIndices);
				conIndices++;

				//triangulo pegado siguiente
				index.push_back(conIndices - 2);
				index.push_back(conIndices - 1);
				index.push_back(conIndices);

			}
		}
	}

}


void ToroideBralex::load() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	size_t stride;

	size_t offset1 = 0;
	size_t offset2 = 0;
	size_t offset3 = 0;

	glBufferData(GL_ARRAY_BUFFER, vertexC.size() * sizeof(glm::vec3) * 2,
		vertexC.data(),
		GL_STATIC_DRAW);
	stride = sizeof(vertexC[0]);
	offset1 = 0;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint),
		index.data(),
		GL_STATIC_DRAW);

	// First attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset1);
	glEnableVertexAttribArray(0);
	// Second attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
		(GLvoid*)offset2);
	glEnableVertexAttribArray(1);
	// Thrid attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset3);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

}

void ToroideBralex::render() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT,
		(GLvoid*)(sizeof(GLuint) * 0));
	glBindVertexArray(0);

}


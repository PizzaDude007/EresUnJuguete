#include "Torus_P.h"

Torus_P::Torus_P() {
	changeParams(8, 25, 0.4);
}

Torus_P::Torus_P(int ladosCilindro, int ladosCirculo, float grosor)
{
	changeParams(ladosCilindro, ladosCirculo, grosor);
}

void Torus_P::render() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT,
		(GLvoid*)(sizeof(GLuint) * 0));
	glBindVertexArray(0);
}

void Torus_P::changeParams(int ladosCilindro, int ladosCirculo, float grosor) {
	this->vertices.clear();
	this->indices.clear();

	this->ladosCilindro = ladosCilindro;
	this->ladosCirculo = ladosCirculo;
	this->grosor = grosor;
}

void Torus_P::init() {
	indiceCount = 0;

	VertexColor vertice = VertexColor();

	for (i = 0; i < ladosCilindro; i++) {
		for (j = 0; j <= ladosCirculo; j++) {
			//if (i == 0 || j == 0) j = 1;
			for (k = 1; k >= 0; k--) {
				s = (i + k) % ladosCilindro + 0.5;
				t = j % ladosCirculo;

				x = (1 + grosor * cos(s * twopi / ladosCilindro)) * cos(t * twopi / ladosCirculo);
				y = (1 + grosor * cos(s * twopi / ladosCilindro)) * sin(t * twopi / ladosCirculo);
				z = grosor * sin(s * twopi / ladosCilindro);

				//mod = sqrt(x * x + y * y + z * z);

				indiceCount++;
				indices.push_back(indiceCount);
				
				vertice = VertexColor();
				vertice.position = glm::vec3(x, y, z);
				vertice.color = glm::sphericalRand(1.0);
				vertices.push_back(vertice);
			}
		}
	}
}

void Torus_P::load() {
	init();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	size_t stride;

	size_t offset1 = 0;
	size_t offset2 = 0;
	size_t offset3 = 0;

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3) * 2,
		vertices.data(),
		GL_STATIC_DRAW);
	stride = sizeof(vertices[0]);
	offset1 = 0;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
		indices.data(),
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

Torus_P::~Torus_P()
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
	//toro->ClearMesh();
}
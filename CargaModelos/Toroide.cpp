#include "Toroide.h"



Toroide::Toroide(double radioMin, double radioMax) {
	radioMaximo = radioMax;
	radioMinimo = radioMin;
	
}

void Toroide::CrearToroide(std::vector<Mesh*> *meshList) {

	//CREACION DEL TOROIDE
	for (int i = 0; i < 100; i++) { //Num C = 100, numC: Numero de caras del circulo interno (el que recorre al externo)
		for (int j = 0; j <= 100; j++) { //Num T = 100, numT: es el nuero de caras del circulo externo
			for (int k = 1; k >= 0; k--) { //num C
				alpha = (i + k) % 100 + 0.5; //alpha = (i + k) % numC + 0.5;
				betha = j % 100; //betha = j % numt

				//x = (1 + .1 * cos(s * 2 * PI / numc)) * cos(t * 2 * PI / numt)
				puntos.push_back((radioMaximo + (radioMaximo - radioMinimo) * cos(alpha * 2 * PI / 100)) * cos(betha * 2 * PI / 100)); //S es alpha, t es betha

				//y = (1 + .1 * cos(s * 2 * PI / numc)) * sin(t * 2 * PI / numt)
				puntos.push_back((radioMaximo + (radioMaximo - radioMinimo) * cos(alpha * 2 * PI / 100)) * sin(betha * 2 * PI / 100));//S es alpha, t es betha

				//z = .1 * sin(s * 2 * PI / numc);
				puntos.push_back((radioMaximo - radioMinimo) * sin(alpha * 2 * PI / 100));//S es alpha, t es betha

				indicesT.push_back(conIndices - 1);
				indicesT.push_back(conIndices);
				indicesT.push_back(conIndices + 1);

				indicesT.push_back(conIndices);
				conIndices++;
				indicesT.push_back(conIndices);
				conIndices++;
				indicesT.push_back(conIndices);
				conIndices++;

				indicesT.push_back(conIndices - 2);
				indicesT.push_back(conIndices - 1);
				indicesT.push_back(conIndices );
			}
		}
	}
	Mesh* Toroide = new Mesh();
	Toroide->CreateMeshToro(&puntos[0], &indicesT[0], puntos.size(), indicesT.size());
	meshList->push_back(Toroide);

}

Toroide::~Toroide()
{
}
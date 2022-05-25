/*
Semestre 2022-2
PROYECTO FINAL
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
//#include <gtc\matrix_transform.hpp>
//#include <gtc\type_ptr.hpp>
#include <irrklang\irrKlang.h>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

#include "KeyFrames.h"


//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Toroide.h"

//NAME SPACE
using namespace irrklang;

//#include "Modelos_MuchaLucha.h"

float contadorDiaNoche = 0.0f;
float posicionLedX, posicionLedZ, posicionLed1X, posicionLed1Z, parpadeoSpike = 0.0f;
float SpectreRotX, SpectreRotY, SpectreMovX, SpectreMovY, SpectreMovZ, AuxSpectreRotX;
float FenixBIrotX, FenixRot;
float KillJBrazosRotX, KillJRotY, KillJRotX, KillJPIrotX, KillJPDrotX, KillJMovZ;
int banderaLedCama, banderaLedEscritorio, LedCama, banderaParpadeoSpike, AnimacionVal, DisparoSpectre, KillJCamina, LampVal;
bool  dia = false, spikeSube = false, cancionVal = true;
double alpha, betha;
const float toRadians = 3.14159265f / 180.0f;
const float PI = 3.14159265f;

float giroSpike = 0.0f;
float movAroSpike = 0.0f;

float rotBrazo[3] = { 0.0f,0.0f,0.0f };
float rotPierna[3] = { 0.0f,0.0f,0.0f };
float rotDireccion[3] = { 0.0f,0.0f,0.0f };


float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, ciclo_x, ciclo_x2, ciclo_d, ciclo_d2, ciclo_g, ciclo_g2, ciclo_y, ciclo_y2, contador = 0;
void inputKeyframes(bool* keys,int action);


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//Camaras
Camera * camera;
Camera cameraLibre;
Camera cameraWheezy;
Camera cameraJett;
Camera cameraFrijolito;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture plainBlueTexture;
Texture pisoTexture;

Texture WheezyTexture;
Texture FrijolitoTexture;
Texture JettTexture;

//Mucha Lucha
Texture StreetMan1_Texture;
Texture StreetMan2_Texture;
Texture StreetMan3_Texture;
Texture Ricochet_Texture;
Texture La_Pulga_Texture;
Texture Buena_Girl_Texture;


Model Cuarto_M = Model();
Model Escritorio_M = Model();
Model Escritorio2_M = Model();
Model Escritorio3_M = Model();
Model Lampara_M = Model();
Model Dado_M = Model();
Model Cubo_M = Model();
Model Silla_M = Model();
Model Bote_basura_M = Model();
Model Puff_M = Model();
Model SetUp_M = Model();
Model Gabinete_M = Model();
Model HeadSet_M = Model();
Model LuzTecho_M = Model();
Model JettCompleta = Model();
Model Cama_M = Model();
Model Alfombra_M = Model();
Model Mueble_M = Model();
Model Rampa_M = Model();
Model Leds_M = Model();
Model Leds_mini_M = Model();
Model Helicoptero_M = Model();
Model Helice_M = Model();

Model White_Helicopter_M = Model();
Model White_Helicopter_Helice_M = Model();
Model White_Helicopter_Rotor_M = Model();
Model Helipad_M = Model();

Model Helipuerto_M = Model();
Model Helicoptero_Bryan = Model();
Model Rotor_Bryan = Model();
Model Helice_Bryan = Model();

//TOY STORY
Model Casita_M = Model();
Model Arbolito_M = Model();
Model Edificio_M = Model();
Model Edificio2_M = Model();
Model Car_M = Model();
Model Bus_M = Model();
Model CuboR_M = Model();

//Wheezy
Model Wheezy_torso_M = Model();
Model Wheezy_cabeza_M = Model();
Model Wheezy_brazo_izq_M = Model();
Model Wheezy_brazo_der_M = Model();
Model Wheezy_pie_izq_M = Model();
Model Wheezy_pie_der_M = Model();

//V A L O R A N T
Model Valorant_Gosth_M = Model();
Model Valorant_Spectre_M = Model();
Model Valorant_Banca_Madera = Model();
Model Valorant_Balde_M = Model();
Model Valorant_Malla_M = Model();
Model Valorant_CajaMadera_M = Model();
Model Valorant_CajaMadera2_M = Model();
Model Valorant_KillJC = Model(); //Carad torso de KillJoy
Model Valorant_KillJBI = Model();// Brazo Izq
Model Valorant_KillJBD = Model();//Brazo Derecho
Model Valorant_KillJPI = Model();//Pie Izq
Model Valorant_KillJPD = Model();//Pie Derecho
Model Valorant_FenixC = Model(); //Carad torso de Fenix
Model Valorant_FenixBI = Model();// Brazo Izq
Model Valorant_FenixBD = Model();//Brazo Derecho
Model Valorant_FenixPI = Model();//Pie Izq
Model Valorant_FenixPD = Model();//Pie Derecho
//Valorant
Model Spike_base_M = Model();
Model Spike_cilindro_M = Model();
Model Spike_aro_M = Model();
Model LamparaVal_M = Model();

Model ML_Ring_M = Model();
Model Luchador_M = Model();

Skybox skybox;
//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLightsNoche[MAX_POINT_LIGHTS];
PointLight pointLightsCama[MAX_POINT_LIGHTS];
PointLight pointLightsSpike[MAX_POINT_LIGHTS];//Todas las pointlights
PointLight pointLightsSpike1[MAX_POINT_LIGHTS];//Pointlights sin los leds de la cama y el escritorio
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotlights1[MAX_SPOT_LIGHTS];//Arreglo con otra spotlight

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

Sphere sp = Sphere(10.0, 30, 30); //radio horizontal vertical





//c�lculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateStar()
{
	unsigned int indices[] = {
		0, 1, 2,
		3, 4, 5,
		5, 6, 7,
		7, 8, 9,
		9, 10, 11,
		2, 1, 9,
		1, 5, 9,
		5, 7, 9
	};

	GLfloat vertices[] = {
		//		x      		y 		     z				u	  v			nx	  ny    nz
			0.054193f, -0.55023f, 0.83147f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.15008f,  -0.12317f, 0.98079f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			-0.13795f,  -0.13795f, 0.98079f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			
			0.15008f,  -0.12317f, 0.98079f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.55023f,  -0.054193f, 0.83147f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.25788f,  0.12742f, 0.95233f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,

			0.30866f,  0.46194f, 0.83147f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.037329f,  0.28521f, 0.95233f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,

			-0.34285f,  0.39285f, 0.83147f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			-0.27245f,  0.092253f, 0.95233f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,

			-0.53089f,  -0.11439f, 0.83147f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			-0.13795f,  -0.13795f, 0.98079f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,

	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	//En create objects: 
	unsigned int vegetacionIndices[] = {
			0, 1, 2,
			0, 2, 3,
			4,5,6,
			4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 24, vertices, 96, 8, 5);


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 96, 24);
	meshList.push_back(obj1);

}

void CreatePersonaje() {
	unsigned int indices[] = {
		//arriba
		0,1,2,		//0, 1, 2,
		3,4,5,		//1, 2, 3,
		//izq
		6,7,8,		//0, 2, 4,
		9,10,11,	//2, 4, 6,
		//atras
		12,13,14,	//0, 1, 5,
		15,16,17,	//0, 4, 5,
		//der
		18,19,20,	//1, 3, 5,
		21,22,23,	//3, 5, 7,
		//abajo
		24,25,26,	//4, 5, 6,
		27,28,29,	//5, 6, 7
		//frente
		30,31,32,	//2, 3, 6,
		33,34,35,	//3, 6, 7,
	};

	GLfloat verticesCabeza[] = {
		//	x      y      z			u	  v				nx	  ny    nz
			//arriba
			-0.25f, 0.25f, -0.25f,	0.125f, 1.0f,		0.0f, 1.0f, 0.0f, //0
			0.25f, 0.25f, -0.25f,	0.250f, 1.0f,		0.0f, 1.0f, 0.0f, //1
			-0.25f, 0.25f, 0.25f,	0.125f, 0.875f,		0.0f, 1.0f, 0.0f, //2

			0.25f, 0.25f, -0.25f,	0.250f, 1.0f,		0.0f, 1.0f, 0.0f, //1
			-0.25f, 0.25f, 0.25f,	0.125f, 0.875f,		0.0f, 1.0f, 0.0f, //2
			0.25f, 0.25f, 0.25f,	0.250f, 0.875f,		0.0f, 1.0f, 0.0f, //3

			//izq
			-0.25f, 0.25f, -0.25f,	0.0f, 0.875f,		-1.0f, 0.0f, 0.0f, //0
			-0.25f, 0.25f, 0.25f,	0.125f, 0.875f,		-1.0f, 0.0f, 0.0f, //2
			-0.25f, -0.25f, -0.25f,	0.0f, 0.75f,		-1.0f, 0.0f, 0.0f, //4

			-0.25f, 0.25f, 0.25f,	0.125f, 0.875f,		-1.0f, 0.0f, 0.0f, //2
			-0.25f, -0.25f, -0.25f,	0.0f, 0.75f,		-1.0f, 0.0f, 0.0f, //4
			-0.25f, -0.25f, 0.25f,	0.125f, 0.75f,		-1.0f, 0.0f, 0.0f, //6

			//atras
			-0.25f, 0.25f, -0.25f,	0.375f, 0.875f,		0.0f, 0.0f, -1.0f, //0
			0.25f, 0.25f, -0.25f,	0.5f, 0.875f,		0.0f, 0.0f, -1.0f, //1
			0.25f, -0.25f, -0.25f,	0.5f, 0.75f,		0.0f, 0.0f, -1.0f, //5

			-0.25f, 0.25f, -0.25f,	0.375f, 0.875f,		0.0f, 1.0f, -1.0f, //0
			-0.25f, -0.25f, -0.25f,	0.5f, 0.75f,		0.0f, 0.0f, -1.0f, //4
			0.25f, -0.25f, -0.25f,	0.5f, 0.75f,		0.0f, 0.0f, -1.0f, //5

			//der
			0.25f, 0.25f, -0.25f,	0.5f, 0.875f,		1.0f, 0.0f, 0.0f, //1
			0.25f, 0.25f, 0.25f,	0.25f, 0.875f,		1.0f, 0.0f, 0.0f, //3
			0.25f, -0.25f, -0.25f,	0.5f, 0.75f,		1.0f, 0.0f, 0.0f, //5

			0.25f, 0.25f, 0.25f,	0.25f, 0.875f,		1.0f, 0.0f, 0.0f, //3
			0.25f, -0.25f, -0.25f,	0.5f, 0.75f,		1.0f, 0.0f, 0.0f, //5
			0.25f, -0.25f, 0.25f,	0.25f, 0.75f,		1.0f, 0.0f, 0.0f, //7

			//abajo
			-0.25f, -0.25f, -0.25f,	0.25f, 1.0f,		0.0f, -1.0f, 0.0f, //4
			0.25f, -0.25f, -0.25f,	0.375f, 1.0f,		0.0f, -1.0f, 0.0f, //5
			-0.25f, -0.25f, 0.25f,	0.25f, 0.875f,		0.0f, -1.0f, 0.0f, //6

			0.25f, -0.25f, -0.25f,	0.375f, 1.0f,		0.0f, -1.0f, 0.0f, //5
			-0.25f, -0.25f, 0.25f, 0.25f, 0.875f,		0.0f, -1.0f, 0.0f, //6
			0.25f, -0.25f, 0.25f,	0.375f, 0.875f,		0.0f, -1.0f, 0.0f, //7

			//frente
			-0.25f, 0.25f, 0.25f,	0.125f, 0.875f,		0.0f, 0.0f, 1.0f, //2
			0.25f, 0.25f, 0.25f,	0.25f, 0.875f,		0.0f, 0.0f, 1.0f, //3
			-0.25f, -0.25f, 0.25f,	0.125f, 0.75f,		0.0f, 0.0f, 1.0f, //6

			0.25f, 0.25f, 0.25f,	0.25f, 0.875f,		0.0f, 0.0f, 1.0f, //3
			-0.25f, -0.25f, 0.25f,	0.125f, 0.75f,		0.0f, 0.0f, 1.0f, //6
			0.25f, -0.25f, 0.25f,	0.25f, 0.75f,		0.0f, 0.0f, 1.0f, //7
	};

	GLfloat verticesTorso[] = {
		//	x      y      z				u	  v				nx	  ny    nz
			//arriba
			-0.25f, 0.375f, -0.125f,	0.4375f, 0.5f,		0.0f, 1.0f, 0.0f, //0
			0.25f, 0.375f, -0.125f,		0.5625f, 0.5f,		0.0f, 1.0f, 0.0f, //1
			-0.25f, 0.375f, 0.125f,		0.4375f, 0.4375f,	0.0f, 1.0f, 0.0f, //2

			0.25f, 0.375f, -0.125f,		0.5625f, 0.5f,		0.0f, 1.0f, 0.0f, //1
			-0.25f, 0.375f, 0.125f,		0.4375f, 0.4375f,	0.0f, 1.0f, 0.0f, //2
			0.25f, 0.375f, 0.125f,		0.5625f, 0.4375f,	0.0f, 1.0f, 0.0f, //3

			//izq
			-0.25f, 0.375f, -0.125f,	0.25f, 0.4375f,		-1.0f, 0.0f, 0.0f, //0
			-0.25f, 0.375f, 0.125f,		0.3125f, 0.4375f,	-1.0f, 0.0f, 0.0f, //2
			-0.25f, -0.375f, -0.125f,	0.25f, 0.25f,		-1.0f, 0.0f, 0.0f, //4

			-0.25f, 0.375f, 0.125f,		0.3125f, 0.4375f,	-1.0f, 0.0f, 0.0f, //2
			-0.25f, -0.375f, -0.125f,	0.25f, 0.25f,		-1.0f, 0.0f, 0.0f, //4
			-0.25f, -0.375f, 0.125f,	0.3125f, 0.25f,		-1.0f, 0.0f, 0.0f, //6

			//atras
			-0.25f, 0.375f, -0.125f,	0.4375f, 0.4375f,	0.0f, 0.0f, -1.0f, //0
			0.25f, 0.375f, -0.125f,		0.5625f, 0.4375f,	0.0f, 0.0f, -1.0f, //1
			0.25f, -0.375f, -0.125f,	0.5625f, 0.25f,		0.0f, 0.0f, -1.0f, //5

			-0.25f, 0.375f, -0.125f,	0.4375f, 0.4375f,	0.0f, 1.0f, -1.0f, //0
			-0.25f, -0.375f, -0.125f,	0.4375f, 0.25f,		-1.0f, 0.0f, -1.0f, //4
			0.25f, -0.375f, -0.125f,	0.5625f, 0.25f,		0.0f, 0.0f, -1.0f, //5

			//der
			0.25f, 0.375f, -0.125f,		0.5625f, 0.4375f,	0.0f, 0.0f, 1.0f, //1
			0.25f, 0.375f, 0.125f,		0.625f, 0.4375f,	0.0f, 0.0f, 1.0f, //3
			0.25f, -0.375f, -0.125f,	0.5625f, 0.25f,		0.0f, 0.0f, 1.0f, //5

			0.25f, 0.375f, 0.125f,		0.625f, 0.4375f,	0.0f, 0.0f, 1.0f, //3
			0.25f, -0.375f, -0.125f,	0.5625f, 0.25f,		0.0f, 0.0f, 1.0f, //5
			0.25f, -0.375f, 0.125f,		0.625f, 0.25f,		0.0f, 0.0f, 1.0f, //7

			//abajo
			-0.25f, -0.375f, -0.125f,	0.4375f, 0.5f,		0.0f, 0.0f, 1.0f, //4
			0.25f, -0.375f, -0.125f,	0.5625f, 0.5f,		0.0f, 0.0f, 1.0f, //5
			-0.25f, -0.375f, 0.125f,	0.4375f, 0.4375f,	0.0f, 0.0f, 1.0f, //6

			0.25f, -0.375f, -0.125f,	0.5625f, 0.5f,		0.0f, 0.0f, 0.0f, //5
			-0.25f, -0.375f, 0.125f,	0.4375f, 0.4375f,	0.0f, 0.0f, 0.0f, //6
			0.25f, -0.375f, 0.125f,		0.5625f, 0.4375f,	0.0f, 0.0f, 0.0f, //7

			//frente
			-0.25f, 0.375f, 0.125f,		0.3125f, 0.4375f,	0.0f, 0.0f, 1.0f, //2
			0.25f, 0.375f, 0.125f,		0.4375f, 0.4375f,	0.0f, 0.0f, 1.0f, //3
			-0.25f, -0.375f, 0.125f,	0.3125f, 0.25f,		0.0f, 0.0f, 1.0f, //6

			0.25f, 0.375f, 0.125f,		0.4375f, 0.4375f,	0.0f, 0.0f, 1.0f, //3
			-0.25f, -0.375f, 0.125f,	0.3125f, 0.25f,		0.0f, 0.0f, 1.0f, //6
			0.25f, -0.375f, 0.125f,		0.4375f, 0.25f,		0.0f, 0.0f, 1.0f, //7
	};

	GLfloat verticesBrazo[] = {
		//	x      y      z				u	  v				nx	  ny    nz
			//arriba
			-0.1f, 0.375f, -0.125f,		0.6875f, 0.75f,		0.0f, 1.0f, 0.0f, //0
			0.1f, 0.375f, -0.125f,		0.734375f, 0.75f,	0.0f, 1.0f, 0.0f, //1
			-0.1f, 0.375f, 0.125f,		0.6875f, 0.6875f,	0.0f, 1.0f, 0.0f, //2

			0.1f, 0.375f, -0.125f,		0.734375f, 0.75f,	0.0f, 1.0f, 0.0f, //1
			-0.1f, 0.375f, 0.125f,		0.6875f, 0.6875f,	0.0f, 1.0f, 0.0f, //2
			0.1f, 0.375f, 0.125f,		0.734375f, 0.5f,	0.0f, 1.0f, 0.0f, //3

			//izq
			-0.1f, 0.375f, -0.125f,		0.625f, 0.6875f,	-1.0f, 0.0f, 0.0f, //0
			-0.1f, 0.375f, 0.125f,		0.6875f, 0.6875f,	-1.0f, 0.0f, 0.0f, //2
			-0.1f, -0.375f, -0.125f,	0.625f, 0.5f,		-1.0f, 0.0f, 0.0f, //4

			-0.1f, 0.375f, 0.125f,		0.6875f, 0.6875f,	-1.0f, 0.0f, 0.0f, //2
			-0.1f, -0.375f, -0.125f,	0.625f, 0.5f,		-1.0f, 0.0f, 0.0f, //4
			-0.1f, -0.375f, 0.125f,		0.6875f, 0.5f,		-1.0f, 0.0f, 0.0f, //6

			//atras
			-0.1f, 0.375f, -0.125f,		0.734375f, 0.6875f,	0.0f, 0.0f, -1.0f, //0
			0.1f, 0.375f, -0.125f,		0.78125f, 0.6875f,	0.0f, 0.0f, -1.0f, //1
			0.1f, -0.375f, -0.125f,		0.78125f, 0.5f,		0.0f, 0.0f, -1.0f, //5

			-0.1f, 0.375f, -0.125f,		0.734375f, 0.6875f,	0.0f, 1.0f, -1.0f, //0
			-0.1f, -0.375f, -0.125f,	0.734375f, 0.5f,	-1.0f, 0.0f, -1.0f, //4
			0.1f, -0.375f, -0.125f,		0.78125f, 0.5f,		0.0f, 0.0f, -1.0f, //5

			//der
			0.1f, 0.375f, -0.125f,		0.78125f, 0.6875f,	0.0f, 0.0f, 1.0f, //1
			0.1f, 0.375f, 0.125f,		0.84375f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			0.1f, -0.375f, -0.125f,		0.78125f, 0.5f,		0.0f, 0.0f, 1.0f, //5

			0.1f, 0.375f, 0.125f,		0.84375f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			0.1f, -0.375f, -0.125f,		0.78125f, 0.5f,		0.0f, 0.0f, 1.0f, //5
			0.1f, -0.375f, 0.125f,		0.84375f, 0.5f,		0.0f, 0.0f, 1.0f, //7

			//abajo
			-0.1f, -0.375f, -0.125f,	0.734375f, 0.75f,	0.0f, 0.0f, 1.0f, //4
			0.1f, -0.375f, -0.125f,		0.78125f, 0.75f,	0.0f, 0.0f, 1.0f, //5
			-0.1f, -0.375f, 0.125f,		0.734375f, 0.6875f,	0.0f, 0.0f, 1.0f, //6

			0.1f, -0.375f, -0.125f,		0.78125f, 0.75f,	0.0f, 0.0f, 0.0f, //5
			-0.1f, -0.375f, 0.125f,		0.734375f, 0.6875f,	0.0f, 0.0f, 0.0f, //6
			0.1f, -0.375f, 0.125f,		0.78125f, 0.6875f,	0.0f, 0.0f, 0.0f, //7

			//frente
			-0.1f, 0.375f, 0.125f,		0.6875f, 0.6875f,	0.0f, 0.0f, 1.0f, //2
			0.1f, 0.375f, 0.125f,		0.734375f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			-0.1f, -0.375f, 0.125f,		0.6875f, 0.5f,		0.0f, 0.0f, 1.0f, //6

			0.1f, 0.375f, 0.125f,		0.734375f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			-0.1f, -0.375f, 0.125f,		0.6875f, 0.5f,		0.0f, 0.0f, 1.0f, //6
			0.1f, -0.375f, 0.125f,		0.734375f, 0.5f,	0.0f, 0.0f, 1.0f, //7
	};

	GLfloat verticesPierna[] = {
		//	x      y      z				u	  v				nx	  ny    nz
			//arriba
			-0.125f, 0.375f, -0.125f,	0.0625f, 0.75f,		0.0f, 1.0f, 0.0f, //0
			0.125f, 0.375f, -0.125f,	0.125f, 0.75f,		0.0f, 1.0f, 0.0f, //1
			-0.125f, 0.375f, 0.125f,	0.0625f, 0.6875f,	0.0f, 1.0f, 0.0f, //2

			0.125f, 0.375f, -0.125f,	0.125f, 0.75f,		0.0f, 1.0f, 0.0f, //1
			-0.125f, 0.375f, 0.125f,	0.0625f, 0.6875f,	0.0f, 1.0f, 0.0f, //2
			0.125f, 0.375f, 0.125f,		0.125f, 0.5f,		0.0f, 1.0f, 0.0f, //3

			//izq
			-0.125f, 0.375f, -0.125f,	0.0f, 0.6875f,		-1.0f, 0.0f, 0.0f, //0
			-0.125f, 0.375f, 0.125f,	0.0625f, 0.6875f,	-1.0f, 0.0f, 0.0f, //2
			-0.125f, -0.375f, -0.125f,	0.0f, 0.5f,			-1.0f, 0.0f, 0.0f, //4

			-0.125f, 0.375f, 0.125f,	0.0625f, 0.6875f,	-1.0f, 0.0f, 0.0f, //2
			-0.125f, -0.375f, -0.125f,	0.0f, 0.5f,			-1.0f, 0.0f, 0.0f, //4
			-0.125f, -0.375f, 0.125f,	0.0625f, 0.5f,		-1.0f, 0.0f, 0.0f, //6

			//atras
			-0.125f, 0.375f, -0.125f,	0.125f, 0.6875f,	0.0f, 0.0f, -1.0f, //0
			0.125f, 0.375f, -0.125f,	0.1875f, 0.6875f,	0.0f, 0.0f, -1.0f, //1
			0.125f, -0.375f, -0.125f,	0.1875f, 0.5f,		0.0f, 0.0f, -1.0f, //5

			-0.125f, 0.375f, -0.125f,	0.125f, 0.6875f,	0.0f, 1.0f, -1.0f, //0
			-0.125f, -0.375f, -0.125f,	0.125f, 0.5f,		-1.0f, 0.0f, -1.0f, //4
			0.125f, -0.375f, -0.125f,	0.1875f, 0.5f,		0.0f, 0.0f, -1.0f, //5

			//der
			0.125f, 0.375f, -0.125f,	0.1875f, 0.6875f,	0.0f, 0.0f, 1.0f, //1
			0.125f, 0.375f, 0.125f,		0.25f, 0.6875f,		0.0f, 0.0f, 1.0f, //3
			0.125f, -0.375f, -0.125f,	0.1875f, 0.5f,		0.0f, 0.0f, 1.0f, //5

			0.125f, 0.375f, 0.125f,		0.25f, 0.6875f,		0.0f, 0.0f, 1.0f, //3
			0.125f, -0.375f, -0.125f,	0.1875f, 0.5f,		0.0f, 0.0f, 1.0f, //5
			0.125f, -0.375f, 0.125f,	0.25f, 0.5f,		0.0f, 0.0f, 1.0f, //7

			//abajo
			-0.125f, -0.375f, -0.125f,	0.125f, 0.75f,		0.0f, 0.0f, 1.0f, //4
			0.125f, -0.375f, -0.125f,	0.1875f, 0.75f,		0.0f, 0.0f, 1.0f, //5
			-0.125f, -0.375f, 0.125f,	0.125f, 0.6875f,	0.0f, 0.0f, 1.0f, //6

			0.125f, -0.375f, -0.125f,	0.1875f, 0.75f,		0.0f, 0.0f, 0.0f, //5
			-0.125f, -0.375f, 0.125f,	0.125f, 0.6875f,	0.0f, 0.0f, 0.0f, //6
			0.125f, -0.375f, 0.125f,	0.1875f, 0.6875f,	0.0f, 0.0f, 0.0f, //7

			//frente
			-0.125f, 0.375f, 0.125f,	0.0625f, 0.6875f,	0.0f, 0.0f, 1.0f, //2
			0.125f, 0.375f, 0.125f,		0.125f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			-0.125f, -0.375f, 0.125f,	0.0625f, 0.5f,		0.0f, 0.0f, 1.0f, //6

			0.125f, 0.375f, 0.125f,		0.125f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			-0.125f, -0.375f, 0.125f,	0.0625f, 0.5f,		0.0f, 0.0f, 1.0f, //6
			0.125f, -0.375f, 0.125f,	0.125f, 0.5f,		0.0f, 0.0f, 1.0f, //7
	};

	GLfloat verticesTorso2[] = {
		//	x      y      z				u	  v				nx	  ny    nz
			//arriba
			-0.25f, 0.375f, -0.125f,	0.4375f, 0.75f,		0.0f, 1.0f, 0.0f, //0
			0.25f, 0.375f, -0.125f,		0.5625f, 0.75f,		0.0f, 1.0f, 0.0f, //1
			-0.25f, 0.375f, 0.125f,		0.4375f, 0.6875f,	0.0f, 1.0f, 0.0f, //2

			0.25f, 0.375f, -0.125f,		0.5625f, 0.75f,		0.0f, 1.0f, 0.0f, //1
			-0.25f, 0.375f, 0.125f,		0.4375f, 0.6875f,	0.0f, 1.0f, 0.0f, //2
			0.25f, 0.375f, 0.125f,		0.5625f, 0.6875f,	0.0f, 1.0f, 0.0f, //3

			//izq
			-0.25f, 0.375f, -0.125f,	0.25f, 0.6875f,		-1.0f, 0.0f, 0.0f, //0
			-0.25f, 0.375f, 0.125f,		0.3125f, 0.6875f,	-1.0f, 0.0f, 0.0f, //2
			-0.25f, -0.375f, -0.125f,	0.25f, 0.5f,		-1.0f, 0.0f, 0.0f, //4

			-0.25f, 0.375f, 0.125f,		0.3125f, 0.6875f,	-1.0f, 0.0f, 0.0f, //2
			-0.25f, -0.375f, -0.125f,	0.25f, 0.5f,		-1.0f, 0.0f, 0.0f, //4
			-0.25f, -0.375f, 0.125f,	0.3125f, 0.5f,		-1.0f, 0.0f, 0.0f, //6

			//atras
			-0.25f, 0.375f, -0.125f,	0.4375f, 0.6875f,	0.0f, 0.0f, -1.0f, //0
			0.25f, 0.375f, -0.125f,		0.5625f, 0.6875f,	0.0f, 0.0f, -1.0f, //1
			0.25f, -0.375f, -0.125f,	0.5625f, 0.5f,		0.0f, 0.0f, -1.0f, //5

			-0.25f, 0.375f, -0.125f,	0.4375f, 0.6875f,	0.0f, 1.0f, -1.0f, //0
			-0.25f, -0.375f, -0.125f,	0.4375f, 0.5f,		-1.0f, 0.0f, -1.0f, //4
			0.25f, -0.375f, -0.125f,	0.5625f, 0.5f,		0.0f, 0.0f, -1.0f, //5

			//der
			0.25f, 0.375f, -0.125f,		0.5625f, 0.6875f,	0.0f, 0.0f, 1.0f, //1
			0.25f, 0.375f, 0.125f,		0.625f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			0.25f, -0.375f, -0.125f,	0.5625f, 0.5f,		0.0f, 0.0f, 1.0f, //5

			0.25f, 0.375f, 0.125f,		0.625f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			0.25f, -0.375f, -0.125f,	0.5625f, 0.5f,		0.0f, 0.0f, 1.0f, //5
			0.25f, -0.375f, 0.125f,		0.625f, 0.5f,		0.0f, 0.0f, 1.0f, //7

			//abajo
			-0.25f, -0.375f, -0.125f,	0.4375f, 0.75f,		0.0f, 0.0f, 1.0f, //4
			0.25f, -0.375f, -0.125f,	0.5625f, 0.75f,		0.0f, 0.0f, 1.0f, //5
			-0.25f, -0.375f, 0.125f,	0.4375f, 0.6875f,	0.0f, 0.0f, 1.0f, //6

			0.25f, -0.375f, -0.125f,	0.5625f, 0.75f,		0.0f, 0.0f, 0.0f, //5
			-0.25f, -0.375f, 0.125f,	0.4375f, 0.6875f,	0.0f, 0.0f, 0.0f, //6
			0.25f, -0.375f, 0.125f,		0.5625f, 0.6875f,	0.0f, 0.0f, 0.0f, //7

			//frente
			-0.25f, 0.375f, 0.125f,		0.3125f, 0.6875f,	0.0f, 0.0f, 1.0f, //2
			0.25f, 0.375f, 0.125f,		0.4375f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			-0.25f, -0.375f, 0.125f,	0.3125f, 0.5f,		0.0f, 0.0f, 1.0f, //6

			0.25f, 0.375f, 0.125f,		0.4375f, 0.6875f,	0.0f, 0.0f, 1.0f, //3
			-0.25f, -0.375f, 0.125f,	0.3125f, 0.5f,		0.0f, 0.0f, 1.0f, //6
			0.25f, -0.375f, 0.125f,		0.4375f, 0.5f,		0.0f, 0.0f, 1.0f, //7
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(verticesCabeza, indices, 288, 36);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(verticesTorso, indices, 288, 36);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(verticesBrazo, indices, 288, 36);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(verticesPierna, indices, 288, 36);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(verticesTorso2, indices, 288, 36);
	meshList.push_back(obj5);


	/*
	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(verticesBrazoDer, indices, 288, 36);
	meshList.push_back(obj4);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(verticesPiernaDer, indices, 288, 36);
	meshList.push_back(obj6);
	*/
}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}




///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;

//NEW// Keyframes

float posXavion = -120.0f, posYavion = 30.0f, posZavion = -130.0f;
float	movAvion_x = 0.0f, movAvion_y = 0.0f, movAvion_z = 0.0f;
float giroAvionY = 0;
float giroAvionX = 0;

#define MAX_FRAMES 41
int i_max_steps = 50;
int i_curr_steps = 36; //frames ya iniciados 
typedef struct _Kframe
{
	//Variables para GUARDAR Key Frames
	float movAvion_x;		//Variable para PosicionX
	float movAvion_y;		//Variable para PosicionY
	float movAvion_z;		//Variable para PosicionZ
	
	float movAvion_xInc;		//Variable para IncrementoX
	float movAvion_yInc;		//Variable para IncrementoY
	float movAvion_zInc;		//Variable para IncrementoZ

	float giroAvionY;
	float giroAvionYInc;
	float giroAvionX;
	float giroAvionXInc;
}KFRAME;

KFRAME KeyFrame[MAX_FRAMES];

int FrameIndex = 36;			//introducir datos
bool play = false;  //var animacion para iniciar por teclado
int playIndex = 0;

void saveFrame(void)
{

	printf("Se guard� el frame[ %d ]\n", FrameIndex);


	KeyFrame[FrameIndex].movAvion_x = movAvion_x;
	KeyFrame[FrameIndex].movAvion_y = movAvion_y;
	KeyFrame[FrameIndex].movAvion_z = movAvion_z;
	KeyFrame[FrameIndex].giroAvionY = giroAvionY;
	KeyFrame[FrameIndex].giroAvionX = giroAvionX;
	FrameIndex++;
}

void resetElements(void)
{

	movAvion_x = KeyFrame[0].movAvion_x;
	movAvion_y = KeyFrame[0].movAvion_y;
	movAvion_z = KeyFrame[0].movAvion_z;
	giroAvionY = KeyFrame[0].giroAvionY;
	giroAvionX = KeyFrame[0].giroAvionX;
}

void interpolation(void)
{
	KeyFrame[playIndex].movAvion_xInc = (KeyFrame[playIndex + 1].movAvion_x - KeyFrame[playIndex].movAvion_x) / i_max_steps;
	KeyFrame[playIndex].movAvion_yInc = (KeyFrame[playIndex + 1].movAvion_y - KeyFrame[playIndex].movAvion_y) / i_max_steps;
	KeyFrame[playIndex].movAvion_zInc = (KeyFrame[playIndex + 1].movAvion_z - KeyFrame[playIndex].movAvion_z) / i_max_steps;
	KeyFrame[playIndex].giroAvionYInc = (KeyFrame[playIndex + 1].giroAvionY - KeyFrame[playIndex].giroAvionY) / i_max_steps;
	KeyFrame[playIndex].giroAvionXInc = (KeyFrame[playIndex + 1].giroAvionX - KeyFrame[playIndex].giroAvionX) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			//printf("frame reproducido playindex : %d\n", playIndex - 1);
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				//printf("ultimo Frame index= %d\n", FrameIndex - 1);
				//printf("termina animacion\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aqu�\n");
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se qued� aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation
			movAvion_x += KeyFrame[playIndex].movAvion_xInc;
			movAvion_y += KeyFrame[playIndex].movAvion_yInc;
			movAvion_z += KeyFrame[playIndex].movAvion_zInc;
			giroAvionY += KeyFrame[playIndex].giroAvionYInc;
			giroAvionX += KeyFrame[playIndex].giroAvionXInc;
			i_curr_steps++;
		}

	}
}

/* FIN KEYFRAMES*/


Toroide toroParada = Toroide(4.0f, 6.0f);


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();


	CreatePersonaje(); //0,1,2,3,4
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader
	CreateStar(); // 5
	toroParada.CrearToroide(&meshList);//6
	CreateShaders();
	

	cameraLibre = Camera(glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.0f, 0.5f);
	cameraWheezy = Camera(glm::vec3(0.0f, 24.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.0f, 0.5f);
	cameraJett = Camera(glm::vec3(-240.0f, 92.0f, -340.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 1.0f, 0.5f);
	cameraFrijolito = Camera(glm::vec3(180.0f, 50.1f, -50.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, 0.0f, 1.0f, 0.5f);

	//========================================PRUEBA TOROIDES===================================
	
	
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();



	WheezyTexture = Texture("Textures/wheezy_textura.tga");
	WheezyTexture.LoadTextureA();
	FrijolitoTexture = Texture("Textures/frijolito_texture.png");
	FrijolitoTexture.LoadTextureA();
	JettTexture = Texture("Textures/jett_texture.jpg");
	JettTexture.LoadTextureA();

	StreetMan1_Texture = Texture("Textures/SimplePeople_StreetMan_Black.png");
	StreetMan1_Texture.LoadTexture();
	StreetMan2_Texture = Texture("Textures/SimplePeople_StreetMan_Brown.png");
	StreetMan2_Texture.LoadTexture();
	StreetMan3_Texture = Texture("Textures/SimplePeople_StreetMan_White.png");
	StreetMan3_Texture.LoadTexture();
	Ricochet_Texture = Texture("Textures/ricochet_hd.png");
	Ricochet_Texture.LoadTextureA();
	La_Pulga_Texture = Texture("Textures/la_pulga_hd.png");
	La_Pulga_Texture.LoadTextureA();
	Buena_Girl_Texture = Texture("Textures/buena_girl_hd.png");
	Buena_Girl_Texture.LoadTextureA();

	//Modelos para el proyecto
	Cuarto_M.LoadModel("Models/cuarto.obj");
	Escritorio_M.LoadModel("Models/SM_Prop_Desk_02_OBJ.obj");
	Escritorio2_M.LoadModel("Models/desk_2.obj");
	Escritorio3_M.LoadModel("Models/desk_3.obj");
	Lampara_M.LoadModel("Models/SM_Prop_DeskLamp_05_OBJ.obj");
	Bote_basura_M.LoadModel("Models/SM_Prop_Bin_03_OBJ.obj");
	Silla_M.LoadModel("Models/silla_desk.obj");
	Puff_M.LoadModel("Models/SM_Prop_Chair_BeanBag_03_OBJ.obj");
	SetUp_M.LoadModel("Models/SM_Prop_Computer_Setup_02_OBJ.obj");
	HeadSet_M.LoadModel("Models/SM_Prop_Headset_02_OBJ.obj");
	LuzTecho_M.LoadModel("Models/SM_Prop_Light_07_OBJ.obj");
	JettCompleta.LoadModel("Models/JettCompleta.obj");
	Cama_M.LoadModel("Models/bed_red.obj");
	Alfombra_M.LoadModel("Models/alfombra.obj");
	Mueble_M.LoadModel("Models/mueble.obj");
	Rampa_M.LoadModel("Models/rampa.obj");
	Leds_M.LoadModel("Models/led_line.obj");
	Leds_mini_M.LoadModel("Models/led_mini_line.obj");
	Helicoptero_M.LoadModel("Models/helicoptero.obj");
	Helice_M.LoadModel("Models/helice.obj");

	//modelos p12 Pieter
	White_Helicopter_M.LoadModel("Models/white_helicopter.obj");
	White_Helicopter_Helice_M.LoadModel("Models/helice_white_helicopter.obj");
	White_Helicopter_Rotor_M.LoadModel("Models/rotor_white_helicopter.obj");
	Helipad_M.LoadModel("Models/helipad.obj");
	
	//MODELOS KEYFRAMES Jesus Bryan
	Helipuerto_M.LoadModel("Models/helipad.obj");
	Helice_Bryan.LoadModel("Models/Helice_Bryan.obj");
	Rotor_Bryan.LoadModel("Models/Rotor_Bryan.obj");
	Helicoptero_Bryan.LoadModel("Models/Helicoptero_Bryan.obj");
	
	//TOY STORY
	Casita_M.LoadModel("Models/casita.obj");
	Arbolito_M.LoadModel("Models/arbolito.obj");
	Edificio_M.LoadModel("Models/edificio.obj");
	Edificio2_M.LoadModel("Models/edificio_azul.obj");
	Car_M.LoadModel("Models/car_01.obj");
	Bus_M.LoadModel("Models/bus.obj");
	CuboR_M.LoadModel("Models/cubo_rubik.obj");

	//Wheezy
	Wheezy_torso_M.LoadModel("Models/wheezy_torso.obj");
	Wheezy_cabeza_M.LoadModel("Models/wheezy_cabeza.obj");
	Wheezy_brazo_izq_M.LoadModel("Models/wheezy_brazo_izq.obj");
	Wheezy_brazo_der_M.LoadModel("Models/wheezy_brazo_der.obj");
	Wheezy_pie_izq_M.LoadModel("Models/wheezy_pie_izq.obj");
	Wheezy_pie_der_M.LoadModel("Models/wheezy_pie_der.obj");

	//V A L O R A N T__________________________________________________________________________
	Valorant_Gosth_M.LoadModel("Models/Valorant_Gosth.obj");
	Valorant_Spectre_M.LoadModel("Models/Valorant_Spectre.obj");
	Valorant_Banca_Madera.LoadModel("Models/Valorant_BancaMadera.obj");
	Valorant_Balde_M.LoadModel("Models/Valorant_Balde.obj");
	Valorant_Malla_M.LoadModel("Models/Valorant_Malla.obj");
	Valorant_CajaMadera_M.LoadModel("Models/Valorant_CajaMadera.obj");
	Valorant_CajaMadera2_M.LoadModel("Models/Valorant_CajaMadera2.obj");
	Valorant_FenixC.LoadModel("Models/FenixCaraTorso.obj");
	Valorant_FenixBD.LoadModel("Models/FenixBrazoDer.obj");
	Valorant_FenixBI.LoadModel("Models/FenixBrazoIzq.obj");
	Valorant_FenixPD.LoadModel("Models/FenixPieDer.obj");
	Valorant_FenixPI.LoadModel("Models/FenixPieIzq.obj");
	LamparaVal_M.LoadModel("Models/LamparaValorant.obj");
	Valorant_KillJC.LoadModel("Models/KillJoyCaraTorso.obj");
	Valorant_KillJBD.LoadModel("Models/KillJoyBrazoDer.obj");
	Valorant_KillJBI.LoadModel("Models/KillJoyBrazoIzq.obj");
	Valorant_KillJPD.LoadModel("Models/KillJoyPieDer.obj");
	Valorant_KillJPI.LoadModel("Models/KillJoyPieIzq.obj");
	//Valorant
	Spike_base_M.LoadModel("Models/spike_base_only.obj");
	Spike_cilindro_M.LoadModel("Models/spike_center_only.obj");
	Spike_aro_M.LoadModel("Models/spike_moveable_only.obj");

	ML_Ring_M.LoadModel("Models/ring_texturizado.obj");
	Luchador_M.LoadModel("Models/Characters/SK_Character_Streetman.fbx");

	//Modelos_MuchaLucha* frijolito = new Modelos_MuchaLucha();

	// TODO: agreagar doble textura para que haya uno de día y uno de noche

	std::vector<std::string> skyboxFaces;

	skyboxFaces.push_back("Textures/Skybox_City/city_right_f.tga");
	skyboxFaces.push_back("Textures/Skybox_City/city_left_f.tga");
	skyboxFaces.push_back("Textures/Skybox_City/city_down_f.tga");
	skyboxFaces.push_back("Textures/Skybox_City/city_up_f.tga");
	skyboxFaces.push_back("Textures/Skybox_City/city_back_f.tga");
	skyboxFaces.push_back("Textures/Skybox_City/city_front_f.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, //color
		0.1f, 0.3f, // 0.5, 0.3 mas iluminado (AMBIENTAL, DIFUSA)
		0.0f, 0.0f, -1.0f); //(DESDE DONDE ILUMINA)
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaraci�n de primer luz puntual

	//LUZ DE LAMPARA DE TECHO 1
	pointLightsNoche[0] = PointLight(1.0f, 1.0f, 1.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		0.0f, 195.0f, 4.5f, // posicion
		0.1f, 0.01f, 0.0f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount++;

	//LUZ DE LAMPARA DE TECHO 2
	pointLightsNoche[1] = PointLight(1.0f, 1.0f, 1.0f, //color 
		0.9f, 0.1f, //ambiente, difusa
		0.0f, 195.0f, -297.0f, // posicion
		0.1f, 0.01f, 0.0f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount++;

	//LUZ DE LA LAMPARA DE ESCRITORIO ARREGLO DE SPOTLIGHTS 0
	unsigned int spotLightCount = 0;
	spotLights[spotLightCount] = SpotLight(1.0f, 0.5f, 0.0f, //COLOR
		0.0f, 2.0f, //AMBIENTE, DIFUSA
		50.0f, 125.0f, -360.0f, //POSICION
		0.0f, -1.0f, 1.0f, //DIRECCION
		1.0f, 0.01f, 0.0004f, //C,B,A: ECUACION DE SEGUNDO GRADO
		15.0f); //ANGULO DE APERTURA
	spotLightCount++;

	//LUZ DE LA LAMPARA DE VALORANT
	unsigned int spotLightCount1 = 0;
	spotlights1[spotLightCount1] = SpotLight(1.0f, 0.0f, 1.0f, //COLOR
		0.0f, 2.0f, //AMBIENTE, DIFUSA
		-121.0f, 100.0f, -305.0f, //POSICION
		0.0f, -1.0f, 0.0f, //DIRECCION
		1.0f, 0.01f, 0.0004f, //C,B,A: ECUACION DE SEGUNDO GRADO
		5.0f); //ANGULO DE APERTURA
	spotLightCount1++;

	//LUZ DE LA LAMPARA DE ESCRITORIO ARREGLO DE SPOTLIGHTS 0
	spotlights1[spotLightCount1] = SpotLight(1.0f, 0.5f, 0.0f, //COLOR
		0.0f, 2.0f, //AMBIENTE, DIFUSA
		50.0f, 125.0f, -360.0f, //POSICION
		0.0f, -1.0f, 1.0f, //DIRECCION
		1.0f, 0.01f, 0.0004f, //C,B,A: ECUACION DE SEGUNDO GRADO
		15.0f); //ANGULO DE APERTURA
	spotLightCount1++;

	unsigned int pointLightCount1 = 0;
	//LUZ DE LEDS DE LA CAMA
	pointLightsCama[0] = PointLight(1.0f, 0.0f, 0.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		-150.0f, 20.0f, 40.0f, // posicion
		0.5f, 0.01f, 0.001f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount1++;

	//LUZ DE LEDS DEL ESCRITORIO
	pointLightsCama[1] = PointLight(1.0f, 0.0f, 0.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		0.0f, 60.0f, -375.0f, // posicion
		0.5f, 0.01f, 0.001f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount1++;

	//LUZ DE LAMPARA DE TECHO 1
	pointLightsCama[2] = PointLight(1.0f, 1.0f, 1.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		0.0f, 195.0f, 4.5f, // posicion
		0.1f, 0.01f, 0.0f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount1++;

	//LUZ DE LAMPARA DE TECHO 2
	pointLightsCama[3] = PointLight(1.0f, 1.0f, 1.0f, //color 
		0.9f, 0.1f, //ambiente, difusa
		0.0f, 195.0f, -297.0f, // posicion
		0.1f, 0.01f, 0.0f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount1++;

	//ARREGLO DE PINTLIGHTS DE LA SPIKE ===================================================
	unsigned int pointLightCount2 = 0;
	//LUZ DE LEDS DE LA CAMA
	pointLightsSpike[0] = PointLight(1.0f, 0.0f, 0.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		-150.0f, 20.0f, 40.0f, // posicion
		0.5f, 0.01f, 0.001f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount2++;

	//LUZ DE LEDS DEL ESCRITORIO
	pointLightsSpike[1] = PointLight(1.0f, 0.0f, 0.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		0.0f, 60.0f, -375.0f, // posicion
		0.5f, 0.01f, 0.001f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount2++;

	//LUZ DE LA SPIKE
	pointLightsSpike[2] = PointLight(0.0f, 0.5f, 1.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		-80.0f, 69.0f, -330.0f, // posicion
		0.5f, 0.01f, 0.001f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount2++;

	//LUZ DE LAMPARA DE TECHO 1
	pointLightsSpike[3] = PointLight(1.0f, 1.0f, 1.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		0.0f, 195.0f, 4.5f, // posicion
		0.1f, 0.01f, 0.0f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount2++;

	//LUZ DE LAMPARA DE TECHO 2
	pointLightsSpike[4] = PointLight(1.0f, 1.0f, 1.0f, //color 
		0.9f, 0.1f, //ambiente, difusa
		0.0f, 195.0f, -297.0f, // posicion
		0.1f, 0.01f, 0.0f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount2++;

	//ARREGLO DE PINTLIGHTS DE LA SPIKE 1 ===================================================
	unsigned int pointLightCount3 = 0;

	//LUZ DE LA SPIKE
	pointLightsSpike1[0] = PointLight(0.0f, 0.5f, 1.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		-80.0f, 69.0f, -330.0f, // posicion
		0.5f, 0.01f, 0.001f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount3++;

	//LUZ DE LAMPARA DE TECHO 1
	pointLightsSpike1[1] = PointLight(1.0f, 1.0f, 1.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		0.0f, 195.0f, 4.5f, // posicion
		0.1f, 0.01f, 0.0f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount3++;

	//LUZ DE LAMPARA DE TECHO 2
	pointLightsSpike1[2] = PointLight(1.0f, 1.0f, 1.0f, //color 
		0.9f, 0.1f, //ambiente, difusa
		0.0f, 195.0f, -297.0f, // posicion
		0.1f, 0.01f, 0.0f); // ecuaci�n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount3++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	float var1 = 0.0f;
	float ledOffset = 20.0f;
	contadorDiaNoche = 0.0f;
	posicionLedX = -150.0f;
	posicionLedZ = 40.0f;
	banderaLedCama = 2;
	bool isWheezyCam = false;
	float movSpike = 0.0f;
	glm::vec3 posSpike = glm::vec3(-80.0f, 69.0f, -330.0f); //-80, 69, -330
	posicionLed1X = 0.0f;
	posicionLed1Z = -380.0f;
	banderaLedEscritorio = 0;
	banderaParpadeoSpike = 0;
	float avanzaOffset = 15.0f;

	int numCam = 0;

	//Vars animacion juguetes
	std::string estado_bus = "PARAR_BUS";
	glm::vec3 posBus1 = glm::vec3(-140.0f, 7.0f, -90.0f);
	float angulo_busZ = -90;
	float angulo_busZ_offset = 1.5f;
	float angulo_busY = 30;
	float angulo_busY_offset = 1.0f;
	float angulo_busX = 0;
	float angulo_busX_offset = 1.0f;
	float posBus1X = 0.0f;
	float posBus1Y = 0.0f;
	float posBus1Z = 0.0f;
	bool anguloBusListo;
	bool posBusListo;
	float auxposx = 0.0f;
	float auxposz = 0.0f;

	std::string estado_car = "VUELTA_CAR";
	glm::vec3 posCar = glm::vec3(-70.0f, 3.0f, -120.0f);
	float angulo_carY = 0.0f;
	float angulo_carY_offset = 0.8f;
	float angulo_carX = 0.0f;
	float angulo_carX_offset = 0.8f;
	float posCar1X = 0.0f;
	float posCar1Y = 0.0f;
	float posCar1Z = 0.0f;
	float auxPosCarx = 0.0f;
	float auxPosCarz = 0.0f;

	std::string estado_car2 = "INICIO_CAR2";
	glm::vec3 posCar2 = glm::vec3(0.0f, 3.0f, -80.0f);
	float angulo_car2Y = -45.0f;
	float angulo_car2Y_offset = 0.8f;
	float angulo_car2X = 0.0f;
	float angulo_car2X_offset = 0.8f;
	float posCar2X = 0.0f;
	float posCar2Y = 3.0f;
	float posCar2Z = -80.0f;
	float auxPosCar2x = 0.0f;
	float auxPosCar2z = 0.0f;

	std::string estado_edificio = "PARAR_EDIFICIO";
	glm::vec3 posEdificio = glm::vec3(-10.0f, 10.0f, -150.0f);
	float angulo_EdiY = 0.0f;
	float angulo_EdiY_offset = 1.0f;
	float angulo_EdiX = 90.0f;
	float angulo_EdiX_offset = 0.6f;
	float posEdi1X = 0.0f;
	float posEdi1Y = 0.0f;
	float posEdi1Z = 0.0f;
	float auxPosEdix = 0.0f;
	float auxPosEdiz = 0.0f;
	float auxAngEdiy = 0.0f;


	glm::vec3 posPelota = glm::vec3(30.0f, 12.0f, -120.0f);
	float posPelotaX = 30.0f;
	float posPelotaY = 12.0f;
	float posPelotaZ = -120.0f;
	float rotPelotaX = 0.0f;
	float rotPelotaY = 0.0f;

	float rotLuchador1 = 0.0f;
	float rotRikochet = 0.0f;
	float rotLa_Pulga = 0.0f, rotY_La_Pulga = 0.0f;
	float rotBuena_Girl = 0.0f;
	float movX_Rik = 5.0f, movY_Rik = 4.0f, movZ_Rik = -5.0f;
	float movX_LP = 5.0f, movY_LP = 4.0f, movZ_LP = 5.0;
	float movX_BG = -5.0f, movY_BG = 4.0f, movZ_BG = -5.0f;
	float rotPiernasR = 0.0f, rotPiernasLP = 0.0f, rotPiernasBG = 0.0f;
	int estado_ML = 0;


	//KEYFRAMES DECLARADOS INICIALES

	KeyFrame[0].movAvion_x = 0.0f;
	KeyFrame[0].movAvion_y = 0.0f;
	KeyFrame[0].movAvion_z = 0.0f;
	KeyFrame[0].giroAvionY = 0;
	KeyFrame[0].giroAvionX = 0;


	KeyFrame[1].movAvion_x =-3.0f;
	KeyFrame[1].movAvion_y = 3.0f;
	KeyFrame[1].movAvion_z = 0.0f;
	KeyFrame[1].giroAvionY = 0;
	KeyFrame[1].giroAvionX = 0;

	KeyFrame[2].movAvion_x = -7.0f;
	KeyFrame[2].movAvion_y = 7.0f;
	KeyFrame[2].movAvion_z = 0.0f;
	KeyFrame[2].giroAvionY = 0;
	KeyFrame[2].giroAvionX = 0;


	KeyFrame[3].movAvion_x = -12.0f;
	KeyFrame[3].movAvion_y = 11.0f;
	KeyFrame[3].movAvion_z = 0.0f;
	KeyFrame[3].giroAvionY = 10.0f;
	KeyFrame[3].giroAvionX = 0;

	KeyFrame[4].movAvion_x = -21.0f;
	KeyFrame[4].movAvion_y = 15.0f;
	KeyFrame[4].movAvion_z = 4.0f;
	KeyFrame[4].giroAvionY = 31.0f;
	KeyFrame[4].giroAvionX = 0.0f;

	KeyFrame[5].movAvion_x = -26.0f;
	KeyFrame[5].movAvion_y = 15.0f;
	KeyFrame[5].movAvion_z = 13.0f;
	KeyFrame[5].giroAvionY = 64.0f;
	KeyFrame[5].giroAvionX = 10.0f;

	KeyFrame[6].movAvion_x = -32.0f;
	KeyFrame[6].movAvion_y = 14.0f;
	KeyFrame[6].movAvion_z = 27.0f;
	KeyFrame[6].giroAvionY = 91.0f;
	KeyFrame[6].giroAvionX = 10.0f;

	KeyFrame[7].movAvion_x = -23.0f;
	KeyFrame[7].movAvion_y = 14.0f;
	KeyFrame[7].movAvion_z = 54.0f;
	KeyFrame[7].giroAvionY = 130.0f;
	KeyFrame[7].giroAvionX = -12.0f;

	KeyFrame[8].movAvion_x = -6.0f;
	KeyFrame[8].movAvion_y = 14.0f;
	KeyFrame[8].movAvion_z = 81.0f;
	KeyFrame[8].giroAvionY = 170.0f;
	KeyFrame[8].giroAvionX = -12.0f;

	KeyFrame[9].movAvion_x = 38.0f;
	KeyFrame[9].movAvion_y = 14.0f;
	KeyFrame[9].movAvion_z = 81.0f;
	KeyFrame[9].giroAvionY = 181.0f;
	KeyFrame[9].giroAvionX = 0.0f;

	KeyFrame[10].movAvion_x = 69.0f;
	KeyFrame[10].movAvion_y = 14.0f;
	KeyFrame[10].movAvion_z = 81.0f;
	KeyFrame[10].giroAvionY = 181.0f;
	KeyFrame[10].giroAvionX = 0.0f;

	KeyFrame[11].movAvion_x = 88.0f;
	KeyFrame[11].movAvion_y = 23.0f;
	KeyFrame[11].movAvion_z = 81.0f;
	KeyFrame[11].giroAvionY = 190.0f;
	KeyFrame[11].giroAvionX = 0.0f;

	KeyFrame[12].movAvion_x = 115.0f;
	KeyFrame[12].movAvion_y = 25.0f;
	KeyFrame[12].movAvion_z = 70.0f;
	KeyFrame[12].giroAvionY = 215.0f;
	KeyFrame[12].giroAvionX = 0.0f;

	KeyFrame[13].movAvion_x = 129.0f;
	KeyFrame[13].movAvion_y = 25.0f;
	KeyFrame[13].movAvion_z = 60.0f;
	KeyFrame[13].giroAvionY = 251.0f;
	KeyFrame[13].giroAvionX = 0.0f;

	KeyFrame[14].movAvion_x = 141.0f;
	KeyFrame[14].movAvion_y = 25.0f;
	KeyFrame[14].movAvion_z = 46.0f;
	KeyFrame[14].giroAvionY = 273.0f;
	KeyFrame[14].giroAvionX = 0.0f;

	KeyFrame[15].movAvion_x = 155.0f;
	KeyFrame[15].movAvion_y = 25.0f;
	KeyFrame[15].movAvion_z = -7.0f;
	KeyFrame[15].giroAvionY = 273.0f;
	KeyFrame[15].giroAvionX = 0.0f;

	KeyFrame[16].movAvion_x = 155.0f;
	KeyFrame[16].movAvion_y = 31.0f;
	KeyFrame[16].movAvion_z = -20.0f;
	KeyFrame[16].giroAvionY = 273.0f;
	KeyFrame[16].giroAvionX = 9.0f;

	KeyFrame[17].movAvion_x = 155.0f;
	KeyFrame[17].movAvion_y = 37.0f;
	KeyFrame[17].movAvion_z = -30.0f;
	KeyFrame[17].giroAvionY = 273.0f;
	KeyFrame[17].giroAvionX = 19.0f;

	KeyFrame[18].movAvion_x = 155.0f;
	KeyFrame[18].movAvion_y = 46.0f;
	KeyFrame[18].movAvion_z = -49.0f;
	KeyFrame[18].giroAvionY = 273.0f;
	KeyFrame[18].giroAvionX = 19.0f;

	KeyFrame[19].movAvion_x = 155.0f;
	KeyFrame[19].movAvion_y = 50.0f;
	KeyFrame[19].movAvion_z = -67.0f;
	KeyFrame[19].giroAvionY = 273.0f;
	KeyFrame[19].giroAvionX = 9.0f;

	KeyFrame[20].movAvion_x = 155.0f;
	KeyFrame[20].movAvion_y = 50.0f;
	KeyFrame[20].movAvion_z = -90.0f;
	KeyFrame[20].giroAvionY = 273.0f;
	KeyFrame[20].giroAvionX = 0.0f;

	KeyFrame[21].movAvion_x = 155.0f;
	KeyFrame[21].movAvion_y = 50.0f;
	KeyFrame[21].movAvion_z = -120.0f;
	KeyFrame[21].giroAvionY = 273.0f;
	KeyFrame[21].giroAvionX = 0.0f;

	KeyFrame[22].movAvion_x = 150.0f;
	KeyFrame[22].movAvion_y = 50.0f;
	KeyFrame[22].movAvion_z = -135.0f;
	KeyFrame[22].giroAvionY = 301.0f;
	KeyFrame[22].giroAvionX = 0.0f;

	KeyFrame[23].movAvion_x = 140.0f;
	KeyFrame[23].movAvion_y = 50.0f;
	KeyFrame[23].movAvion_z = -147.0f;
	KeyFrame[23].giroAvionY = 356.0f;
	KeyFrame[23].giroAvionX = 0.0f;

	KeyFrame[24].movAvion_x = 122.0f;
	KeyFrame[24].movAvion_y = 50.0f;
	KeyFrame[24].movAvion_z = -147.0f;
	KeyFrame[24].giroAvionY = 362.0f;
	KeyFrame[24].giroAvionX = 0.0f;

	KeyFrame[25].movAvion_x = 104.0f;
	KeyFrame[25].movAvion_y = 50.0f;
	KeyFrame[25].movAvion_z = -147.0f;
	KeyFrame[25].giroAvionY = 362.0f;
	KeyFrame[25].giroAvionX = 0.0f;

	KeyFrame[26].movAvion_x = 91.0f;
	KeyFrame[26].movAvion_y = 50.0f;
	KeyFrame[26].movAvion_z = -147.0f;
	KeyFrame[26].giroAvionY = 371.0f;
	KeyFrame[26].giroAvionX = 10.0f;

	KeyFrame[27].movAvion_x = 81.0f;
	KeyFrame[27].movAvion_y = 45.0f;
	KeyFrame[27].movAvion_z = -135.0f;
	KeyFrame[27].giroAvionY = 397.0f;
	KeyFrame[27].giroAvionX = 24.0f;

	KeyFrame[28].movAvion_x = 75.0f;
	KeyFrame[28].movAvion_y = 35.0f;
	KeyFrame[28].movAvion_z = -117.0f;
	KeyFrame[28].giroAvionY = 425.0f;
	KeyFrame[28].giroAvionX = 28.0f;

	KeyFrame[29].movAvion_x = 75.0f;
	KeyFrame[29].movAvion_y = 20.0f;
	KeyFrame[29].movAvion_z = -84.0f;
	KeyFrame[29].giroAvionY = 427.0f;
	KeyFrame[29].giroAvionX = 17.0f;

	KeyFrame[30].movAvion_x = 75.0f;
	KeyFrame[30].movAvion_y = 12.0f;
	KeyFrame[30].movAvion_z = -57.0f;
	KeyFrame[30].giroAvionY = 436.0f;
	KeyFrame[30].giroAvionX = 12.0f;

	KeyFrame[31].movAvion_x = 70.0f;
	KeyFrame[31].movAvion_y = 3.0f;
	KeyFrame[31].movAvion_z = -13.0f;
	KeyFrame[31].giroAvionY = 426.0f;
	KeyFrame[31].giroAvionX = 0.0f;

	KeyFrame[32].movAvion_x = 58.0f;
	KeyFrame[32].movAvion_y = 3.0f;
	KeyFrame[32].movAvion_z = -4.0f;
	KeyFrame[32].giroAvionY = 380.0f;
	KeyFrame[32].giroAvionX = 0.0f;

	KeyFrame[33].movAvion_x = 42.0f;
	KeyFrame[33].movAvion_y = 3.0f;
	KeyFrame[33].movAvion_z = 0.0f;
	KeyFrame[33].giroAvionY = 360.0f;
	KeyFrame[33].giroAvionX = 0.0f;
	
	KeyFrame[34].movAvion_x = 25.0f;
	KeyFrame[34].movAvion_y = 3.0f;
	KeyFrame[34].movAvion_z = 0.0f;
	KeyFrame[34].giroAvionY = 360.0f;
	KeyFrame[34].giroAvionX = 0.0f;

	KeyFrame[35].movAvion_x = 0.0f;
	KeyFrame[35].movAvion_y = 0.0f;
	KeyFrame[35].movAvion_z = 0.0f;
	KeyFrame[35].giroAvionY = 361.0f;
	KeyFrame[35].giroAvionX = 0.0f;

	KeyFrames keyframe_Bryan = KeyFrames(70, 66, 66, false, 0);
	keyframe_Bryan.arreglo[0].mov_x = 0.0f;
	keyframe_Bryan.arreglo[0].mov_y = 0.0f;
	keyframe_Bryan.arreglo[0].mov_z = 0.0f;
	keyframe_Bryan.arreglo[0].giroX = 0.0f;
	keyframe_Bryan.arreglo[0].giroY = 0.0f;
	keyframe_Bryan.arreglo[0].giroZ = 0.0f;

	keyframe_Bryan.arreglo[1].mov_x = -7.0f;
	keyframe_Bryan.arreglo[1].mov_y = 3.0f;
	keyframe_Bryan.arreglo[1].mov_z = 0.0f;
	keyframe_Bryan.arreglo[1].giroX = 0.0f;
	keyframe_Bryan.arreglo[1].giroY = 0.0f;
	keyframe_Bryan.arreglo[1].giroZ = 0.0f;

	keyframe_Bryan.arreglo[2].mov_x = -14.0f;
	keyframe_Bryan.arreglo[2].mov_y = 6.0f;
	keyframe_Bryan.arreglo[2].mov_z = 0.0f;
	keyframe_Bryan.arreglo[2].giroX = 0.0f;
	keyframe_Bryan.arreglo[2].giroY = 0.0f;
	keyframe_Bryan.arreglo[2].giroZ = 0.0f;

	keyframe_Bryan.arreglo[3].mov_x = -28.0f;
	keyframe_Bryan.arreglo[3].mov_y = 12.0f;
	keyframe_Bryan.arreglo[3].mov_z = 0.0f;
	keyframe_Bryan.arreglo[3].giroX = 0.0f;
	keyframe_Bryan.arreglo[3].giroY = 0.0f;
	keyframe_Bryan.arreglo[3].giroZ = 0.0f;

	keyframe_Bryan.arreglo[4].mov_x = -28.0f;
	keyframe_Bryan.arreglo[4].mov_y = 12.0f;
	keyframe_Bryan.arreglo[4].mov_z = 0.0f;
	keyframe_Bryan.arreglo[4].giroX = 24.0f;
	keyframe_Bryan.arreglo[4].giroY = 50.0f;
	keyframe_Bryan.arreglo[4].giroZ = 0.0f;

	keyframe_Bryan.arreglo[5].mov_x = -28.0f;
	keyframe_Bryan.arreglo[5].mov_y = 12.0f;
	keyframe_Bryan.arreglo[5].mov_z = 10.0f;
	keyframe_Bryan.arreglo[5].giroX = 12.0f;
	keyframe_Bryan.arreglo[5].giroY = 23.0f;
	keyframe_Bryan.arreglo[5].giroZ = 0.0f;

	keyframe_Bryan.arreglo[6].mov_x = -28.0f;
	keyframe_Bryan.arreglo[6].mov_y = 12.0f;
	keyframe_Bryan.arreglo[6].mov_z = 10.0f;
	keyframe_Bryan.arreglo[6].giroX = 22.5f;
	keyframe_Bryan.arreglo[6].giroY = 45.0f;
	keyframe_Bryan.arreglo[6].giroZ = 0.0f;

	keyframe_Bryan.arreglo[7].mov_x = -28.0f;
	keyframe_Bryan.arreglo[7].mov_y = 12.0f;
	keyframe_Bryan.arreglo[7].mov_z = 10.0f;
	keyframe_Bryan.arreglo[7].giroX = 40.0f;
	keyframe_Bryan.arreglo[7].giroY = 55.0f;
	keyframe_Bryan.arreglo[7].giroZ = 0.0f;

	keyframe_Bryan.arreglo[8].mov_x = -28.0f;
	keyframe_Bryan.arreglo[8].mov_y = 12.0f;
	keyframe_Bryan.arreglo[8].mov_z = 12.0f;
	keyframe_Bryan.arreglo[8].giroX = 30.0f;
	keyframe_Bryan.arreglo[8].giroY = 70.0f;
	keyframe_Bryan.arreglo[8].giroZ = 0.0f;

	keyframe_Bryan.arreglo[9].mov_x = -28.0f;
	keyframe_Bryan.arreglo[9].mov_y = 12.0f;
	keyframe_Bryan.arreglo[9].mov_z = 14.0f;
	keyframe_Bryan.arreglo[9].giroX = 20.0f;
	keyframe_Bryan.arreglo[9].giroY = 80.0f;
	keyframe_Bryan.arreglo[9].giroZ = 0.0f;

	keyframe_Bryan.arreglo[10].mov_x = -28.0f;
	keyframe_Bryan.arreglo[10].mov_y = 12.0f;
	keyframe_Bryan.arreglo[10].mov_z = 16.0f;
	keyframe_Bryan.arreglo[10].giroX = 10.0f;
	keyframe_Bryan.arreglo[10].giroY = 90.0f;
	keyframe_Bryan.arreglo[10].giroZ = 0.0f;

	keyframe_Bryan.arreglo[11].mov_x = -28.0f;
	keyframe_Bryan.arreglo[11].mov_y = 12.0f;
	keyframe_Bryan.arreglo[11].mov_z = 18.0f;
	keyframe_Bryan.arreglo[11].giroX = 00.0f;
	keyframe_Bryan.arreglo[11].giroY = 90.0f;
	keyframe_Bryan.arreglo[11].giroZ = 0.0f;

	keyframe_Bryan.arreglo[12].mov_x = -28.0f;
	keyframe_Bryan.arreglo[12].mov_y = 12.0f;
	keyframe_Bryan.arreglo[12].mov_z = 30.0f;
	keyframe_Bryan.arreglo[12].giroX = 00.0f;
	keyframe_Bryan.arreglo[12].giroY = 90.0f;
	keyframe_Bryan.arreglo[12].giroZ = 0.0f;

	keyframe_Bryan.arreglo[13].mov_x = -28.0f;
	keyframe_Bryan.arreglo[13].mov_y = 12.0f;
	keyframe_Bryan.arreglo[13].mov_z = 50.0f;
	keyframe_Bryan.arreglo[13].giroX = 00.0f;
	keyframe_Bryan.arreglo[13].giroY = 90.0f;
	keyframe_Bryan.arreglo[13].giroZ = 0.0f;

	keyframe_Bryan.arreglo[14].mov_x = -28.0f;
	keyframe_Bryan.arreglo[14].mov_y = 12.0f;
	keyframe_Bryan.arreglo[14].mov_z = 80.0f;
	keyframe_Bryan.arreglo[14].giroX = 00.0f;
	keyframe_Bryan.arreglo[14].giroY = 90.0f;
	keyframe_Bryan.arreglo[14].giroZ = 0.0f;

	keyframe_Bryan.arreglo[15].mov_x = -28.0f;
	keyframe_Bryan.arreglo[15].mov_y = 12.0f;
	keyframe_Bryan.arreglo[15].mov_z = 80.0f;
	keyframe_Bryan.arreglo[15].giroX = -10.0f;
	keyframe_Bryan.arreglo[15].giroY = 100.0f;
	keyframe_Bryan.arreglo[15].giroZ = 0.0f;

	keyframe_Bryan.arreglo[16].mov_x = -28.0f;
	keyframe_Bryan.arreglo[16].mov_y = 12.0f;
	keyframe_Bryan.arreglo[16].mov_z = 80.0f;
	keyframe_Bryan.arreglo[16].giroX = -20.0f;
	keyframe_Bryan.arreglo[16].giroY = 110.0f;
	keyframe_Bryan.arreglo[16].giroZ = 0.0f;

	keyframe_Bryan.arreglo[17].mov_x = -28.0f;
	keyframe_Bryan.arreglo[17].mov_y = 12.0f;
	keyframe_Bryan.arreglo[17].mov_z = 80.0f;
	keyframe_Bryan.arreglo[17].giroX = -30.0f;
	keyframe_Bryan.arreglo[17].giroY = 120.0f;
	keyframe_Bryan.arreglo[17].giroZ = 0.0f;

	keyframe_Bryan.arreglo[18].mov_x = -28.0f;
	keyframe_Bryan.arreglo[18].mov_y = 12.0f;
	keyframe_Bryan.arreglo[18].mov_z = 80.0f;
	keyframe_Bryan.arreglo[18].giroX = -40.0f;
	keyframe_Bryan.arreglo[18].giroY = 130.0f;
	keyframe_Bryan.arreglo[18].giroZ = 0.0f;

	keyframe_Bryan.arreglo[19].mov_x = -28.0f;
	keyframe_Bryan.arreglo[19].mov_y = 12.0f;
	keyframe_Bryan.arreglo[19].mov_z = 80.0f;
	keyframe_Bryan.arreglo[19].giroX = -45.0f;
	keyframe_Bryan.arreglo[19].giroY = 140.0f;
	keyframe_Bryan.arreglo[19].giroZ = 0.0f;

	keyframe_Bryan.arreglo[20].mov_x = -20.0f;
	keyframe_Bryan.arreglo[20].mov_y = 12.0f;
	keyframe_Bryan.arreglo[20].mov_z = 80.0f;
	keyframe_Bryan.arreglo[20].giroX = -40.0f;
	keyframe_Bryan.arreglo[20].giroY = 150.0f;
	keyframe_Bryan.arreglo[20].giroZ = 0.0f;

	keyframe_Bryan.arreglo[21].mov_x = -10.0f;
	keyframe_Bryan.arreglo[21].mov_y = 12.0f;
	keyframe_Bryan.arreglo[21].mov_z = 80.0f;
	keyframe_Bryan.arreglo[21].giroX = -30.0f;
	keyframe_Bryan.arreglo[21].giroY = 160.0f;
	keyframe_Bryan.arreglo[21].giroZ = 0.0f;

	keyframe_Bryan.arreglo[22].mov_x = 0.0f;
	keyframe_Bryan.arreglo[22].mov_y = 12.0f;
	keyframe_Bryan.arreglo[22].mov_z = 80.0f;
	keyframe_Bryan.arreglo[22].giroX = -20.0f;
	keyframe_Bryan.arreglo[22].giroY = 170.0f;
	keyframe_Bryan.arreglo[22].giroZ = 0.0f;

	keyframe_Bryan.arreglo[23].mov_x = 10.0f;
	keyframe_Bryan.arreglo[23].mov_y = 12.0f;
	keyframe_Bryan.arreglo[23].mov_z = 80.0f;
	keyframe_Bryan.arreglo[23].giroX = -10.0f;
	keyframe_Bryan.arreglo[23].giroY = 180.0f;
	keyframe_Bryan.arreglo[23].giroZ = 0.0f;

	keyframe_Bryan.arreglo[24].mov_x = 20.0f;
	keyframe_Bryan.arreglo[24].mov_y = 10.0f;
	keyframe_Bryan.arreglo[24].mov_z = 80.0f;
	keyframe_Bryan.arreglo[24].giroX = 0.0f;
	keyframe_Bryan.arreglo[24].giroY = 180.0f;
	keyframe_Bryan.arreglo[24].giroZ = 0.0f;

	keyframe_Bryan.arreglo[25].mov_x = 30.0f;
	keyframe_Bryan.arreglo[25].mov_y = 5.0f;
	keyframe_Bryan.arreglo[25].mov_z = 80.0f;
	keyframe_Bryan.arreglo[25].giroX = 0.0f;
	keyframe_Bryan.arreglo[25].giroY = 180.0f;
	keyframe_Bryan.arreglo[25].giroZ = 0.0f;

	keyframe_Bryan.arreglo[26].mov_x = 40.0f;
	keyframe_Bryan.arreglo[26].mov_y = 0.0f;
	keyframe_Bryan.arreglo[26].mov_z = 80.0f;
	keyframe_Bryan.arreglo[26].giroX = 0.0f;
	keyframe_Bryan.arreglo[26].giroY = 180.0f;
	keyframe_Bryan.arreglo[26].giroZ = 0.0f;

	keyframe_Bryan.arreglo[27].mov_x = 50.0f;
	keyframe_Bryan.arreglo[27].mov_y = -5.0f;
	keyframe_Bryan.arreglo[27].mov_z = 80.0f;
	keyframe_Bryan.arreglo[27].giroX = 0.0f;
	keyframe_Bryan.arreglo[27].giroY = 180.0f;
	keyframe_Bryan.arreglo[27].giroZ = 0.0f;

	keyframe_Bryan.arreglo[28].mov_x = 60.0f;
	keyframe_Bryan.arreglo[28].mov_y = -10.0f;
	keyframe_Bryan.arreglo[28].mov_z = 80.0f;
	keyframe_Bryan.arreglo[28].giroX = 0.0f;
	keyframe_Bryan.arreglo[28].giroY = 180.0f;
	keyframe_Bryan.arreglo[28].giroZ = 0.0f;

	keyframe_Bryan.arreglo[29].mov_x = 70.0f;
	keyframe_Bryan.arreglo[29].mov_y = -5.0f;
	keyframe_Bryan.arreglo[29].mov_z = 80.0f;
	keyframe_Bryan.arreglo[29].giroX = 0.0f;
	keyframe_Bryan.arreglo[29].giroY = 180.0f;
	keyframe_Bryan.arreglo[29].giroZ = 0.0f;

	keyframe_Bryan.arreglo[30].mov_x = 80.0f;
	keyframe_Bryan.arreglo[30].mov_y = 0.0f;
	keyframe_Bryan.arreglo[30].mov_z = 80.0f;
	keyframe_Bryan.arreglo[30].giroX = 0.0f;
	keyframe_Bryan.arreglo[30].giroY = 180.0f;
	keyframe_Bryan.arreglo[30].giroZ = 0.0f;

	keyframe_Bryan.arreglo[31].mov_x = 90.0f;
	keyframe_Bryan.arreglo[31].mov_y = 5.0f;
	keyframe_Bryan.arreglo[31].mov_z = 80.0f;
	keyframe_Bryan.arreglo[31].giroX = 0.0f;
	keyframe_Bryan.arreglo[31].giroY = 180.0f;
	keyframe_Bryan.arreglo[31].giroZ = 0.0f;

	keyframe_Bryan.arreglo[32].mov_x = 100.0f;
	keyframe_Bryan.arreglo[32].mov_y = 10.0f;
	keyframe_Bryan.arreglo[32].mov_z = 80.0f;
	keyframe_Bryan.arreglo[32].giroX = 0.0f;
	keyframe_Bryan.arreglo[32].giroY = 180.0f;
	keyframe_Bryan.arreglo[32].giroZ = 0.0f;

	keyframe_Bryan.arreglo[33].mov_x = 100.0f;
	keyframe_Bryan.arreglo[33].mov_y = 10.0f;
	keyframe_Bryan.arreglo[33].mov_z = 80.0f;
	keyframe_Bryan.arreglo[33].giroX = -10.0f;
	keyframe_Bryan.arreglo[33].giroY = 190.0f;
	keyframe_Bryan.arreglo[33].giroZ = 0.0f;

	keyframe_Bryan.arreglo[34].mov_x = 100.0f;
	keyframe_Bryan.arreglo[34].mov_y = 10.0f;
	keyframe_Bryan.arreglo[34].mov_z = 80.0f;
	keyframe_Bryan.arreglo[34].giroX = -20.0f;
	keyframe_Bryan.arreglo[34].giroY = 200.0f;
	keyframe_Bryan.arreglo[34].giroZ = 0.0f;

	keyframe_Bryan.arreglo[35].mov_x = 100.0f;
	keyframe_Bryan.arreglo[35].mov_y = 10.0f;
	keyframe_Bryan.arreglo[35].mov_z = 80.0f;
	keyframe_Bryan.arreglo[35].giroX = -30.0f;
	keyframe_Bryan.arreglo[35].giroY = 210.0f;
	keyframe_Bryan.arreglo[35].giroZ = 0.0f;

	keyframe_Bryan.arreglo[36].mov_x = 100.0f;
	keyframe_Bryan.arreglo[36].mov_y = 10.0f;
	keyframe_Bryan.arreglo[36].mov_z = 80.0f;
	keyframe_Bryan.arreglo[36].giroX = -40.0f;
	keyframe_Bryan.arreglo[36].giroY = 220.0f;
	keyframe_Bryan.arreglo[36].giroZ = 0.0f;

	keyframe_Bryan.arreglo[37].mov_x = 100.0f;
	keyframe_Bryan.arreglo[37].mov_y = 10.0f;
	keyframe_Bryan.arreglo[37].mov_z = 80.0f;
	keyframe_Bryan.arreglo[37].giroX = -45.0f;
	keyframe_Bryan.arreglo[37].giroY = 235.0f;
	keyframe_Bryan.arreglo[37].giroZ = 0.0f;

	keyframe_Bryan.arreglo[38].mov_x = 100.0f;
	keyframe_Bryan.arreglo[38].mov_y = 10.0f;
	keyframe_Bryan.arreglo[38].mov_z = 80.0f;
	keyframe_Bryan.arreglo[38].giroX = -40.0f;
	keyframe_Bryan.arreglo[38].giroY = 240.0f;
	keyframe_Bryan.arreglo[38].giroZ = 0.0f;

	keyframe_Bryan.arreglo[39].mov_x = 100.0f;
	keyframe_Bryan.arreglo[39].mov_y = 10.0f;
	keyframe_Bryan.arreglo[39].mov_z = 80.0f;
	keyframe_Bryan.arreglo[39].giroX = -30.0f;
	keyframe_Bryan.arreglo[39].giroY = 250.0f;
	keyframe_Bryan.arreglo[39].giroZ = 0.0f;

	keyframe_Bryan.arreglo[40].mov_x = 100.0f;
	keyframe_Bryan.arreglo[40].mov_y = 10.0f;
	keyframe_Bryan.arreglo[40].mov_z = 80.0f;
	keyframe_Bryan.arreglo[40].giroX = -20.0f;
	keyframe_Bryan.arreglo[40].giroY = 260.0f;
	keyframe_Bryan.arreglo[40].giroZ = 0.0f;

	keyframe_Bryan.arreglo[41].mov_x = 100.0f;
	keyframe_Bryan.arreglo[41].mov_y = 10.0f;
	keyframe_Bryan.arreglo[41].mov_z = 80.0f;
	keyframe_Bryan.arreglo[41].giroX = -10.0f;
	keyframe_Bryan.arreglo[41].giroY = 270.0f;
	keyframe_Bryan.arreglo[41].giroZ = 0.0f;

	keyframe_Bryan.arreglo[42].mov_x = 100.0f;
	keyframe_Bryan.arreglo[42].mov_y = 10.0f;
	keyframe_Bryan.arreglo[42].mov_z = 70.0f;
	keyframe_Bryan.arreglo[42].giroX = 0.0f;
	keyframe_Bryan.arreglo[42].giroY = 270.0f;
	keyframe_Bryan.arreglo[42].giroZ = 0.0f;

	keyframe_Bryan.arreglo[43].mov_x = 100.0f;
	keyframe_Bryan.arreglo[43].mov_y = 5.0f;
	keyframe_Bryan.arreglo[43].mov_z = 60.0f;
	keyframe_Bryan.arreglo[43].giroX = 0.0f;
	keyframe_Bryan.arreglo[43].giroY = 270.0f;
	keyframe_Bryan.arreglo[43].giroZ = 0.0f;

	keyframe_Bryan.arreglo[44].mov_x = 100.0f;
	keyframe_Bryan.arreglo[44].mov_y = 0.0f;
	keyframe_Bryan.arreglo[44].mov_z = 50.0f;
	keyframe_Bryan.arreglo[44].giroX = 0.0f;
	keyframe_Bryan.arreglo[44].giroY = 270.0f;
	keyframe_Bryan.arreglo[44].giroZ = 0.0f;

	keyframe_Bryan.arreglo[45].mov_x = 100.0f;
	keyframe_Bryan.arreglo[45].mov_y = -5.0f;
	keyframe_Bryan.arreglo[45].mov_z = 40.0f;
	keyframe_Bryan.arreglo[45].giroX = 0.0f;
	keyframe_Bryan.arreglo[45].giroY = 270.0f;
	keyframe_Bryan.arreglo[45].giroZ = 0.0f;

	keyframe_Bryan.arreglo[46].mov_x = 100.0f;
	keyframe_Bryan.arreglo[46].mov_y = 0.0f;
	keyframe_Bryan.arreglo[46].mov_z = 30.0f;
	keyframe_Bryan.arreglo[46].giroX = 0.0f;
	keyframe_Bryan.arreglo[46].giroY = 270.0f;
	keyframe_Bryan.arreglo[46].giroZ = 0.0f;

	keyframe_Bryan.arreglo[47].mov_x = 100.0f;
	keyframe_Bryan.arreglo[47].mov_y = 5.0f;
	keyframe_Bryan.arreglo[47].mov_z = 20.0f;
	keyframe_Bryan.arreglo[47].giroX = 0.0f;
	keyframe_Bryan.arreglo[47].giroY = 270.0f;
	keyframe_Bryan.arreglo[47].giroZ = 0.0f;

	keyframe_Bryan.arreglo[48].mov_x = 100.0f;
	keyframe_Bryan.arreglo[48].mov_y = 10.0f;
	keyframe_Bryan.arreglo[48].mov_z = 10.0f;
	keyframe_Bryan.arreglo[48].giroX = 0.0f;
	keyframe_Bryan.arreglo[48].giroY = 270.0f;
	keyframe_Bryan.arreglo[48].giroZ = 0.0f;

	keyframe_Bryan.arreglo[49].mov_x = 100.0f;
	keyframe_Bryan.arreglo[49].mov_y = 15.0f;
	keyframe_Bryan.arreglo[49].mov_z = 0.0f;
	keyframe_Bryan.arreglo[49].giroX = 0.0f;
	keyframe_Bryan.arreglo[49].giroY = 270.0f;
	keyframe_Bryan.arreglo[49].giroZ = 0.0f;

	keyframe_Bryan.arreglo[50].mov_x = 100.0f;
	keyframe_Bryan.arreglo[50].mov_y = 10.0f;
	keyframe_Bryan.arreglo[50].mov_z = 0.0f;
	keyframe_Bryan.arreglo[50].giroX = 10.0f;
	keyframe_Bryan.arreglo[50].giroY = 280.0f;
	keyframe_Bryan.arreglo[50].giroZ = 0.0f;

	keyframe_Bryan.arreglo[51].mov_x = 100.0f;
	keyframe_Bryan.arreglo[51].mov_y = 10.0f;
	keyframe_Bryan.arreglo[51].mov_z = 0.0f;
	keyframe_Bryan.arreglo[51].giroX = 20.0f;
	keyframe_Bryan.arreglo[51].giroY = 290.0f;
	keyframe_Bryan.arreglo[51].giroZ = 0.0f;

	keyframe_Bryan.arreglo[52].mov_x = 100.0f;
	keyframe_Bryan.arreglo[52].mov_y = 10.0f;
	keyframe_Bryan.arreglo[52].mov_z = 0.0f;
	keyframe_Bryan.arreglo[52].giroX = 30.0f;
	keyframe_Bryan.arreglo[52].giroY = 300.0f;
	keyframe_Bryan.arreglo[52].giroZ = 0.0f;

	keyframe_Bryan.arreglo[53].mov_x = 100.0f;
	keyframe_Bryan.arreglo[53].mov_y = 10.0f;
	keyframe_Bryan.arreglo[53].mov_z = 0.0f;
	keyframe_Bryan.arreglo[53].giroX = 40.0f;
	keyframe_Bryan.arreglo[53].giroY = 310.0f;
	keyframe_Bryan.arreglo[53].giroZ = 0.0f;

	keyframe_Bryan.arreglo[54].mov_x = 100.0f;
	keyframe_Bryan.arreglo[54].mov_y = 10.0f;
	keyframe_Bryan.arreglo[54].mov_z = 0.0f;
	keyframe_Bryan.arreglo[54].giroX = 45.0f;
	keyframe_Bryan.arreglo[54].giroY = 320.0f;
	keyframe_Bryan.arreglo[54].giroZ = 0.0f;

	keyframe_Bryan.arreglo[55].mov_x = 100.0f;
	keyframe_Bryan.arreglo[55].mov_y = 10.0f;
	keyframe_Bryan.arreglo[55].mov_z = 0.0f;
	keyframe_Bryan.arreglo[55].giroX = 40.0f;
	keyframe_Bryan.arreglo[55].giroY = 330.0f;
	keyframe_Bryan.arreglo[55].giroZ = 0.0f;

	keyframe_Bryan.arreglo[56].mov_x = 100.0f;
	keyframe_Bryan.arreglo[56].mov_y = 10.0f;
	keyframe_Bryan.arreglo[56].mov_z = 0.0f;
	keyframe_Bryan.arreglo[56].giroX = 30.0f;
	keyframe_Bryan.arreglo[56].giroY = 340.0f;
	keyframe_Bryan.arreglo[56].giroZ = 0.0f;

	keyframe_Bryan.arreglo[57].mov_x = 100.0f;
	keyframe_Bryan.arreglo[57].mov_y = 10.0f;
	keyframe_Bryan.arreglo[57].mov_z = 0.0f;
	keyframe_Bryan.arreglo[57].giroX = 20.0f;
	keyframe_Bryan.arreglo[57].giroY = 350.0f;
	keyframe_Bryan.arreglo[57].giroZ = 0.0f;

	keyframe_Bryan.arreglo[58].mov_x = 100.0f;
	keyframe_Bryan.arreglo[58].mov_y = 10.0f;
	keyframe_Bryan.arreglo[58].mov_z = 0.0f;
	keyframe_Bryan.arreglo[58].giroX = 10.0f;
	keyframe_Bryan.arreglo[58].giroY = 360.0f;
	keyframe_Bryan.arreglo[58].giroZ = 0.0f;

	keyframe_Bryan.arreglo[59].mov_x = 90.0f;
	keyframe_Bryan.arreglo[59].mov_y = 10.0f;
	keyframe_Bryan.arreglo[59].mov_z = 0.0f;
	keyframe_Bryan.arreglo[59].giroX = 0.0f;
	keyframe_Bryan.arreglo[59].giroY = 360.0f;
	keyframe_Bryan.arreglo[59].giroZ = 0.0f;

	keyframe_Bryan.arreglo[60].mov_x = 80.0f;
	keyframe_Bryan.arreglo[60].mov_y = 10.0f;
	keyframe_Bryan.arreglo[60].mov_z = 0.0f;
	keyframe_Bryan.arreglo[60].giroX = 0.0f;
	keyframe_Bryan.arreglo[60].giroY = 360.0f;
	keyframe_Bryan.arreglo[60].giroZ = 0.0f;

	keyframe_Bryan.arreglo[61].mov_x = 60.0f;
	keyframe_Bryan.arreglo[61].mov_y = 10.0f;
	keyframe_Bryan.arreglo[61].mov_z = 0.0f;
	keyframe_Bryan.arreglo[61].giroX = 0.0f;
	keyframe_Bryan.arreglo[61].giroY = 360.0f;
	keyframe_Bryan.arreglo[61].giroZ = 0.0f;

	keyframe_Bryan.arreglo[62].mov_x = 40.0f;
	keyframe_Bryan.arreglo[62].mov_y = 10.0f;
	keyframe_Bryan.arreglo[62].mov_z = 0.0f;
	keyframe_Bryan.arreglo[62].giroX = 0.0f;
	keyframe_Bryan.arreglo[62].giroY = 360.0f;
	keyframe_Bryan.arreglo[62].giroZ = 0.0f;

	keyframe_Bryan.arreglo[63].mov_x = 20.0f;
	keyframe_Bryan.arreglo[63].mov_y = 10.0f;
	keyframe_Bryan.arreglo[63].mov_z = 0.0f;
	keyframe_Bryan.arreglo[63].giroX = 0.0f;
	keyframe_Bryan.arreglo[63].giroY = 360.0f;
	keyframe_Bryan.arreglo[63].giroZ = 0.0f;

	keyframe_Bryan.arreglo[64].mov_x = 10.0f;
	keyframe_Bryan.arreglo[64].mov_y = 5.0f;
	keyframe_Bryan.arreglo[64].mov_z = 0.0f;
	keyframe_Bryan.arreglo[64].giroX = 0.0f;
	keyframe_Bryan.arreglo[64].giroY = 360.0f;
	keyframe_Bryan.arreglo[64].giroZ = 0.0f;

	keyframe_Bryan.arreglo[65].mov_x = 0.0f;
	keyframe_Bryan.arreglo[65].mov_y = 0.0f;
	keyframe_Bryan.arreglo[65].mov_z = 0.0f;
	keyframe_Bryan.arreglo[65].giroX = 0.0f;
	keyframe_Bryan.arreglo[65].giroY = 360.0f;
	keyframe_Bryan.arreglo[65].giroZ = 0.0f;


	KeyFrames keyframe_Piet = KeyFrames();

	keyframe_Piet.arreglo[0].mov_x = 0.0f;
	keyframe_Piet.arreglo[0].mov_y = 0.0f;
	keyframe_Piet.arreglo[0].mov_z = 0.0f;
	keyframe_Piet.arreglo[0].giroY = 0.0f;
	keyframe_Piet.arreglo[0].giroX = 0.0f;
	keyframe_Piet.arreglo[0].giroZ = 0.0f;

	keyframe_Piet.arreglo[1].mov_x = 25.0f;
	keyframe_Piet.arreglo[1].mov_y = 3.0f;
	keyframe_Piet.arreglo[1].mov_z = 0.0f;
	keyframe_Piet.arreglo[1].giroY = 360.0f;
	keyframe_Piet.arreglo[1].giroX = 0.0f;
	keyframe_Piet.arreglo[1].giroZ = 0.0f;

	keyframe_Piet.arreglo[2].mov_x = 42.0f;
	keyframe_Piet.arreglo[2].mov_y = 3.0f;
	keyframe_Piet.arreglo[2].mov_z = 0.0f;
	keyframe_Piet.arreglo[2].giroY = 360.0f;
	keyframe_Piet.arreglo[2].giroX = 0.0f;
	keyframe_Piet.arreglo[2].giroZ = 0.0f;

	keyframe_Piet.arreglo[3].mov_x = 58.0f;
	keyframe_Piet.arreglo[3].mov_y = 3.0f;
	keyframe_Piet.arreglo[3].mov_z = -4.0f;
	keyframe_Piet.arreglo[3].giroY = 380.0f;
	keyframe_Piet.arreglo[3].giroX = 0.0f;
	keyframe_Piet.arreglo[3].giroZ = 0.0f;

	keyframe_Piet.arreglo[4].mov_x = 70.0f;
	keyframe_Piet.arreglo[4].mov_y = 3.0f;
	keyframe_Piet.arreglo[4].mov_z = -13.0f;
	keyframe_Piet.arreglo[4].giroY = 426.0f;
	keyframe_Piet.arreglo[4].giroX = 0.0f;
	keyframe_Piet.arreglo[4].giroZ = 0.0f;

	keyframe_Piet.arreglo[5].mov_x = 75.0f;
	keyframe_Piet.arreglo[5].mov_y = 12.0f;
	keyframe_Piet.arreglo[5].mov_z = -57.0f;
	keyframe_Piet.arreglo[5].giroY = 436.0f;
	keyframe_Piet.arreglo[5].giroX = 12.0f;
	keyframe_Piet.arreglo[5].giroZ = 0.0f;

	keyframe_Piet.arreglo[6].mov_x = 75.0f;
	keyframe_Piet.arreglo[6].mov_y = 20.0f;
	keyframe_Piet.arreglo[6].mov_z = -84.0f;
	keyframe_Piet.arreglo[6].giroY = 427.0f;
	keyframe_Piet.arreglo[6].giroX = 17.0f;
	keyframe_Piet.arreglo[6].giroZ = 0.0f;

	keyframe_Piet.arreglo[7].mov_x = 75.0f;
	keyframe_Piet.arreglo[7].mov_y = 35.0f;
	keyframe_Piet.arreglo[7].mov_z = -117.0f;
	keyframe_Piet.arreglo[7].giroY = 425.0f;
	keyframe_Piet.arreglo[7].giroX = 28.0f;
	keyframe_Piet.arreglo[7].giroZ = 0.0f;

	keyframe_Piet.arreglo[8].mov_x = 81.0f;
	keyframe_Piet.arreglo[8].mov_y = 45.0f;
	keyframe_Piet.arreglo[8].mov_z = -135.0f;
	keyframe_Piet.arreglo[8].giroY = 397.0f;
	keyframe_Piet.arreglo[8].giroX = 24.0f;
	keyframe_Piet.arreglo[8].giroZ = 0.0f;

	keyframe_Piet.arreglo[9].mov_x = 91.0f;
	keyframe_Piet.arreglo[9].mov_y = 50.0f;
	keyframe_Piet.arreglo[9].mov_z = -147.0f;
	keyframe_Piet.arreglo[9].giroY = 371.0f;
	keyframe_Piet.arreglo[9].giroX = 10.0f;
	keyframe_Piet.arreglo[9].giroZ = 0.0f;

	keyframe_Piet.arreglo[10].mov_x = 104.0f;
	keyframe_Piet.arreglo[10].mov_y = 50.0f;
	keyframe_Piet.arreglo[10].mov_z = -147.0f;
	keyframe_Piet.arreglo[10].giroY = 362.0f;
	keyframe_Piet.arreglo[10].giroX = 0.0f;
	keyframe_Piet.arreglo[10].giroZ = 0.0f;

	keyframe_Piet.arreglo[12].mov_x = 140.0f;
	keyframe_Piet.arreglo[12].mov_y = 50.0f;
	keyframe_Piet.arreglo[12].mov_z = -147.0f;
	keyframe_Piet.arreglo[12].giroY = 356.0f;
	keyframe_Piet.arreglo[12].giroX = 0.0f;
	keyframe_Piet.arreglo[12].giroZ = 0.0f;

	keyframe_Piet.arreglo[13].mov_x = 150.0f;
	keyframe_Piet.arreglo[13].mov_y = 50.0f;
	keyframe_Piet.arreglo[13].mov_z = -135.0f;
	keyframe_Piet.arreglo[13].giroY = 301.0f;
	keyframe_Piet.arreglo[13].giroX = 0.0f;
	keyframe_Piet.arreglo[13].giroZ = 0.0f;

	keyframe_Piet.arreglo[11].mov_x = 122.0f;
	keyframe_Piet.arreglo[11].mov_y = 50.0f;
	keyframe_Piet.arreglo[11].mov_z = -147.0f;
	keyframe_Piet.arreglo[11].giroY = 362.0f;
	keyframe_Piet.arreglo[11].giroX = 0.0f;
	keyframe_Piet.arreglo[11].giroZ = 0.0f;

	keyframe_Piet.arreglo[14].mov_x = 155.0f;
	keyframe_Piet.arreglo[14].mov_y = 50.0f;
	keyframe_Piet.arreglo[14].mov_z = -120.0f;
	keyframe_Piet.arreglo[14].giroY = 273.0f;
	keyframe_Piet.arreglo[14].giroX = 0.0f;
	keyframe_Piet.arreglo[14].giroZ = 0.0f;

	keyframe_Piet.arreglo[15].mov_x = 155.0f;
	keyframe_Piet.arreglo[15].mov_y = 50.0f;
	keyframe_Piet.arreglo[15].mov_z = -90.0f;
	keyframe_Piet.arreglo[15].giroY = 273.0f;
	keyframe_Piet.arreglo[15].giroX = 0.0f;
	keyframe_Piet.arreglo[15].giroZ = 0.0f;

	keyframe_Piet.arreglo[16].mov_x = 155.0f;
	keyframe_Piet.arreglo[16].mov_y = 50.0f;
	keyframe_Piet.arreglo[16].mov_z = -67.0f;
	keyframe_Piet.arreglo[16].giroY = 273.0f;
	keyframe_Piet.arreglo[16].giroX = 9.0f;
	keyframe_Piet.arreglo[16].giroZ = 0.0f;

	keyframe_Piet.arreglo[17].mov_x = 155.0f;
	keyframe_Piet.arreglo[17].mov_y = 46.0f;
	keyframe_Piet.arreglo[17].mov_z = -49.0f;
	keyframe_Piet.arreglo[17].giroY = 273.0f;
	keyframe_Piet.arreglo[17].giroX = 19.0f;
	keyframe_Piet.arreglo[17].giroZ = 0.0f;

	keyframe_Piet.arreglo[18].mov_x = 155.0f;
	keyframe_Piet.arreglo[18].mov_y = 37.0f;
	keyframe_Piet.arreglo[18].mov_z = -30.0f;
	keyframe_Piet.arreglo[18].giroY = 273.0f;
	keyframe_Piet.arreglo[18].giroX = 19.0f;
	keyframe_Piet.arreglo[18].giroZ = 0.0f;

	keyframe_Piet.arreglo[19].mov_x = 155.0f;
	keyframe_Piet.arreglo[19].mov_y = 31.0f;
	keyframe_Piet.arreglo[19].mov_z = -20.0f;
	keyframe_Piet.arreglo[19].giroY = 273.0f;
	keyframe_Piet.arreglo[19].giroX = 9.0f;
	keyframe_Piet.arreglo[19].giroZ = 0.0f;

	keyframe_Piet.arreglo[20].mov_x = 155.0f;
	keyframe_Piet.arreglo[20].mov_y = 25.0f;
	keyframe_Piet.arreglo[20].mov_z = -7.0f;
	keyframe_Piet.arreglo[20].giroY = 273.0f;
	keyframe_Piet.arreglo[20].giroX = 0.0f;
	keyframe_Piet.arreglo[20].giroZ = 0.0f;

	keyframe_Piet.arreglo[21].mov_x = 141.0f;
	keyframe_Piet.arreglo[21].mov_y = 25.0f;
	keyframe_Piet.arreglo[21].mov_z = 46.0f;
	keyframe_Piet.arreglo[21].giroY = 273.0f;
	keyframe_Piet.arreglo[21].giroX = 0.0f;
	keyframe_Piet.arreglo[21].giroZ = 0.0f;

	keyframe_Piet.arreglo[22].mov_x = 129.0f;
	keyframe_Piet.arreglo[22].mov_y = 25.0f;
	keyframe_Piet.arreglo[22].mov_z = 60.0f;
	keyframe_Piet.arreglo[22].giroY = 251.0f;
	keyframe_Piet.arreglo[22].giroX = 0.0f;
	keyframe_Piet.arreglo[22].giroZ = 0.0f;

	keyframe_Piet.arreglo[23].mov_x = 115.0f;
	keyframe_Piet.arreglo[23].mov_y = 25.0f;
	keyframe_Piet.arreglo[23].mov_z = 70.0f;
	keyframe_Piet.arreglo[23].giroY = 215.0f;
	keyframe_Piet.arreglo[23].giroX = 0.0f;
	keyframe_Piet.arreglo[23].giroZ = 0.0f;

	keyframe_Piet.arreglo[24].mov_x = 88.0f;
	keyframe_Piet.arreglo[24].mov_y = 23.0f;
	keyframe_Piet.arreglo[24].mov_z = 81.0f;
	keyframe_Piet.arreglo[24].giroY = 190.0f;
	keyframe_Piet.arreglo[24].giroX = 0.0f;
	keyframe_Piet.arreglo[24].giroZ = 0.0f;

	keyframe_Piet.arreglo[25].mov_x = 69.0f;
	keyframe_Piet.arreglo[25].mov_y = 14.0f;
	keyframe_Piet.arreglo[25].mov_z = 81.0f;
	keyframe_Piet.arreglo[25].giroY = 181.0f;
	keyframe_Piet.arreglo[25].giroX = 0.0f;
	keyframe_Piet.arreglo[25].giroZ = 0.0f;

	keyframe_Piet.arreglo[26].mov_x = 38.0f;
	keyframe_Piet.arreglo[26].mov_y = 14.0f;
	keyframe_Piet.arreglo[26].mov_z = 81.0f;
	keyframe_Piet.arreglo[26].giroY = 181.0f;
	keyframe_Piet.arreglo[26].giroX = 0.0f;
	keyframe_Piet.arreglo[26].giroZ = 0.0f;

	keyframe_Piet.arreglo[27].mov_x = -6.0f;
	keyframe_Piet.arreglo[27].mov_y = 14.0f;
	keyframe_Piet.arreglo[27].mov_z = 81.0f;
	keyframe_Piet.arreglo[27].giroY = 170.0f;
	keyframe_Piet.arreglo[27].giroX = -12.0f;
	keyframe_Piet.arreglo[27].giroZ = 0.0f;

	keyframe_Piet.arreglo[28].mov_x = -23.0f;
	keyframe_Piet.arreglo[28].mov_y = 14.0f;
	keyframe_Piet.arreglo[28].mov_z = 54.0f;
	keyframe_Piet.arreglo[28].giroY = 130.0f;
	keyframe_Piet.arreglo[28].giroX = -12.0f;
	keyframe_Piet.arreglo[28].giroZ = 0.0f;

	keyframe_Piet.arreglo[29].mov_x = -32.0f;
	keyframe_Piet.arreglo[29].mov_y = 14.0f;
	keyframe_Piet.arreglo[29].mov_z = 27.0f;
	keyframe_Piet.arreglo[29].giroY = 91.0f;
	keyframe_Piet.arreglo[29].giroX = 10.0f;
	keyframe_Piet.arreglo[29].giroZ = 0.0f;

	keyframe_Piet.arreglo[30].mov_x = -26.0f;
	keyframe_Piet.arreglo[30].mov_y = 15.0f;
	keyframe_Piet.arreglo[30].mov_z = 13.0f;
	keyframe_Piet.arreglo[30].giroY = 64.0f;
	keyframe_Piet.arreglo[30].giroX = 10.0f;
	keyframe_Piet.arreglo[30].giroZ = 0.0f;

	keyframe_Piet.arreglo[31].mov_x = -21.0f;
	keyframe_Piet.arreglo[31].mov_y = 15.0f;
	keyframe_Piet.arreglo[31].mov_z = 4.0f;
	keyframe_Piet.arreglo[31].giroY = 31.0f;
	keyframe_Piet.arreglo[31].giroX = 0.0f;
	keyframe_Piet.arreglo[31].giroZ = 0.0f;

	keyframe_Piet.arreglo[32].mov_x = -12.0f;
	keyframe_Piet.arreglo[32].mov_y = 11.0f;
	keyframe_Piet.arreglo[32].mov_z = 0.0f;
	keyframe_Piet.arreglo[32].giroY = 10.0f;
	keyframe_Piet.arreglo[32].giroX = 0;
	keyframe_Piet.arreglo[32].giroZ = 0.0f;

	keyframe_Piet.arreglo[33].mov_x = -7.0f;
	keyframe_Piet.arreglo[33].mov_y = 7.0f;
	keyframe_Piet.arreglo[33].mov_z = 0.0f;
	keyframe_Piet.arreglo[33].giroY = 0;
	keyframe_Piet.arreglo[33].giroX = 0;
	keyframe_Piet.arreglo[33].giroZ = 0.0f;

	keyframe_Piet.arreglo[34].mov_x = -3.0f;
	keyframe_Piet.arreglo[34].mov_y = 3.0f;
	keyframe_Piet.arreglo[34].mov_z = 0.0f;
	keyframe_Piet.arreglo[34].giroY = 0;
	keyframe_Piet.arreglo[34].giroX = 0;
	keyframe_Piet.arreglo[34].giroZ = 0.0f;

	keyframe_Piet.arreglo[35].mov_x = 0.0f;
	keyframe_Piet.arreglo[35].mov_y = 0.0f;
	keyframe_Piet.arreglo[35].mov_z = 0.0f;
	keyframe_Piet.arreglo[35].giroY = 0;
	keyframe_Piet.arreglo[35].giroX = 0;
	keyframe_Piet.arreglo[35].giroZ = 0.0f;
	

	glm::vec3 posblackhawk = glm::vec3(-120.0f, 30.0f, -130.0f);

	//-----------------------A U D I O ---------------------------------------
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	ISoundEngine* ambiental = createIrrKlangDevice();
	//Sonido ambiente
	ambiental->play2D("Media/AmbienteToyStory.ogg", true);
	ambiental->setSoundVolume(0.1);
	

	//Helice
	float rotYHelice = 0.0f;
	float rotRotor = 0.0f;
	float rotYHeliceOffset=0.01f;
	SpectreRotX = 90.0f;
	SpectreRotY = 0.0f;
	AnimacionVal = 0;
	DisparoSpectre = 0;
	SpectreMovX = 0.0f;
	SpectreMovY = 0.0f;
	SpectreMovZ = 0.0f;
	KillJMovZ = 0.0f;
	KillJBrazosRotX = 0.0f;
	KillJPDrotX = 0.0f;
	KillJPIrotX = 0.0f;
	KillJCamina = 0;

	////Loop mientras no se cierra la ventana ############# INICIA CICLO WHILE ################
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();

		//para keyframes
		//inputKeyframes(mainWindow.getsKeys(),mainWindow.getAction());
		if (play == false) {
			resetElements();
			interpolation();
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
			rotYHeliceOffset = 0.01f;
			rotYHelice = 0.0f;
		}
		//keyframe_Bryan.inputKeyframes(mainWindow.getsKeys(), mainWindow.getAction());

		keyframe_Bryan.iniciaAutomatico();

		keyframe_Piet.iniciaAutomatico();

		//keyframe_Piet.inputKeyframes(mainWindow.getsKeys(), mainWindow.getAction());

		animate();
		keyframe_Bryan.animate();
		keyframe_Piet.animate();

		//ANIMACION HELICE
		rotYHelice += rotYHeliceOffset * deltaTime;
		if (playIndex < 4) {
			rotYHeliceOffset += 0.1f;
		}
		else if (playIndex > 32) {
			rotYHeliceOffset -= 0.2f;
			if (rotYHeliceOffset < 0) rotYHeliceOffset = 0;
		}



		// MANEJO DE CAMARA AEREA Y FIJA
		numCam = mainWindow.getCamaraVal();

		if (numCam == 0) {
			camera = &cameraLibre;
			camera->keyControl(mainWindow.getsKeys(), deltaTime);
			camera->mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		}
		else if (numCam == 1) {
			camera = &cameraWheezy;
			camera->keyControl(mainWindow.getsKeys(), deltaTime);
			camera->mouseControl(mainWindow.getXChange(), 0.0f);
		}
		else if (numCam == 2) {
			camera = &cameraJett;
			camera->keyControl(mainWindow.getsKeys(), deltaTime);
			camera->mouseControl(mainWindow.getXChange(), 0.0f);
		}
		else if (numCam == 3) {
			camera = &cameraFrijolito;
			camera->keyControl(mainWindow.getsKeys(), deltaTime);
			camera->mouseControl(mainWindow.getXChange(), 0.0f);
		}

		//posicion de la camara Wheezy
		glm::vec3 poscam = cameraWheezy.getCameraPosition();
		//direccion de la camara Wheezy
		glm::vec3 dircam = cameraWheezy.getCameraDirection();
		float angulo_cam = atan(dircam.z / dircam.x);
		angulo_cam += (90 * toRadians);
		if (dircam.x > 0) {
			angulo_cam += (180 * toRadians);
		}
		glm::vec3 poswheezy = glm::vec3(0, 0, 0);
		poswheezy.x = poscam.x + ((0 * cos(angulo_cam)) - (40 * sin(angulo_cam)));
		poswheezy.z = poscam.z + ((0 * sin(angulo_cam)) + (40 * cos(angulo_cam)));
		poswheezy.y = poscam.y - 12;


		//posicion de la camara Jett
		poscam = cameraJett.getCameraPosition();
		//direccion de la camara Jett
		dircam = cameraJett.getCameraDirection();
		float angulo_cam_jett = atan(dircam.z / dircam.x);
		angulo_cam_jett += (90 * toRadians);
		if (dircam.x > 0) {
			angulo_cam_jett += (180 * toRadians);
		}
		glm::vec3 posJett = glm::vec3(0, 0, 0);
		posJett.x = poscam.x + ((0 * cos(angulo_cam_jett)) - (40 * sin(angulo_cam_jett)));
		posJett.z = poscam.z + ((0 * sin(angulo_cam_jett)) + (40 * cos(angulo_cam_jett)));
		posJett.y = poscam.y - 12;


		//posicion de la camara Frijolito
		poscam = cameraFrijolito.getCameraPosition();
		//direccion de la camara Frijolito
		dircam = cameraFrijolito.getCameraDirection();
		float angulo_cam_frijolito = atan(dircam.z / dircam.x);
		angulo_cam_frijolito += (90 * toRadians);
		if (dircam.x > 0) {
			angulo_cam_frijolito += (180 * toRadians);
		}
		glm::vec3 posFrijolito = glm::vec3(0, 0, 0);
		posFrijolito.x = poscam.x + ((0 * cos(angulo_cam_frijolito)) - (15 * sin(angulo_cam_frijolito)));
		posFrijolito.z = poscam.z + ((0 * sin(angulo_cam_frijolito)) + (15 * cos(angulo_cam_frijolito)));
		posFrijolito.y = poscam.y - 5;

		//Cambio del ciclo de luz de dia y noche_____________________________________

		if (contadorDiaNoche <= 1.0f and dia) {
			contadorDiaNoche += deltaTime * 0.0001f;
		}
		else if (contadorDiaNoche >= 1.0f and dia) {
			dia = false;
		}
		else if (contadorDiaNoche >= 0.0f and !dia) {
			contadorDiaNoche -= deltaTime * 0.0001f;
		}
		else if (contadorDiaNoche <= 0.0f and !dia) {
			dia = true;
		}
		//printf("\nContador = %f", contadorDiaNoche);
		mainLight.ChangeDiffuseAmbient(contadorDiaNoche, 0.3);

		//Movimiento del led de la cama ______________________________________________
		if (posicionLedX >= -248.0f and banderaLedCama == 0) {
			posicionLedX -= deltaTime * ledOffset;
			//printf("\nposicionLedX = %f", posicionLedX);
		}
		else if (posicionLedX <= -248.0f and banderaLedCama == 0) {
			banderaLedCama = 1;
		}
		else if (posicionLedX <= -45.0f and banderaLedCama == 1) {
			posicionLedX += deltaTime * ledOffset;
			//printf("\nposicionLedX = %f", posicionLedX);
		}
		else if (posicionLedX >= -45.0f and banderaLedCama == 1) {
			banderaLedCama = 2;
		}
		else if (posicionLedZ <= 140.0f and banderaLedCama == 2) {
			posicionLedZ += deltaTime * ledOffset;
			//printf("\nposicionLedZ = %f", posicionLedZ);
		}
		else if (posicionLedZ >= 140.0f and banderaLedCama == 2) {
			banderaLedCama = 3;
		}
		else if (posicionLedZ >= 40.0f and banderaLedCama == 3) {
			posicionLedZ -= deltaTime * ledOffset;
			//printf("\nposicionLedZ = %f", posicionLedZ);
		}
		else if (posicionLedZ <= 40.0f and banderaLedCama == 3) {
			banderaLedCama = 0;
		}
		pointLightsCama[0].SetPos(glm::vec3(posicionLedX, 20.0f, posicionLedZ));
		pointLightsSpike[0].SetPos(glm::vec3(posicionLedX, 20.0f, posicionLedZ));

//		-----------------------------ANIMACION VALORANT-----------------------------------
		if (SpectreRotX >= 0.0f and AnimacionVal == 0) {
			SpectreRotX -= deltaTime * 0.1f;
			FenixBIrotX -= deltaTime * 0.1f;
			SpectreMovY += deltaTime * 0.004f;
			SpectreMovX -= deltaTime * 0.003f;
			KillJRotY -= deltaTime * 0.1f;
			KillJBrazosRotX -= deltaTime * 0.05;
		}
		else if (SpectreRotX <= 0.0f and AnimacionVal == 0) {
			AnimacionVal = 1;
			AuxSpectreRotX = SpectreRotX;
		}
		else if (KillJMovZ <= 40.0f and AnimacionVal == 1) {
			KillJMovZ += deltaTime * 0.06f;
			FenixRot += deltaTime * 0.04f;
			SpectreRotY += deltaTime * 0.04f;
			SpectreMovZ += deltaTime * 0.04 * sin(SpectreMovY * toRadians);
			SpectreMovX += deltaTime * 0.002 * cos(SpectreMovY * toRadians);

			if (DisparoSpectre == 0 and SpectreRotX <= 5.0f) { //Animacion de disparo
				SpectreRotX += deltaTime * 0.5f;
			}
			else if (DisparoSpectre == 0 and SpectreRotX >= 5.0f) {
				DisparoSpectre = 1;
			}
			else if (DisparoSpectre == 1 and SpectreRotX >= 0.0f) {
				SpectreRotX -= deltaTime * 0.5f;
			}
			else if (DisparoSpectre == 1 and SpectreRotX <= 0.0f) {
				DisparoSpectre = 0;
			}

			if (KillJCamina == 0 and KillJPDrotX <= 30.0f) { //Animacion de caminado de Kill Joy
				KillJPDrotX += deltaTime * 2.5f;			//Pie Derecho
			}
			else if (KillJCamina == 0 and KillJPDrotX >= 30.0f) {
				KillJCamina = 1;
			}
			else if (KillJCamina == 1 and KillJPDrotX >= 0.0f) {
				KillJPDrotX -= deltaTime * 2.5f;
			}
			else if (KillJCamina == 1 and KillJPDrotX <= 0.0f) {
				KillJCamina = 2;
			}
			if (KillJCamina == 2 and KillJPIrotX <= 30.0f) { //Animacion de caminado de Kill Joy
				KillJPIrotX += deltaTime * 2.5f;			//Pie Izquierdo
			}
			else if (KillJCamina == 2 and KillJPIrotX >= 30.0f) {
				KillJCamina = 3;
			}
			else if (KillJCamina == 3 and KillJPIrotX >= 0.0f) {
				KillJPIrotX -= deltaTime * 2.5f;
			}
			else if (KillJCamina == 3 and KillJPIrotX <= 0.0f) {
				KillJCamina = 0;
			}
		}
		else if (KillJMovZ >= 40.0f and AnimacionVal == 1) {
			AnimacionVal = 2;
			SpectreRotX = AuxSpectreRotX;
			DisparoSpectre = 0;
			KillJPDrotX = 0.0f;
			KillJPIrotX = 0.0f;
		}
		else if (KillJRotY <= 0.0f and AnimacionVal == 2) {
			KillJRotY += deltaTime * 0.5f;
			KillJBrazosRotX += deltaTime * 0.5;
		}
		else if (KillJRotY >= 0.0f and AnimacionVal == 2) {
			AnimacionVal = 3;
		}
		else if (KillJRotY <= 90.0f and AnimacionVal == 3) {//Giro para correr como naruto
			KillJRotY += deltaTime * 0.5f;
			KillJRotX += deltaTime * 0.1;
		}
		else if (KillJRotY >= 90.0f and AnimacionVal == 3) {
			AnimacionVal = 4;
		}
		else if (KillJMovZ >= 0.0f and AnimacionVal == 4) {
			KillJMovZ -= deltaTime * 0.06f;
			FenixRot -= deltaTime * 0.04f;
			SpectreRotY -= deltaTime * 0.04f;
			SpectreMovZ -= deltaTime * 0.04 * sin(SpectreMovY * toRadians);
			SpectreMovX -= deltaTime * 0.002 * cos(SpectreMovY * toRadians);

			if (DisparoSpectre == 0 and SpectreRotX <= 5.0f) { //Animacion de disparo
				SpectreRotX += deltaTime * 0.5f;
			}
			else if (DisparoSpectre == 0 and SpectreRotX >= 5.0f) {
				DisparoSpectre = 1;
			}
			else if (DisparoSpectre == 1 and SpectreRotX >= 0.0f) {
				SpectreRotX -= deltaTime * 0.5f;
			}
			else if (DisparoSpectre == 1 and SpectreRotX <= 0.0f) {
				DisparoSpectre = 0;
			}

			if (KillJCamina == 0 and KillJPDrotX <= 45.0f) { //Animacion de caminado de Kill Joy
				KillJPDrotX += deltaTime * 8.0f;			//Pie Derecho
			}
			else if (KillJCamina == 0 and KillJPDrotX >= 45.0f) {
				KillJCamina = 1;
			}
			else if (KillJCamina == 1 and KillJPDrotX >= -10.0f) {
				KillJPDrotX -= deltaTime * 8.0f;
			}
			else if (KillJCamina == 1 and KillJPDrotX <= -10.0f) {
				KillJCamina = 2;
			}
			if (KillJCamina == 2 and KillJPIrotX <= 45.0f) { //Animacion de caminado de Kill Joy
				KillJPIrotX += deltaTime * 8.0f;			//Pie Izquierdo
			}
			else if (KillJCamina == 2 and KillJPIrotX >= 45.0f) {
				KillJCamina = 3;
			}
			else if (KillJCamina == 3 and KillJPIrotX >= -10.0f) {
				KillJPIrotX -= deltaTime * 8.0f;
			}
			else if (KillJCamina == 3 and KillJPIrotX <= -10.0f) {
				KillJCamina = 0;
			}
		}
		else if (KillJMovZ <= 0.0f and AnimacionVal == 4) {
			AnimacionVal = 5;
			SpectreRotX = AuxSpectreRotX;
			DisparoSpectre = 0;
			KillJPDrotX = 0.0f;
			KillJPIrotX = 0.0f;
		}
		else if (KillJRotY >= 0.0f and AnimacionVal == 5) {
			SpectreRotX += deltaTime * 0.5f;
			FenixBIrotX += deltaTime * 0.5f;
			SpectreMovY -= deltaTime * 0.0225f;
			SpectreMovX += deltaTime * 0.0125f;

			KillJRotY -= deltaTime * 0.5f;
			KillJRotX -= deltaTime * 0.1;
			KillJBrazosRotX -= deltaTime * 0.27;

		}
		else if (KillJRotY <= 0.0f and AnimacionVal == 5) {
			AnimacionVal = 0;
			SpectreMovX = 0.0f;
			SpectreMovY = 0.0f;
			SpectreMovZ = 0.0f;
		}



//	Animación Spike
		//glm::vec3 distance = poswheezy - posSpike;

		if (distance(posJett, posSpike) <= 25.0f and movAroSpike <= 5.5f) {
			movAroSpike += deltaTime * 0.02f;
			giroSpike += deltaTime * 0.8f;
			spikeSube = true;
			ambiental->setSoundVolume(0.0);
			if (cancionVal) {
				cancionVal = false;
				engine->play2D("Media/la-cumbia-de-valorant.ogg", true);
			}
			engine->setSoundVolume(0.3);
		}
		else if (distance(posJett, posSpike) > 25.0f and movAroSpike > 0.0f) {
			movAroSpike -= deltaTime * 0.02f;
			giroSpike -= deltaTime * 0.8f;
			spikeSube = false;
			ambiental->setSoundVolume(0.3);
			engine->setSoundVolume(0.0);
		}

		//printf("\nDistancia a Spike = %f\nAltura Spike = %f", distance(posJett, posSpike),movAroSpike);


//	Animación Movimiento

		if (rotBrazo[numCam - 1] >= 360.0f or rotBrazo[numCam - 1] <= -360.0f) rotBrazo[numCam - 1] = 0.0f;
		//if (rotPierna[numCam - 1] >= 360 or rotPierna[numCam - 1] <= -360) rotPierna[numCam - 1] = 0;

		if (numCam != 0) { //verifica si se está utilizando una cámara de personaje
			switch (mainWindow.getDireccion())
			{
			case 1: //avanza al frente (W)
				rotBrazo[numCam - 1] += deltaTime * avanzaOffset;
				//rotPierna[numCam - 1] += deltaTime * avanzaOffset;
				if (rotDireccion[numCam - 1] < 0.0f) rotDireccion[numCam - 1] += deltaTime * avanzaOffset / 2;
				if (rotDireccion[numCam - 1] > 0.0f) rotDireccion[numCam - 1] -= deltaTime * avanzaOffset / 2;
				break;
			case 2: //avanza a la izquierda (A)
				rotBrazo[numCam - 1] += deltaTime * avanzaOffset;
				//rotPierna[numCam - 1] += deltaTime * avanzaOffset;
				if (rotDireccion[numCam - 1] < 90.0f) rotDireccion[numCam - 1] += deltaTime * avanzaOffset / 2;
				break;
			case 3: //avanza hacia atrás (S)
				rotBrazo[numCam - 1] -= deltaTime * avanzaOffset;
				//rotPierna[numCam - 1] -= deltaTime * avanzaOffset;
				if (rotDireccion[numCam - 1] < 0.0f) rotDireccion[numCam - 1] += deltaTime * avanzaOffset / 2;
				if (rotDireccion[numCam - 1] > 0.0f) rotDireccion[numCam - 1] -= deltaTime * avanzaOffset / 2;
				break;
			case 4: //avanza a la derecha (D)
				rotBrazo[numCam - 1] += deltaTime * avanzaOffset;
				//rotPierna[numCam - 1] += deltaTime * avanzaOffset;
				if (rotDireccion[numCam - 1] > -90.0f) rotDireccion[numCam - 1] -= deltaTime * avanzaOffset / 2;
				break;
			default:
				for (int i = 0; i < 4; i++) {
					if (rotBrazo[i] > 0.0f)rotBrazo[i] -= deltaTime * avanzaOffset;
					if (rotBrazo[i] < 0.0f)rotBrazo[i] += deltaTime * avanzaOffset;
					/*if (rotPierna[i] > 0)rotBrazo[i] -= deltaTime * avanzaOffset;
					if (rotPierna[i] < 0)rotBrazo[i] += deltaTime * avanzaOffset;*/
					if (rotDireccion[i] > 0.0f)rotBrazo[i] -= deltaTime * avanzaOffset / 2;
					if (rotDireccion[i] < 0.0f)rotBrazo[i] += deltaTime * avanzaOffset / 2;

					if (rotBrazo[i] < 25.0f and rotBrazo[i] > -25.0f) rotBrazo[i] = 0.0f;
				}
				break;
			}
		}
		//printf("\nnumCam = %d\nDireccion = %d", numCam, mainWindow.getDireccion());
		//if (numCam != 0) printf("\nRotacionBrazo = %f\nRotacionPierna = %f", rotBrazo[numCam - 1], rotPierna[numCam - 1]);

		//Movimiento del led deL ESCRITORIO ______________________________________________
		if (posicionLed1X <= 150.0f and banderaLedEscritorio == 0) {
			posicionLed1X += deltaTime * ledOffset * 0.5;
		}
		else if (posicionLed1X >= 150.0f and banderaLedEscritorio == 0) {
			banderaLedEscritorio = 1;
		}
		else if (posicionLed1X >= 0.0f and banderaLedEscritorio == 1) {
			posicionLed1X -= deltaTime * ledOffset * 0.5;
		}
		else if (posicionLed1X <= 0.0f and banderaLedEscritorio == 1) {
			banderaLedEscritorio = 0;
		}
		pointLightsCama[1].SetPos(glm::vec3(posicionLed1X, 60.0f, posicionLed1Z));
		pointLightsSpike[1].SetPos(glm::vec3(posicionLed1X, 60.0f, posicionLed1Z));

	//ANIMACION - GUARDAR JUGUETES
		if (mainWindow.getSaveToys()) {
			// ANIMACION BUS
			if (estado_bus == "PARAR_BUS")
			{
				if (posBus1Y > 3.0f || angulo_busZ < 0) {
					if (angulo_busZ < 0) {
						angulo_busZ += deltaTime * angulo_busZ_offset;
					}
					if (posBus1Y > 3.0f) {
						posBus1Y -= deltaTime * 0.1f;
					}
				}
				else {
					estado_bus = "GIRAR_BUS";
				}
			}
			else if (estado_bus == "GIRAR_BUS") {
				if (angulo_busY > 0.0f) {
					angulo_busY -= deltaTime * angulo_busY_offset;

				}
				else {
					estado_bus = "VUELTA_BUS";
					auxposx = posBus1X;
					auxposz = posBus1Z;
				}
			}
			else if (estado_bus == "VUELTA_BUS") {
				float radio = 80.0f;
				float centroX = auxposx - radio;
				float centroZ = auxposz;

				if (angulo_busY < 90.0f) {
					if (angulo_busY > 60.0f) {
						if (angulo_busX < 15.5f){
							angulo_busX += 0.5f * deltaTime;
						}
						posBus1Y += deltaTime * 0.18f;
					}
					angulo_busY += deltaTime * angulo_busY_offset * 0.8f;
					posBus1X = centroX + (radio * cos((0 - angulo_busY) * toRadians));
					posBus1Z = centroZ + (radio * sin((0 - angulo_busY) * toRadians));
				}
				else {
					estado_bus = "SUBE_BUS";
					auxposx = posBus1X;
					auxposz = posBus1Z;

				}
			}
			else if (estado_bus == "SUBE_BUS") {

				if (posBus1X > -225.0f) {
					posBus1Y += deltaTime * 0.1f*1.2f;
					posBus1X -= deltaTime * 0.3f*1.2f;
				}
				else {
					estado_bus = "ACOMODA_BUS";
					auxposx = posBus1X;
					auxposz = posBus1Z;
				}
			}
			else if (estado_bus == "ACOMODA_BUS") {
				float radio = 20.0f;
				float centroX = auxposx;
				float centroZ = auxposz - radio;

				if (angulo_busY > 20.0f) {
					if (posBus1Y < 14.0f) {
						posBus1Y += deltaTime * 0.1f * 1.2f;
					}
					if(angulo_busX > 0.0f){
						angulo_busX -= 0.6f * deltaTime;
					}
					

					angulo_busY -= deltaTime * angulo_busY_offset * 0.6f;
					posBus1X = centroX + (radio * cos((-180 - angulo_busY) * toRadians));
					posBus1Z = centroZ + (radio * sin((-180 - angulo_busY) * toRadians));
				}
				else {
					estado_bus = "BUS_LISTO";
				}
			}

			// ANIMACION CAR
			if (estado_car == "VUELTA_CAR") {
				float radio = 46.0f;
				float centroX = auxPosCarx - radio;
				float centroZ = auxPosCarz;

				if (angulo_carY < 90.0f) {
					angulo_carY += deltaTime * angulo_carY_offset * 0.7;
					posCar1X = centroX + (radio * cos((0 - angulo_carY) * toRadians));
					posCar1Z = centroZ + (radio * sin((0 - angulo_carY) * toRadians));
				}
				else {
					estado_car = "AVANZA_CAR";
					auxPosCarx = posCar1X;
				}
			}
			else if (estado_car == "AVANZA_CAR") {
				if (posCar1X > auxPosCarx - 113) {
					if (posCar1X < auxPosCarx - 80) {
						if (angulo_carX < 15.5f) {
							angulo_carX += 0.5f * deltaTime;
						}
						posCar1Y += deltaTime * 0.15f;
					}
					
					posCar1X -= deltaTime * 0.5f;
				}
				else {
					estado_car = "ACOMODA_CAR";
					auxPosCarx = posCar1X;
				}
			}
			else if (estado_car == "ACOMODA_CAR") {
				if (posCar1X > auxPosCarx - 15) {
					if (angulo_carX > 0.0f) {
						angulo_carX -= 0.5f * deltaTime;
					}
					if (posCar1Y < 14.0f) {
						posCar1Y += deltaTime * 0.15f;
					}
					posCar1X -= deltaTime * 0.5f;
				}
				else {
					estado_car = "CAR_LISTO";
				}
			}

			if (estado_car2 == "INICIO_CAR2") {
				float radio = 35.0f;
				float centroX = auxPosCar2x;
				float centroZ = auxPosCar2z - radio;

				if (angulo_car2Y < 90.0f) {
					posCar2X = centroX + (radio * cos((0 - angulo_car2Y) * toRadians));
					posCar2Z = centroZ + (radio * sin((0 - angulo_car2Y) * toRadians));
					angulo_car2Y += deltaTime * 0.9f;
				}
				else {
					estado_car2 = "AVANZA_CAR2";
				}
			}
			else if (estado_car2 == "AVANZA_CAR2") {
				if (posCar2X > -25.0f) {
					posCar2X -= deltaTime * 0.6;
				}
				else {
					estado_car2 = "EMPUJA_CAR2";
				}

			}
			else if (estado_car2 == "EMPUJA_CAR2") {
				if (posCar2X > -60.0f) {
					posCar2X -= deltaTime * 0.3;
				}
				else {
					estado_car2 = "GIRA_CAR2";
					auxPosCar2x = posCar2X;
					auxPosCar2z = posCar2Z;
				}


			}
			else if (estado_car2 == "GIRA_CAR2") {
				float radio = 70.0f;
				float centroX = auxPosCar2x;
				float centroZ = auxPosCar2z - radio;

				if (angulo_car2Y > 0.0f) {
					posCar2X = centroX + (radio * cos((180 - angulo_car2Y) * toRadians));
					posCar2Z = centroZ + (radio * sin((180 - angulo_car2Y) * toRadians));
					angulo_car2Y -= deltaTime * 0.25f;
				}
				else {
					estado_car2 = "AVANZA2_CAR2";
					auxPosCar2x = posCar2X;
					auxPosCar2z = posCar2Z;
				}
			}
			else if (estado_car2 == "AVANZA2_CAR2") {
				if (posCar2Z > auxPosCar2z - 90.0f) {
					posCar2Z -= deltaTime * 0.3;
				}
				else {
					estado_car2 = "ACOMODA_CAR2";
					auxPosCar2x = posCar2X;
					auxPosCar2z = posCar2Z;
				}


			}
			else if (estado_car2 == "ACOMODA_CAR2") {
				float radio = 25.0f;
				float centroX = auxPosCar2x - radio;
				float centroZ = auxPosCar2z;

				if (angulo_car2Y > -180.0f) {
					posCar2X = centroX + (radio * cos((0 - angulo_car2Y) * toRadians));
					posCar2Z = centroZ + (radio * sin((0 - angulo_car2Y) * toRadians));
					angulo_car2Y -= deltaTime * 0.5f;
				}
				else {
					estado_car2 = "CAR2_LISTO";
					auxPosCar2x = posCar2X;
					auxPosCar2z = posCar2Z;
				}
			}

			// EMPUJA AUTOBUS
			if (estado_car2 == "EMPUJA_CAR2" ||
				estado_car2 == "GIRA_CAR2" ||
				estado_car2 == "AVANZA2_CAR2") {

				float anguloCarEmpuja = -angulo_car2Y;
				float diffX = -15.5f;
				float diffZ = 0.0f;
				posEdi1X = posCar2X + ((diffZ * cos(anguloCarEmpuja* toRadians)) - (diffX * sin(anguloCarEmpuja* toRadians)));
				posEdi1Z = posCar2Z + ((diffZ * sin(anguloCarEmpuja* toRadians)) + (diffX * cos(anguloCarEmpuja* toRadians)));
				posEdi1Y = posCar2Y -1.0f;
				angulo_EdiY = -anguloCarEmpuja;
			}

		}
		else {
			//variables bus
			posBus1X = -140.0f;
			posBus1Y = 7.0f;
			posBus1Z = -90.0f;
			angulo_busY = 30.0f;
			angulo_busZ = -90;
			angulo_busX = 0.0f;
			estado_bus = "PARAR_BUS";

			//variables car
			angulo_carY = 0.0f;
			angulo_carX = 0.0f;
			posCar1X = -70.0f;
			posCar1Y = 3.0f;
			posCar1Z = -120.0f;
			estado_car = "VUELTA_CAR";
			auxPosCarx = posCar1X;
			auxPosCarz = posCar1Z;

			//variables car2
			angulo_car2Y = -90.0f;
			angulo_car2X = 0.0f;
			posCar2X = 0.0f;
			posCar2Y = 3.0f;
			posCar2Z = -80.0f;
			estado_car2 = "INICIO_CAR2";
			auxPosCar2x = posCar2X;
			auxPosCar2z = posCar2Z;

			//variables Edificio
			angulo_EdiY = 90.0f;
			angulo_EdiX = 0.0f;
			posEdi1X = -40.0f;
			posEdi1Y = 2.0f;
			posEdi1Z = -150.0f;
			estado_edificio = "PARAR_EDIFICIO";
		}
		

		posBus1 = glm::vec3(posBus1X, posBus1Y, posBus1Z);
		posCar = glm::vec3(posCar1X, posCar1Y, posCar1Z);
		posCar2 = glm::vec3(posCar2X, posCar2Y, posCar2Z);
		posEdificio = glm::vec3(posEdi1X, posEdi1Y, posEdi1Z);

		// ANIMACION PELOTA
		posPelota.y = posPelotaY + abs(15 * sin(rotPelotaX * toRadians));
		rotPelotaX += deltaTime * 5.0f;
		if (rotPelotaX > 360) rotPelotaX = 0;


		float radio = 90.0f;
		float centroX = posPelotaX - radio + 10.0f;
		float centroZ = posPelotaZ + 20;

		if (rotPelotaY < 360.0f) {
			rotPelotaY += deltaTime * 0.5f;
			posPelota.x = centroX + (radio * 1.5 * cos((0 - rotPelotaY) * toRadians));
			posPelota.z = centroZ + (radio * sin((0 - rotPelotaY) * toRadians));
		}
		else {
			rotPelotaY = 0.0f;
		}

//	ANIMACION LUCHADORES
		if (rotLuchador1 < 360.0f) rotLuchador1 += deltaTime * 2.5;
		else rotLuchador1 = 0.0f;

		//switch (estado_ML)
		//{
		//case 0:
		//	//la pulga avanza hasta 0 en Z (mientras camina)
		//	if (movZ_LP > 0) { 
		//		movZ_LP -= deltaTime * 2.0f;
		//		rotPiernasLP += deltaTime * avanzaOffset;
		//	}
		//	else if (movZ_LP <= 0 and rotLa_Pulga < 90) {
	
		//		rotLa_Pulga += deltaTime * avanzaOffset;
		//		rotPiernasLP += deltaTime * avanzaOffset;
		//	}//voltea 90° en y (mientras camina)
		//	else if (movZ_LP <= 0 and rotLa_Pulga >= 90) { 
		//		rotPiernasLP = 0.0f;
		//		estado_ML++;
		//	}
		//	//avanza hasta 0 (o 2) en X
		//	if (movZ_Rik > 1.5f) {
		//		movZ_Rik -= deltaTime * 2.0f;
		//		rotPiernasR += deltaTime * avanzaOffset;
		//	}

		//	if (movZ_BG < -1.5f) {
		//		movZ_BG += deltaTime * 2.0f;
		//		rotPiernasBG += deltaTime * avanzaOffset;
		//	}

		//	break;
		//case 1:
		//	//salto mortal (incrementa en Y, y en Z, mientras gira 270° en Z)
		//	if (rotY_La_Pulga < 270) {
		//		//movY_LP += deltaTime * avanzaOffset;
		//		rotY_La_Pulga += deltaTime * avanzaOffset * 2;
		//	}
		//	break;
		//case 2:
		//	break;
		//case 3:
		//	break;
		//case 4:
		//	break;
		//case 5:
		//	break;
		//default:
		//	break;
		//}

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera->calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();


		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera->getCameraPosition().x, camera->getCameraPosition().y, camera->getCameraPosition().z);

		// -----------------------
		// RENDERIZADO DE MODELOS
		// ------------------------
		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelaux_body(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Cuarto
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Cuarto_M.RenderModel();

		//CAMA
		//color = glm::vec3(0.705f, 0.705f, 0.105f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 1.0f, 90.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Cama_M.RenderModel();

		//leds
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-220.0f, 20.0f, 39.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-164.0f, 20.0f, 39.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-108.0f, 20.0f, 39.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-73.0f, 19.8f, 39.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-59.0f, 19.8f, 39.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-51.8f, 19.8f, 39.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-44.7f, 20.0f, 67.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-44.7f, 19.8f, 102.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-44.7f, 19.8f, 116.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-44.7f, 19.8f, 130.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		//Alfombra
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Alfombra_M.RenderModel();

		//Escritorio2
		//color = glm::vec3(0.705f, 0.705f, 0.105f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 1.0f, -330.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Escritorio2_M.RenderModel();

		//Escritorio3
		//color = glm::vec3(0.705f, 0.705f, 0.105f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, 1.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Escritorio3_M.RenderModel();

		//Escritorio
		//color = glm::vec3(0.705f, 0.705f, 0.105f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 1.0f, -317.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Escritorio_M.RenderModel();

		//tira de leds
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.0f, 64.0f, -384.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(74.0f, 64.0f, -384.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(39.0f, 64.2f, -384.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 64.2f, -384.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(11.0f, 64.2f, -384.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Leds_mini_M.RenderModel();

		//Lampara de escritorio
		//color = glm::vec3(0.705f, 0.705f, 0.705f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 52.0f, -50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lampara_M.RenderModel();

		//Bote de basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, -250.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Bote_basura_M.RenderModel();

		//Silla Gamer
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 0.0f, -270.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Silla_M.RenderModel();

		//Puff
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, 80.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puff_M.RenderModel();

		//SetUp
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 64.0f, -350.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SetUp_M.RenderModel();

		//Gabinete
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 64.0f, -350.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Gabinete_M.RenderModel();

		//HeadSet
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 64.0f, -350.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HeadSet_M.RenderModel();

		//Luz de techo 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 215.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LuzTecho_M.RenderModel();

		//Luz de techo 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 215.0f, -300.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LuzTecho_M.RenderModel();

		//MUEBLE
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-249.0f, 1.0f, -180.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mueble_M.RenderModel();

		//Rampa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-214.0f, 1.0f, -175.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rampa_M.RenderModel();

	  // TOY STORY

		//Casita
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 3.0f, -80.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casita_M.RenderModel();

		//Casita
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-249.0f, 64.0f, -170.0f) );
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casita_M.RenderModel();

		//Edificio
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-249.0f, 64.0f, -190.0f));
		model = glm::rotate(model, -120 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio_M.RenderModel();


		//Edificio Largo
		model = glm::mat4(1.0);
		model = glm::translate(model, posEdificio);
		model = glm::rotate(model, angulo_EdiY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulo_EdiX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio2_M.RenderModel();

		//Edificio Largo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 3.0f, -130.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio2_M.RenderModel();


		//Helicoptero
		model = glm::mat4(1.0);
		posblackhawk = glm::vec3(posXavion + movAvion_x, posYavion + movAvion_y, posZavion + movAvion_z);
		model = glm::translate(model, posblackhawk);
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, giroAvionX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, giroAvionY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Helicoptero_M.RenderModel();

		//Helice
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -15.0f, 0.0f));
		model = glm::rotate(model, rotYHelice * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helice_M.RenderModel();


		//Carro
		model = glm::mat4(1.0);
		model = glm::translate(model, posCar);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, angulo_carY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulo_carX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Car_M.RenderModel();

		//Carro
		model = glm::mat4(1.0);
		model = glm::translate(model, posCar2);

		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, angulo_car2Y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulo_car2X * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Car_M.RenderModel();

		//Bus
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 3.0f, -110.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bus_M.RenderModel();

		//Bus
		model = glm::mat4(1.0);
		model = glm::translate(model, posBus1);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, angulo_busY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, angulo_busZ * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, angulo_busX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bus_M.RenderModel();

		//Cubo Rubik
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-249.0f, 95.0f, -160.0f));
		model = glm::rotate(model, -10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CuboR_M.RenderModel();


		//PELOTA
		float auxRotPelotax = (rotPelotaX < 180) ? rotPelotaX : -rotPelotaX;
		color = glm::vec3(248.0f / 255.0f, 228.0f / 255.0f, 46.0f / 255.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, posPelota);
		model = glm::rotate(model, (auxRotPelotax)*toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (-90.0f + rotPelotaY) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		plainTexture.UseTexture();
		sp.render(); //esfera
			//franja azul
		color = glm::vec3(29.0f / 255.0f, 68.0f / 255.0f, 135.0f / 255.0f);
		model = modelaux;
		model = glm::scale(model, glm::vec3(1.04f, 1.04f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		plainTexture.UseTexture();
		sp.render(); //esfera
			//estrellas rojas
		color = glm::vec3(212.0f / 255.0f, 62.0f / 255.0f, 44.0f / 255.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.4f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		plainTexture.UseTexture();
		meshList[5]->RenderMesh();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		//  VALORANT ----------- VALORANT-------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 70.0f, -360.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_Gosth_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-91.0f, 80.0f, -337.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(SpectreMovX, SpectreMovY, SpectreMovZ));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, SpectreRotX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, SpectreRotY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_Spectre_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, 70.0f, -360.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_Banca_Madera.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, 70.0f, -310.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_Balde_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, 70.0f, -315.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_Malla_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 70.0f, -300.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LamparaVal_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 70.0f, -305.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_CajaMadera_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 70.0f, -360.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_CajaMadera2_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 70.0f, -300.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_CajaMadera2_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 100.0f, 100.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[6]->RenderMesh();

		//////////////////////////////// F E N I X ///////////////////////////////
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 70.0f, -340.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, FenixRot * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_FenixC.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.35f, 1.6f, 0.0f));
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, FenixBIrotX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_FenixBD.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.35f, 1.6f, 0.0f));
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_FenixBI.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.125f, 0.8f, 0.0f));
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_FenixPI.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.125f, 0.8f, 0.0f));
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_FenixPD.RenderModel();


		//////////////////////////////// K I L L  J O Y ///////////////////////////////
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-220.0f, 82.0f, -340.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, KillJMovZ));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, KillJRotY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, KillJRotX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_KillJC.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.35f, 0.2f, 0.0f));
		model = glm::rotate(model, KillJBrazosRotX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_KillJBD.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.35f, 0.2f, 0.0f));
		model = glm::rotate(model, KillJBrazosRotX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_KillJBI.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.125f, -0.5f, 0.0f));
		model = glm::rotate(model, -KillJPIrotX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_KillJPI.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.125f, -0.5f, 0.0f));
		model = glm::rotate(model, -KillJPDrotX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Valorant_KillJPD.RenderModel();

	//  VALORANT ----------- VALORANT
		glm::mat4 auxSpike(1.0);

		//spike
		model = glm::mat4(1.0);
		model = glm::translate(model, posSpike);
		auxSpike = model;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Spike_base_M.RenderModel();

		model = auxSpike;
		model = glm::rotate(model, giroSpike * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Spike_cilindro_M.RenderModel();

		model = auxSpike;
		model = glm::translate(model, glm::vec3(0.0f, movAroSpike, 0.0f));
		model = glm::rotate(model, -giroSpike/5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Spike_aro_M.RenderModel();

		//HELICOPTERO BRYAN PARADA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 70.0f, -290.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helipuerto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f + keyframe_Bryan.mov_x_p, 75.0f + keyframe_Bryan.mov_y_p, -290.0f + keyframe_Bryan.mov_z_p));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, keyframe_Bryan.giroX_p * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, keyframe_Bryan.giroY_p * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, keyframe_Bryan.giroZ_p * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helicoptero_Bryan.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
		model = glm::rotate(model, rotYHelice * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helice_Bryan.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.9f, 0.0f, 0.1f));
		model = glm::rotate(model, rotYHelice * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rotor_Bryan.RenderModel();

//	M U C H A  L U C H A

		glm::mat4 auxML(1.0);

		//ring
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 42.75f, 40.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		auxML = model;
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ML_Ring_M.RenderModel();

		//ring 2
		model = auxML;
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ML_Ring_M.RenderModel();
		
		//Luchador 1
		model = auxML;
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, -20.0f));
		model = glm::rotate(model, 150 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		//model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StreetMan1_Texture.UseTexture();
		Luchador_M.RenderModel();

		//Luchador 2
		model = auxML;
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 20.0f));
		model = glm::rotate(model, -30 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StreetMan2_Texture.UseTexture();
		Luchador_M.RenderModel();

		//Luchador 3
		model = auxML;
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 20.0f));
		model = glm::rotate(model, 210 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StreetMan3_Texture.UseTexture();
		Luchador_M.RenderModel();

		//Luchador 4 (animado)
		model = auxML;
		model = glm::translate(model, glm::vec3(45.0f + 2 * sin(rotLuchador1 * toRadians), 1.25f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//animacion
		model = glm::translate(model, glm::vec3(cos(rotLuchador1*toRadians), sin(rotLuchador1 * toRadians), 0.0f));
		model = glm::rotate(model, 1.5f * sin(rotLuchador1 * toRadians), glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, cos(rotLuchador1 * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StreetMan2_Texture.UseTexture();
		Luchador_M.RenderModel();

		//Luchador 5 (animado)
		model = auxML;
		model = glm::translate(model, glm::vec3(55.0f - 2 * sin(rotLuchador1 * toRadians), 1.25f, 0.0f));
		model = glm::rotate(model, - 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//animacion
		model = glm::translate(model, glm::vec3(-cos(rotLuchador1*toRadians), sin(rotLuchador1*toRadians), 0.0f));
		model = glm::rotate(model, 1.5f *cos(rotLuchador1 * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, cos(rotLuchador1 * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StreetMan3_Texture.UseTexture();
		Luchador_M.RenderModel();

	//	Rikochet
		glm::mat4 auxPersonaje(1.0);

		//Torso (utiliza torso 2)
		model = auxML;
		//model = glm::translate(model, glm::vec3(5.0f,4.0f,-5.0f));
		model = glm::translate(model, glm::vec3(movX_Rik, movY_Rik, movZ_Rik));
		//model = glm::rotate(model, -angulo_cam, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, rotRikochet * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		auxPersonaje = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ricochet_Texture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//Cabeza
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.0f, 0.625f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ricochet_Texture.UseTexture();
		meshList[0]->RenderMesh();

		//Brazo izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(-tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotPiernasR * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasR * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ricochet_Texture.UseTexture();
		meshList[2]->RenderMesh();

		//Brazo der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotPiernasR * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasR * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ricochet_Texture.UseTexture();
		meshList[2]->RenderMesh();

		//Pierna izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotPiernasR * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasR * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ricochet_Texture.UseTexture();
		meshList[3]->RenderMesh();

		//Pierna der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotPiernasR * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasR * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ricochet_Texture.UseTexture();
		meshList[3]->RenderMesh();

	//	La Pulga

		//Torso (utiliza torso 2)
		model = auxML;
		//model = glm::translate(model, glm::vec3(-5.0f, 4.0f, -5.0f));
		if (estado_ML == 1) model = glm::translate(model, glm::vec3(movX_LP + sin(rotY_La_Pulga * toRadians), movY_LP + cos(rotY_La_Pulga * toRadians), movZ_LP));
		else model = glm::translate(model, glm::vec3(movX_LP,movY_LP,movZ_LP));
		//model = glm::rotate(model, -angulo_cam, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, rotLa_Pulga * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotY_La_Pulga * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		auxPersonaje = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		La_Pulga_Texture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//Cabeza
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.0f, 0.625f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		La_Pulga_Texture.UseTexture();
		meshList[0]->RenderMesh();

		//Brazo izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(-tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotPiernasLP * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasLP * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		La_Pulga_Texture.UseTexture();
		meshList[2]->RenderMesh();

		//Brazo der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotPiernasLP * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasLP * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		La_Pulga_Texture.UseTexture();
		meshList[2]->RenderMesh();

		//Pierna izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotPiernasLP * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasLP * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		La_Pulga_Texture.UseTexture();
		meshList[3]->RenderMesh();

		//Pierna der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotPiernasLP * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasLP * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		La_Pulga_Texture.UseTexture();
		meshList[3]->RenderMesh();

	//	Buena Girl

			//Torso (utiliza torso 2)
		model = auxML;
		//model = glm::translate(model, glm::vec3(5.0f, 4.0f, 5.0f));
		model = glm::translate(model, glm::vec3(movX_BG,movY_BG,movZ_BG));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, rotBuena_Girl * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		auxPersonaje = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Buena_Girl_Texture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//Cabeza
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.0f, 0.625f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Buena_Girl_Texture.UseTexture();
		meshList[0]->RenderMesh();

		//Brazo izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(-tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotPiernasBG * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasBG * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Buena_Girl_Texture.UseTexture();
		meshList[2]->RenderMesh();

		//Brazo der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotPiernasBG * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasBG * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Buena_Girl_Texture.UseTexture();
		meshList[2]->RenderMesh();

		//Pierna izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotPiernasBG * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasBG * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Buena_Girl_Texture.UseTexture();
		meshList[3]->RenderMesh();

		//Pierna der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotPiernasBG * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotPiernasBG * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Buena_Girl_Texture.UseTexture();
		meshList[3]->RenderMesh();



//	Personaje Frijolito
		//glm::mat4 auxPersonaje(1.0);
 
		//Torso
		model = glm::mat4(1.0);
		model = glm::translate(model, posFrijolito);
		model = glm::rotate(model, -angulo_cam_frijolito, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		//para animación
		model = glm::rotate(model, rotDireccion[2] * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		auxPersonaje = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoTexture.UseTexture();
		meshList[1]->RenderMesh();

		//Cabeza
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.0f, 0.375f, 0.0f));
		//model = glm::rotate(model, 20 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.25f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoTexture.UseTexture();
		meshList[0]->RenderMesh();

		//Brazo izq
		model = glm::mat4(1.0);
		model = auxPersonaje;

		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotBrazo[2] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[2] * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));

		//se traslada lo necesario para el hombro
		model = glm::translate(model, glm::vec3(-0.25f, 0.0f, 0.0f));
		//se desplaza la distancia equivalente al cateto opuesto (distancia inferior) al realizar la rotación
		model = glm::translate(model, glm::vec3(-tan(10*toRadians)*0.375f, 0.0f, 0.0f));
		//se realiza la rotación
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		//se desplaza lo necesario para llegar al centro del objeto (la mitad de su ancho)
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Brazo der
		model = auxPersonaje;
		//para animaciones
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotBrazo[2] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[2] * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		//posicionamiento normal
		model = glm::translate(model, glm::vec3(0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Pierna izq
		model = auxPersonaje;
		//posición
		model = glm::translate(model, glm::vec3(-0.125f, -0.75f, 0.0f));
		//para animaciones
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotBrazo[2] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[2] * toRadians)/2, glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoTexture.UseTexture();
		meshList[3]->RenderMesh();

		//Pierna der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.125f, -0.75f, 0.0f));		
		//para animaciones
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotBrazo[2] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[2] * toRadians)/2, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FrijolitoTexture.UseTexture();
		meshList[3]->RenderMesh();

//	Personaje Jett
		
		//Torso (utiliza torso 2)
		model = glm::mat4(1.0);
		model = glm::translate(model, posJett);
		model = glm::rotate(model, -angulo_cam_jett, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, rotDireccion[1] * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		auxPersonaje = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JettTexture.UseTexture();
		meshList[4]->RenderMesh();

		//Cabeza
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.0f, 0.625f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JettTexture.UseTexture();
		meshList[0]->RenderMesh();

		//Brazo izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(-tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotBrazo[1] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[1] * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JettTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Brazo der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotBrazo[1] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[1] * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JettTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Pierna izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotBrazo[1] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[1] * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JettTexture.UseTexture();
		meshList[3]->RenderMesh();

		//Pierna der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotBrazo[1] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[1] * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JettTexture.UseTexture();
		meshList[3]->RenderMesh();


		//informaci�n al shader de fuentes de iluminaci�n
		//informaci�n al shader de fuentes de iluminaci�n

//	Personaje Wheezy

		//Torso (utiliza torso 2)
		model = glm::mat4(1.0);
		model = glm::translate(model, poswheezy);
		model = glm::rotate(model, -angulo_cam, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, rotDireccion[0] * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		auxPersonaje = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//Cabeza
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.0f, 0.625f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		meshList[0]->RenderMesh();

		//Brazo izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(-tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotBrazo[0] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[0] * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Brazo der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.25f, 0.0, 0.0f));
		model = glm::translate(model, glm::vec3(tan(10 * toRadians) * 0.375f, 0.0f, 0.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotBrazo[0] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[0] * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Pierna izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotBrazo[0] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[0] * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		meshList[3]->RenderMesh();

		//Pierna der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotBrazo[0] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[0] * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		meshList[3]->RenderMesh();

		//	Modelo helicoptero blanco (Pieter)
		glm::mat4 auxHelicopterW(1.0);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, -200.0f));
		auxHelicopterW = model;
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helipad_M.RenderModel();

		model = auxHelicopterW;
		model = glm::translate(model, glm::vec3(0.0f + keyframe_Piet.mov_x_p, 2.5f + keyframe_Piet.mov_y_p, 2.0f + keyframe_Piet.mov_z_p));
		model = glm::rotate(model, keyframe_Piet.giroX_p * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, keyframe_Piet.giroY_p * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, keyframe_Piet.giroZ_p * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		auxHelicopterW = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		White_Helicopter_M.RenderModel();

		model = auxHelicopterW;
		model = glm::translate(model, glm::vec3(0.0f, 3.25f, -0.5f));
		model = glm::rotate(model, rotYHelice * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		White_Helicopter_Helice_M.RenderModel();

		model = auxHelicopterW;
		model = glm::translate(model, glm::vec3(0.0f, 1.8f, -8.15f));
		model = glm::rotate(model, rotYHelice * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		White_Helicopter_Rotor_M.RenderModel();

		

		//informaci�n al shader de fuentes de iluminaci�n
		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		LedCama = mainWindow.getLedCama();
		LampVal = mainWindow.getLampVal();
		if (contadorDiaNoche <= 0.7f) {
			//printf("\nLedCama = %d", LedCama);
			if (LedCama == 1 and !spikeSube)
				shaderList[0].SetPointLights(pointLightsCama, pointLightCount1);
			else if (LedCama == 1 and spikeSube) {
				//CONDICIONALES PARA EL PARPADEO
				if (movAroSpike <= 6.0f and parpadeoSpike <= 5.0f and banderaParpadeoSpike == 0) { //Parpadeo Encendido, luz en azul
					pointLightsSpike[2].setRGB(0.0f, 0.5f, 0.1f);
					shaderList[0].SetPointLights(pointLightsSpike, pointLightCount2);
					parpadeoSpike += deltaTime * 0.1f;
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike >= 5.0f and banderaParpadeoSpike == 0) {//Parpadeo apagado, luz en 0
					banderaParpadeoSpike = 1;
					pointLightsSpike[2].setRGB(0.0f, 0.0f, 0.0f);
					shaderList[0].SetPointLights(pointLightsSpike, pointLightCount2);
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike >= 0.0f and banderaParpadeoSpike == 1) {//Parpadeo apagado, luz en 0
					shaderList[0].SetPointLights(pointLightsSpike, pointLightCount2);
					parpadeoSpike -= deltaTime * 0.1f;
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike <= 0.0f and banderaParpadeoSpike == 1) {//Parpadeo Encendido, luz en azul
					banderaParpadeoSpike = 0;
					pointLightsSpike[2].setRGB(0.0f, 0.5f, 1.0f);
					shaderList[0].SetPointLights(pointLightsSpike, pointLightCount2);
				}
			}
			else if (LedCama == 0 and spikeSube) {
				//CONDICIONALES PARA EL PARPADEO
				if (movAroSpike <= 6.0f and parpadeoSpike <= 5.0f and banderaParpadeoSpike == 0) { //Parpadeo Encendido, luz en azul
					pointLightsSpike1[0].setRGB(0.0f, 0.5f, 0.1f);
					shaderList[0].SetPointLights(pointLightsSpike1, pointLightCount3);
					parpadeoSpike += deltaTime * 0.1f;
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike >= 5.0f and banderaParpadeoSpike == 0) {//Parpadeo apagado, luz en 0
					banderaParpadeoSpike = 1;
					pointLightsSpike1[0].setRGB(0.0f, 0.0f, 0.0f);
					shaderList[0].SetPointLights(pointLightsSpike1, pointLightCount3);
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike >= 0.0f and banderaParpadeoSpike == 1) {//Parpadeo apagado, luz en 0
					shaderList[0].SetPointLights(pointLightsSpike1, pointLightCount3);
					parpadeoSpike -= deltaTime * 0.1f;
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike <= 0.0f and banderaParpadeoSpike == 1) {//Parpadeo Encendido, luz en azul
					banderaParpadeoSpike = 0;
					pointLightsSpike1[0].setRGB(0.0f, 0.5f, 1.0f);
					shaderList[0].SetPointLights(pointLightsSpike1, pointLightCount3);
				}
			}
			else if (LedCama == 0 and !spikeSube)
				shaderList[0].SetPointLights(pointLightsNoche, pointLightCount);

			if (mainWindow.getDeskLamp() == 1 and mainWindow.getLampVal() == 0) {
				shaderList[0].SetSpotLights(spotLights, spotLightCount);
			}
			else if (mainWindow.getDeskLamp() == 0 and mainWindow.getLampVal() == 0) {
				shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
			}
			else if (mainWindow.getDeskLamp() == 0 and mainWindow.getLampVal() == 1) {
				shaderList[0].SetSpotLights(spotlights1, spotLightCount1 - 1);
			}
			else if (mainWindow.getDeskLamp() == 1 and mainWindow.getLampVal() == 1) {
				shaderList[0].SetSpotLights(spotlights1, spotLightCount1);
			}
		}
		else {
			if (LedCama == 1 and !spikeSube)
				shaderList[0].SetPointLights(pointLightsCama, pointLightCount1 - 2);
			else if (LedCama == 1 and spikeSube) {
				//CONDICIONALES PARA EL PARPADEO
				if (movAroSpike <= 6.0f and parpadeoSpike <= 5.0f and banderaParpadeoSpike == 0) { //Parpadeo Encendido, luz en azul
					pointLightsSpike[2].setRGB(0.0f, 0.5f, 0.1f);
					shaderList[0].SetPointLights(pointLightsSpike, pointLightCount2 - 2);
					parpadeoSpike += deltaTime * 0.1f;
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike >= 5.0f and banderaParpadeoSpike == 0) {//Parpadeo apagado, luz en 0
					banderaParpadeoSpike = 1;
					pointLightsSpike[2].setRGB(0.0f, 0.0f, 0.0f);
					shaderList[0].SetPointLights(pointLightsSpike, pointLightCount2 - 2);
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike >= 0.0f and banderaParpadeoSpike == 1) {//Parpadeo apagado, luz en 0
					shaderList[0].SetPointLights(pointLightsSpike, pointLightCount2 - 2);
					parpadeoSpike -= deltaTime * 0.1f;
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike <= 0.0f and banderaParpadeoSpike == 1) {//Parpadeo Encendido, luz en azul
					banderaParpadeoSpike = 0;
					pointLightsSpike[2].setRGB(0.0f, 0.5f, 1.0f);
					shaderList[0].SetPointLights(pointLightsSpike, pointLightCount2 - 2);
				}
			}
			else if (LedCama == 0 and spikeSube) {
				//CONDICIONALES PARA EL PARPADEO
				if (movAroSpike <= 6.0f and parpadeoSpike <= 5.0f and banderaParpadeoSpike == 0) { //Parpadeo Encendido, luz en azul
					pointLightsSpike1[0].setRGB(0.0f, 0.5f, 0.1f);
					shaderList[0].SetPointLights(pointLightsSpike1, pointLightCount3 - 2);
					parpadeoSpike += deltaTime * 0.1f;
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike >= 5.0f and banderaParpadeoSpike == 0) {//Parpadeo apagado, luz en 0
					banderaParpadeoSpike = 1;
					pointLightsSpike1[0].setRGB(0.0f, 0.0f, 0.0f);
					shaderList[0].SetPointLights(pointLightsSpike1, pointLightCount3 - 2);
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike >= 0.0f and banderaParpadeoSpike == 1) {//Parpadeo apagado, luz en 0
					shaderList[0].SetPointLights(pointLightsSpike1, pointLightCount3 - 2);
					parpadeoSpike -= deltaTime * 0.1f;
				}
				else if (movAroSpike <= 6.0f and parpadeoSpike <= 0.0f and banderaParpadeoSpike == 1) {//Parpadeo Encendido, luz en azul
					banderaParpadeoSpike = 0;
					pointLightsSpike1[0].setRGB(0.0f, 0.5f, 1.0f);
					shaderList[0].SetPointLights(pointLightsSpike1, pointLightCount3 - 2);
				}
			}
			else if (LedCama == 0 and !spikeSube) {
				shaderList[0].SetPointLights(pointLightsNoche, pointLightCount - 2);
			}


			if (mainWindow.getDeskLamp() == 1 and mainWindow.getLampVal() == 0) {
				shaderList[0].SetSpotLights(spotLights, spotLightCount);
			}
			else if (mainWindow.getDeskLamp() == 0 and mainWindow.getLampVal() == 0) {
				shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
			}
			else if (mainWindow.getDeskLamp() == 0 and mainWindow.getLampVal() == 1) {
				shaderList[0].SetSpotLights(spotlights1, spotLightCount1 - 1);
			}
			else if (mainWindow.getDeskLamp() == 1 and mainWindow.getLampVal() == 1) {
				shaderList[0].SetSpotLights(spotlights1, spotLightCount1);
			}
		}
		

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	
	ambiental->drop();
	return 0;
}



void inputKeyframes(bool* keys, int action)
{
	if (keys[GLFW_KEY_SPACE] && action == GLFW_PRESS) // Empezar animacion
	{
		//if (reproduciranimacion < 1)
		//{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				//reproduciranimacion++;
				//printf("presiona 0 para habilitar reproducir de nuevo la animaci�n'\n");
				//habilitaranimacion = 0;

			}
			else
			{
				play = false;
			}
		//}
	}
	/*if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
	}*/

	if (keys[GLFW_KEY_L] && action == GLFW_PRESS) //Guardar
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("\n--------- SE GUARDA -----------\n");
			printf("movAvion_x es: %f\n", movAvion_x);
			printf("movAvion_y es: %f\n", movAvion_y);
			printf("movAvion_z es: %f\n", movAvion_z);
			printf("giroAvionY es: %f\n", giroAvionY);
			printf("giroAvionX es: %f\n", giroAvionX);
			printf("presiona R para habilitar guardar otro frame'\n");
			printf("\n-----------------------------\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_R])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
		}
	}

	if (keys[GLFW_KEY_UP] && action == GLFW_PRESS) // DECREMENTA X
	{
		//if (ciclo_x < 1)
		//{
			movAvion_x -= 1.0f;
			printf("movAvion_x es: %f\n", movAvion_x);
			//ciclo_x++;
			//ciclo_x2 = 0;
			//printf("reinicia con C\n");
		//}

	}
	/*if (keys[GLFW_KEY_V] )
	{
		if (ciclo_x2 < 1)
		{
			ciclo_x = 0;
		}
	}*/
	if (keys[GLFW_KEY_DOWN] && action == GLFW_PRESS) // INCREMENTA X
	{
		//if (ciclo < 1)
		//{
			movAvion_x += 1.0f;
			printf("movAvion_x es: %f\n", movAvion_x);
			//ciclo++;
			//ciclo2 = 0;
			//printf("reinicia con 2\n");
		//}

	}
	/*if (keys[GLFW_KEY_B] )
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}*/
	if (keys[GLFW_KEY_RIGHT] && action == GLFW_PRESS) // DECREMENTA Z
	{
		movAvion_z -= 1.0f;
		printf("movAvion_z es: %f\n", movAvion_z);
		//ciclo_x++;
		//ciclo_x2 = 0;
		//printf("reinicia con C\n");

	}
	/*if (keys[GLFW_KEY_V] )
	{
		if (ciclo_x2 < 1)
		{
			ciclo_x = 0;
		}
	}*/
	if (keys[GLFW_KEY_LEFT] && action == GLFW_PRESS) // INCREMENTA Z
	{
		//if (ciclo < 1)
		//{
		movAvion_z += 1.0f;
		printf("movAvion_x es: %f\n", movAvion_z);
		//ciclo++;
		//ciclo2 = 0;
		//printf("reinicia con 2\n");
		//}

	}
	/*if (keys[GLFW_KEY_B] )
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}*/
	if (keys[GLFW_KEY_K] && action == GLFW_PRESS) // INCREMENTA Y
	{
		//if (ciclo_d < 1)
		//{
			movAvion_y += 1.0f;
			printf("movAvion_y es: %f\n", movAvion_y);
			//ciclo_d++;
			//ciclo_d2 = 0;
			//printf("reinicia con 4\n");
		//}

	}
	/*if (keys[GLFW_KEY_N] )
	{
		if (ciclo_d2 < 1)
		{
			ciclo_d = 0;
		}
	}*/
	if (keys[GLFW_KEY_M] && action == GLFW_PRESS) // DECREMENTA Y
	{
		//if (ciclo_y < 1)
		//{
			movAvion_y -= 1.0f;
			printf("giroAvionY es: %f\n", giroAvionY);
			//ciclo_y++;
			//ciclo_y2 = 0;
			//printf("reinicia con 6\n");
		//}

	}
	/*if (keys[GLFW_KEY_6])
	{
		if (ciclo_y2 < 1)
		{
			ciclo_y = 0;
		}
	}*/
	if (keys[GLFW_KEY_1] && action == GLFW_PRESS) // INCREMENTA ROTY
	{
		//if (ciclo_g < 1)
		//{
			giroAvionY += 1.0f;
			printf("giroAvionY es: %f\n", giroAvionY);
			//ciclo_g++;
			//ciclo_g2 = 0;
			//printf("reinicia con 8\n");
		//}

	}
	if (keys[GLFW_KEY_2] && action == GLFW_PRESS) // DECREMENTA ROTY
	{
		//if (ciclo_g < 1)
		//{
		giroAvionY -= 1.0f;
		printf("giroAvionY es: %f\n", giroAvionY);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
	if (keys[GLFW_KEY_3] && action == GLFW_PRESS) // INCREMENTA ROTX
	{
		//if (ciclo_g < 1)
		//{
		giroAvionX += 1.0f;
		printf("giroAvionX es: %f\n", giroAvionX);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
	if (keys[GLFW_KEY_4] && action == GLFW_PRESS) // DECREMENTA ROTX
	{
		//if (ciclo_g < 1)
		//{
		giroAvionX -= 1.0f;
		printf("giroAvionX es: %f\n", giroAvionX);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
}


#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>


typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float mov_x = 0.0f;		//Variable para PosicionX
	float mov_y = 0.0f;		//Variable para PosicionY
	float mov_z = 0.0f;		//Variable para PosicionZ

	float mov_xInc = 0.0f;		//Variable para IncrementoX
	float mov_yInc = 0.0f;		//Variable para IncrementoY
	float mov_zInc = 0.0f;		//Variable para IncrementoZ

	float giroY = 0.0f;
	float giroYInc = 0.0f;
	float giroX = 0.0f;
	float giroXInc = 0.0f;
	float giroZ = 0.0f;
	float giroZInc = 0.0f;
}FRAME;

class KeyFrames
{
public:
	FRAME arreglo[100];
	float mov_x_p = 0.0f;		//Variable para PosicionX
	float mov_y_p = 0.0f;		//Variable para PosicionY
	float mov_z_p = 0.0f;		//Variable para PosicionZ
	float giroY_p = 0.0f;
	float giroX_p = 0.0f;
	float giroZ_p = 0.0f;
	KeyFrames();
	KeyFrames(int max_steps, int curr_steps, int FrameIndex, int play, int playIndex);
	void saveFrame(void);
	void resetElements(void);
	void interpolation(void);
	void animate(void);
	void inputKeyframes(bool* keys, int action);
	void iniciaAutomatico(void);

private:
	bool animacion = false;
	int i_max_steps = 50;
	int i_curr_steps = 36; //frames ya iniciados 
	int FrameIndex = 36;			//introducir datos
	bool play = false;  //var animacion para iniciar por teclado
	int playIndex = 0;
	float guardoFrame;
	float reinicioFrame;


};


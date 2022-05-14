#include "KeyFrames.h"

KeyFrames::KeyFrames(){
	i_max_steps = 50;
	i_curr_steps = 36; //frames ya iniciados 
	FrameIndex = 36;			//introducir datos
	play = false;  //var animacion para iniciar por teclado
	playIndex = 0;
}

KeyFrames::KeyFrames(int max_steps, int curr_steps, int FrameIndex, int play, int playIndex) {
	i_max_steps = max_steps;
	i_curr_steps = curr_steps; //frames ya iniciados 
	this->FrameIndex = FrameIndex;			//introducir datos
	this->play = play;  //var animacion para iniciar por teclado
	this->playIndex = playIndex;
}

void KeyFrames::saveFrame(void) {

	printf("Se guard� el frame[ %d ]\n", FrameIndex);

	arreglo[FrameIndex].mov_x = mov_x_p;
	arreglo[FrameIndex].mov_y = mov_y_p;
	arreglo[FrameIndex].mov_z = mov_z_p;
	arreglo[FrameIndex].giroY = giroY_p;
	arreglo[FrameIndex].giroX = giroX_p;
	arreglo[FrameIndex].giroZ = giroZ_p;
	
	FrameIndex++;
}
void KeyFrames::resetElements(void) {
	mov_x_p = arreglo[0].mov_x;
	mov_y_p = arreglo[0].mov_y;
	mov_z_p = arreglo[0].mov_z;
	giroY_p = arreglo[0].giroY;
	giroX_p = arreglo[0].giroX;
}
void KeyFrames::interpolation(void) {
	arreglo[playIndex].mov_xInc = (arreglo[playIndex + 1].mov_x - arreglo[playIndex].mov_x) / i_max_steps;
	arreglo[playIndex].mov_yInc = (arreglo[playIndex + 1].mov_y - arreglo[playIndex].mov_y) / i_max_steps;
	arreglo[playIndex].mov_zInc = (arreglo[playIndex + 1].mov_z - arreglo[playIndex].mov_z) / i_max_steps;
	arreglo[playIndex].giroYInc = (arreglo[playIndex + 1].giroY - arreglo[playIndex].giroY) / i_max_steps;
	arreglo[playIndex].giroXInc = (arreglo[playIndex + 1].giroX - arreglo[playIndex].giroX) / i_max_steps;

}
void KeyFrames::animate(void) {
	//Movimiento del objeto
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			printf("frame reproducido playindex : %d\n", playIndex - 1);
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("ultimo Frame index= %d\n", FrameIndex - 1);
				printf("termina animacion\n");
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
			mov_x_p += arreglo[playIndex].mov_xInc;
			mov_y_p += arreglo[playIndex].mov_yInc;
			mov_z_p += arreglo[playIndex].mov_zInc;
			giroY_p += arreglo[playIndex].giroYInc;
			giroX_p += arreglo[playIndex].giroXInc;
			i_curr_steps++;
		}

	}
}

void KeyFrames::inputKeyframes(bool* keys, int action)
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
			printf("mov_x es: %f\n", mov_x_p);
			printf("mov_y_p es: %f\n", mov_y_p);
			printf("mov_z_p es: %f\n", mov_z_p);
			printf("giroX_p es: %f\n", giroX_p);
			printf("giroY es: %f\n", giroY_p);
			printf("giroZ_p es: %f\n", giroZ_p);
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
		mov_x_p -= 0.25f;
		//printf("mov_x_p es: %f\n", mov_x_p);
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
		mov_x_p += 0.25f;
		//printf("mov_x_p es: %f\n", mov_x_p);
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
		mov_z_p -= 0.25f;
		//printf("mov_z_p es: %f\n", mov_z_p);
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
		mov_z_p += 0.25f;
		//printf("mov_x_p es: %f\n", mov_z_p);
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
		mov_y_p += 0.25f;
		//printf("mov_y_p es: %f\n", mov_y_p);
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
		mov_y_p -= 0.25f;
		//printf("giroY_p es: %f\n", giroY_p);
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
		giroY_p += 0.25f;
		//printf("giroY_p es: %f\n", giroY_p);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
	if (keys[GLFW_KEY_2] && action == GLFW_PRESS) // DECREMENTA ROTY
	{
		//if (ciclo_g < 1)
		//{
		giroY_p -= 0.25f;
		//printf("giroY_p es: %f\n", giroY_p);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
	if (keys[GLFW_KEY_3] && action == GLFW_PRESS) // INCREMENTA ROTX
	{
		//if (ciclo_g < 1)
		//{
		giroX_p += 0.25f;
		//printf("giroX_p es: %f\n", giroX_p);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
	if (keys[GLFW_KEY_4] && action == GLFW_PRESS) // DECREMENTA ROTX
	{
		//if (ciclo_g < 1)
		//{
		giroX_p -= 0.25f;
		//printf("giroX_p es: %f\n", giroX_p);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
	if (keys[GLFW_KEY_5] && action == GLFW_PRESS) // INCREMENTA ROTZ
	{
		//if (ciclo_g < 1)
		//{
		giroZ_p += 0.25f;
		//printf("giroZ_p es: %f\n", giroZ_p);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
	if (keys[GLFW_KEY_6] && action == GLFW_PRESS) // DECREMENTA ROTZ
	{
		//if (ciclo_g < 1)
		//{
		giroZ_p -= 0.25f;
		//printf("giroZ_p es: %f\n", giroZ_p);
		//ciclo_g++;
		//ciclo_g2 = 0;
		//printf("reinicia con 8\n");
	//}

	}
}
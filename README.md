# EresUnJuguete (You Are a Toy!)
- The videogame prototype project is a virtual world designed as a boy's room filled with toys and inspired by the iconic movie Toy Story. 
- The virtual landscape is made using voxel art, and the toys and avatars have a blocky appearance to follow the same design style. 
- The movement in the game follows the standard PC layout of WASD and mouse movement, and the world has four different cameras that can be switched using the C key. 
- The virtual world has different types of lights, including day and night cycle lights, ceiling lights, desk lamps, LED lights, and spike lights. 
- The world consists of seven animations, including Valorant-themed animations and a lot of fighting animations. 
- The game has background music playing at all times, which is the instrumental for the movie Toy Story. There is also another implementation of audio within the game, which is activated when the Jett character approaches the spike.

#### Techincal Manual
---
## **Universidad Nacional Autónoma de México**

### **Facultad de Ingeniería**

#### **Computación gráfica e interacción humano computadora**

<p style="text-align: right">
<strong>Student Names:</strong></p>


<p style="text-align: right">
<strong> </strong></p>


<p style="text-align: right">
<strong>Martinez Vazquez Brayan Alexis</strong></p>


<p style="text-align: right">
<strong>Parada Pérez Jesús Bryan</strong></p>


<p style="text-align: right">
<strong>van der Werff Vargas Pieter Alexander</strong></p>


<p style="text-align: right">
<strong>Account Numbers: 316117436</strong></p>


<p style="text-align: right">
<strong>316044956</strong></p>


<p style="text-align: right">
<strong>316246435</strong></p>


<p style="text-align: right">
<strong>Group number: 03</strong></p>


<p style="text-align: right">
<strong> </strong></p>


<p style="text-align: right">
<strong>Technical Manual</strong></p>


<p style="text-align: right">
<strong>Semester 2022-2</strong></p>


<p style="text-align: right">
<strong>Deadline Date: 25/05/2022</strong></p>


<p style="text-align: right">
</p>


## **Index**

[ Geometry. ](#geometry)

[ Skybox. ](#skybox)

[ Avatar. ](#avatar)

[ Route. ](#route) 

[ Lighting. ](#lighting)

[ Animation. ](#animation) 

[ Audio. ](#audio)


<a name="geomtry"></a>
## **Geometry**

For our main room environment we imported the models of the main furniture, some of which are:



* Bed
* Puff
* 2 Desks
* 1 Table
* 1 Chair
* Cubbeard
* Rug

These models were imported and textured using external software such as Blender, in order to give a more blocky aesthetic and follow the voxel art model. The other purpose of having the furniture is to make the scenery more recognizable and feel like a child’s room.

<a href="https://drive.google.com/uc?export=view&id=1yCLy5-vYVNm0fYAhiHbsj-wni8_JM383"><img src="https://drive.google.com/uc?export=view&id=1yCLy5-vYVNm0fYAhiHbsj-wni8_JM383" style="max-width: 100%; height: auto" title="Click to enlarge picture" />
1. Room overhead perspective


```
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
Model Helicoptero_M = Model();
Model Helice_M = Model();
```



```
      //Modelos para el proyecto
	Cuarto_M.LoadModel("Models/cuarto_text.obj");
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
	Helicoptero_M.LoadModel("Models/helicoptero.obj");
	Helice_M.LoadModel("Models/helice.obj");
```



```
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

		//Alfombra
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Alfombra_M.RenderModel();
```


To make our main character models we used primitives created in OpenGL, as well as added textures by each vertex.


```
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
```


2. Character model code


```

```



<a href="https://drive.google.com/uc?export=view&id=1lirY-bIDmpFgrYLuRyGt91OdULlHq3uT"><img src="https://drive.google.com/uc?export=view&id=1lirY-bIDmpFgrYLuRyGt91OdULlHq3uT" style="max-width: 100%; height: auto" title="Click to enlarge picture" />
 
3. Image Character model (Jett)

Apart from the main character models, the Toy Story ball model was also added using OpenGL primitives, those being spheres and triangles, for the red star.

Using a model hierarchy, by first creating a yellow sphere that would be the main object we inherit this position to create the rest of the main components for the ball, those being the blue stripe and the red star. \



```
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
```


To create the blue stripe a second blue sphere was created and using the scaling transformation, it was modified in the “x”, “y” and “z” axis to have it resemble the ball’s stripe and only have it be slightly extruded from the main yellow sphere model.


```
     //franja azul
   color = glm::vec3(29.0f / 255.0f, 68.0f / 255.0f, 135.0f / 255.0f);
   model = modelaux;
   model = glm::scale(model, glm::vec3(1.04f, 1.04f, 0.8f));
   glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
   glUniform3fv(uniformColor, 1, glm::value_ptr(color));
   plainTexture.UseTexture();
   sp.render(); //esfera
```


To create the red star a different set of triangles had to be created, in which each a position for each vertex is given and then connected to create the different necessary triangles. For the color a blank texture was used and later colored by using a red colored uniform.


```
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
   //    x         y          z        u   v     nx    ny    nz
     0.054193f, -0.55023f, 0.83147f, 0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
     0.15008f,  -0.12317f, 0.98079f,   0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     -0.13795f,  -0.13795f, 0.98079f,    1.0f, 0.0f,   0.0f, 0.0f, 0.0f,
    
     0.15008f,  -0.12317f, 0.98079f,   0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     0.55023f,  -0.054193f, 0.83147f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     0.25788f,  0.12742f, 0.95233f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,

     0.30866f,  0.46194f, 0.83147f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     0.037329f,  0.28521f, 0.95233f,   0.5f, 0.0f,   0.0f, 0.0f, 0.0f,

     -0.34285f,  0.39285f, 0.83147f,   0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     -0.27245f,  0.092253f, 0.95233f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,

     -0.53089f,  -0.11439f, 0.83147f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     -0.13795f,  -0.13795f, 0.98079f,    1.0f, 0.0f,   0.0f, 0.0f, 0.0f,

 };
```



```
     //estrellas rojas
   color = glm::vec3(212.0f / 255.0f, 62.0f / 255.0f, 44.0f / 255.0f);
   model = modelaux;
   model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.4f));
   model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
   glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
   glUniform3fv(uniformColor, 1, glm::value_ptr(color));
   plainTexture.UseTexture();
   meshList[5]->RenderMesh();
```


The resulting model for our ball can be seen in the following image:

<a href="https://drive.google.com/uc?export=view&id=1ls7cN80Lb0KYq8BYFwnmYbRkvXsJ0ppc"><img src="https://drive.google.com/uc?export=view&id=1ls7cN80Lb0KYq8BYFwnmYbRkvXsJ0ppc" style="max-width: 100%; height: auto" title="Click to enlarge picture" />

4. Image, Toy Story Ball

Lastly, to have each table and desk, as well as the rug occupied, different models for each main character’s franchise were imported. For Wheezy’s space city models representing houses, cars and buildings as a toy playset.


```
 // TOY STORY
 Casita_M.LoadModel("Models/casita.obj");
 Arbolito_M.LoadModel("Models/arbolito.obj");
 Edificio_M.LoadModel("Models/edificio.obj");
 Edificio2_M.LoadModel("Models/edificio_azul.obj");
 Car_M.LoadModel("Models/car_01.obj");
 Bus_M.LoadModel("Models/bus.obj");
```


<a href="https://drive.google.com/uc?export=view&id=1gGfLNszzidBvarwPPMeP8z4M5N8XofoT"><img src="https://drive.google.com/uc?export=view&id=1gGfLNszzidBvarwPPMeP8z4M5N8XofoT" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


5. Image, Wheezy’s rug environment

For Frijolito’s desk, different wrestler models were imported, additionally a fighting ring model and textures were created. The fighting ring was created using external software such as 3dsMax for the model creation and Blender was used to add texture to the model. For the wrestlers the same model was used, only the textures were changed in order to have different models, this textures were imported using OpenGL Texture classes.


```
//Mucha Lucha
Texture StreetMan1_Texture;
Texture StreetMan2_Texture;
Texture StreetMan3_Texture;
Texture Ricochet_Texture;
Texture La_Pulga_Texture;
Texture Buena_Girl_Texture;
```




<a href="https://drive.google.com/uc?export=view&id=1MhyqCLjFynymP2k_b5neMHCkbOvDYMyi"><img src="https://drive.google.com/uc?export=view&id=1MhyqCLjFynymP2k_b5neMHCkbOvDYMyi" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


<a href="https://drive.google.com/uc?export=view&id=156XFGLHlETGmpA7M5mwmUrmoVqdesHcN"><img src="https://drive.google.com/uc?export=view&id=156XFGLHlETGmpA7M5mwmUrmoVqdesHcN" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


<a href="https://drive.google.com/uc?export=view&id=1VE1K2TZEcFiswv9sPTQ-6VsKoxc7zAs8"><img src="https://drive.google.com/uc?export=view&id=1VE1K2TZEcFiswv9sPTQ-6VsKoxc7zAs8" style="max-width: 100%; height: auto" title="Click to enlarge picture" />

6. Image, Frijolito’s desk

For Jett, different crate models were imported, as well as guns and different props. With these a small shooting range was created on top of the desk. Additionally two characters from the same franchise were added.


```
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
```



<a href="https://drive.google.com/uc?export=view&id=1Xl5Z_1-v8cK09-yNmDZeZ4YFVfcQMtQ7"><img src="https://drive.google.com/uc?export=view&id=1Xl5Z_1-v8cK09-yNmDZeZ4YFVfcQMtQ7" style="max-width: 100%; height: auto" title="Click to enlarge picture" />

7. Imagen  de escenario Jett

As you can see, every franchise has its own corner of the room in which different models are imported to correctly represent each character’s franchise and make the room more lively.

<a name="skybox"></a>
## **Skybox**

For ourSkybox implementation, two sets of 6 images were used, each of which represents the internal faces of the cube that represents the sky of our world environment. In order to do this, it is required to import the 6 images and load them in different vectors as well as a skybox object type for each one.


```
std::vector<std::string> skyboxFacesDay, skyboxFacesNight;

	skyboxFacesDay.push_back("Textures/Skybox_City/city_right_f.tga");
	skyboxFacesDay.push_back("Textures/Skybox_City/city_left_f.tga");
	skyboxFacesDay.push_back("Textures/Skybox_City/city_down_f.tga");
	skyboxFacesDay.push_back("Textures/Skybox_City/city_up_f.tga");
	skyboxFacesDay.push_back("Textures/Skybox_City/city_back_f.tga");
	skyboxFacesDay.push_back("Textures/Skybox_City/city_front_f.tga");

	skyboxFacesNight.push_back("Textures/Skybox_City/city_right_fN.tga");
	skyboxFacesNight.push_back("Textures/Skybox_City/city_left_fN.tga");
	skyboxFacesNight.push_back("Textures/Skybox_City/city_down_fN.tga");
	skyboxFacesNight.push_back("Textures/Skybox_City/city_up_fN.tga");
	skyboxFacesNight.push_back("Textures/Skybox_City/city_back_fN.tga");
	skyboxFacesNight.push_back("Textures/Skybox_City/city_front_fN.tga");

	skyboxDay = Skybox(skyboxFacesDay);
	skyboxNight = Skybox(skyboxFacesNight);
```


The way in which the texture images for the night cycle were created, was by modifying their properties within the image editing specialized Photoshop application so that the saturation, brightness and contrast more closely resemble a night environment. How the day and night cycle works is better described later on, in the Lighting section of the document. As of now, we can say that as soon as the light has a value greater than 0.7 and therefore, it is daytime, the textures and the skybox will be used during the day and, failing that, the skybox will be used at night.


```
// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (contadorDiaNoche > 0.7)
			skyboxDay.DrawSkybox(camera->calculateViewMatrix(), projection);
		else
			skyboxNight.DrawSkybox(camera->calculateViewMatrix(), projection);
		shaderList[0].UseShader();
```


Shown below, is how both daytime instances can be observed:



<a href="https://drive.google.com/uc?export=view&id=1zgiSo9NkupaatUsRkV7rJNRA6oNFHi8F"><img src="https://drive.google.com/uc?export=view&id=1zgiSo9NkupaatUsRkV7rJNRA6oNFHi8F" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


Image  Skybox during Daytime



<a href="https://drive.google.com/uc?export=view&id=1ZC_wUVkAwcWw9VJF0BZNYS_AuTiHQY21"><img src="https://drive.google.com/uc?export=view&id=1ZC_wUVkAwcWw9VJF0BZNYS_AuTiHQY21" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


Image  Skybox during Nightime

<a name="avatar"></a>
## **Avatar**

For the main avatar model creation, three different characters were created using rectangular prism OpenGL primitives. These were textured using their normal vectors and the texture class for OpenGL. In order to render the full body of each character correctly a hierarchical model for each model, starting from the character’s torso was used.


```
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
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		//Pierna izq
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(-0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, tan(sin(rotBrazo[0] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[0] * toRadians), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		//Pierna der
		model = auxPersonaje;
		model = glm::translate(model, glm::vec3(0.125f, -0.75f, 0.0f));
		//rotación para la animación de caminar
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -tan(sin(rotBrazo[0] * toRadians)) * 0.125f));
		model = glm::rotate(model, sin(rotBrazo[0] * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		WheezyTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
```


8. Image Avatar Hierarchical Model code

As you can see, the character’s torso was used as the main element for every character, from here the arms, legs and head are connected. Additionally, to create more fluid-like movements whilst animating the model, different articulation points were added to create correct rotations for arms and legs.


```
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
```


9. Image Texture and Material code

For every body part the given character texture was added, as well as the opaque material shininess to have it reflect less light and be more natural.

Lastly for the avatar’s animation different joint points given by the model’s hierarchy were used to move their arms and legs. These parameters were increased and decreased  accordingly, while pressing one of the WASD keys. For each case a different movement was used, in the case of the front and backward movement a sinus equation was used to make the movement in a more natural fashion. However, when pressing S or D to turn either left or right an additional torso rotation to 90 degrees was used in the given direction, this is done to have the character face the correct direction to where he is moving.


```
//	Animación Movimiento

		if (rotBrazo[numCam - 1] >= 360.0f or rotBrazo[numCam - 1] <= -360.0f) rotBrazo[numCam - 1] = 0.0f;

		if (numCam != 0) { //verifica si se está utilizando una cámara de personaje
			switch (mainWindow.getDireccion())
			{
			case 1: //avanza al frente (W)
				rotBrazo[numCam - 1] += deltaTime * avanzaOffset;
				if (rotDireccion[numCam - 1] < 0.0f) rotDireccion[numCam - 1] += deltaTime * avanzaOffset / 2;
				if (rotDireccion[numCam - 1] > 0.0f) rotDireccion[numCam - 1] -= deltaTime * avanzaOffset / 2;
				break;
			case 2: //avanza a la izquierda (A)
				rotBrazo[numCam - 1] += deltaTime * avanzaOffset;
				if (rotDireccion[numCam - 1] < 90.0f) rotDireccion[numCam - 1] += deltaTime * avanzaOffset / 2;
				break;
			case 3: //avanza hacia atrás (S)
				rotBrazo[numCam - 1] -= deltaTime * avanzaOffset;
				if (rotDireccion[numCam - 1] < 0.0f) rotDireccion[numCam - 1] += deltaTime * avanzaOffset / 2;
				if (rotDireccion[numCam - 1] > 0.0f) rotDireccion[numCam - 1] -= deltaTime * avanzaOffset / 2;
				break;
			case 4: //avanza a la derecha (D)
				rotBrazo[numCam - 1] += deltaTime * avanzaOffset;
				if (rotDireccion[numCam - 1] > -90.0f) rotDireccion[numCam - 1] -= deltaTime * avanzaOffset / 2;
				break;
			default:
				for (int i = 0; i < 4; i++) {
					if (rotBrazo[i] > 0.0f)rotBrazo[i] -= deltaTime * avanzaOffset;
					if (rotBrazo[i] < 0.0f)rotBrazo[i] += deltaTime * avanzaOffset;
					if (rotDireccion[i] > 0.0f)rotBrazo[i] -= deltaTime * avanzaOffset / 2;
					if (rotDireccion[i] < 0.0f)rotBrazo[i] += deltaTime * avanzaOffset / 2;

					if (rotBrazo[i] < 25.0f and rotBrazo[i] > -25.0f) rotBrazo[i] = 0.0f;
				}
				break;
			}
		}
```


10. Image Avatar animation code

Lastly when we stop pressing or holding one of the keys for movement, the character will automatically return to the zero rotation position to simulate a completely still stance.

<a name="route"></a>
## **Route**

For the main camera movement we need to use a 3 variable vector to which a given camera is assigned, this camera can be either one of the 3 character’s perspectives or the main global camera. The choice of which camera is used is given by the _CameraVal_ variable that is declared in the class file _Window_ and can increase from 0 to 3 or advance from 3 to 0 with each press of the _C_ key. If one of the character cameras is used, the angle position of where the camera is looking at has to be given to the character's torso, in order to have it “look” at the correct position and rotate accordingly. To do this rotation and translation functions are needed to change one axis reference to another. In this case a transformation from the camera axis to the scenery axis is needed.


```
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
```

<a name="lighting"></a>
## **Lighting**

In the lighting section, we have a directional light that acts as the sun, as well as 4 light arrays that represent pointlights and one array of spotlights.


```
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLightsNoche[MAX_POINT_LIGHTS];
PointLight pointLightsCama[MAX_POINT_LIGHTS];
PointLight pointLightsSpike[MAX_POINT_LIGHTS];//Todas las pointlights
PointLight pointLightsSpike1[MAX_POINT_LIGHTS];//Pointlights sin los leds de la cama y el escritorio
SpotLight spotLights[MAX_SPOT_LIGHTS];
```


Depending on which lights are active, the array that is sent to the shader in the pointlight array will always have two lights. These are the day and night lights, the night lights being the fixtures in the ceiling. One of them will always be on.

The array _pointLightsCama_ has 2 ceiling lamps as well as 2 pointlights that move around the bed and main computer setup desk, in order to give the illusion of a LED strip.


```
	//LUZ DE LEDS DE LA CAMA
	pointLightsCama[0] = PointLight(1.0f, 0.0f, 0.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		-150.0f, 20.0f, 40.0f, // posicion
		0.5f, 0.01f, 0.001f); // ecuaci'n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount1++;

	//LUZ DE LEDS DEL ESCRITORIO
	pointLightsCama[1] = PointLight(1.0f, 0.0f, 0.0f, //color 
		0.6f, 1.0f, //ambiente, difusa
		0.0f, 60.0f, -375.0f, // posicion
		0.5f, 0.01f, 0.001f); // ecuaci'n de segundo grado 
	//  c,	b ,	 a
		//sqrt(b^2 -4ac)
	// para no dar una raiz comlejo
	pointLightCount1++;
```


We need to move these lights using a variable that decreases or increases the given sequence of if clauses, to later pass through the value of the variable to a function that modifies the position of the pointlight.


```
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
```


For the day and night cycle a variable is created that increments slowly until it reaches a 1 value, after that this variable decreases until it reaches 0. For each increment or decrease we need to pass through the value of the ambient component. When this is below 0.7 the ceiling lights will turn on, in order to continue to give light when the day and night cycle is in the night setting.


```
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
```


For the array pointLightsSpike and pointLightsSpike1, apart from having the ceiling lamp lights, they have a light that is for the spike, the difference between both of the 2 arrays is that the pointLightsSpike have the lights for the bed and desk, meanwhile the pointLightsSpike1 do not have it, this is just for the  case the lights are not active for the bed and desk. 

To know what array was sended to the shader, an if and else sequence was made that are valued with flags that tell us which lights are active and which not 


```
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

			if(mainWindow.getDeskLamp() == 1)
				shaderList[0].SetSpotLights(spotLights, spotLightCount);
			else 
				shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
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
			else if (LedCama == 0 and !spikeSube)
				shaderList[0].SetPointLights(pointLightsNoche, pointLightCount - 2);

			if (mainWindow.getDeskLamp() == 1)
				shaderList[0].SetSpotLights(spotLights, spotLightCount);
			else
				shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
		}
```


The mean condition to know what array is going to be sended to the shader is if the directional light is equal or below 0.7, if yes , then the arrays are sended with the  ceiling lights activated to the shader, if not the arrays are sended to the shader decreasing the last 2 lights( the ceiling lights). The next condition that is valued is if the lights from the bed and desk are active and if the spike animation is still active, if yes then the arrays are sended to the shader with the light from the bed and desk  and also the spike light 

It is important to mention that the spike light flashes, this was made with a variable that increases and decreases, when the variable is increasing, the spike light is turned on, meanwhile it decreases it turns off, this makes a flash  illusion.  

In case the light from the bed and desk are off, the light just  from the spike is sended to the shader  and the same process of shining is remade  

<a name="animation"></a>
## **Animation**

The first of our animations that is visible to the naked eye on stage is the one with the ball bouncing around the mat. To create this animation we decided to take the main model of our ball, which is the yellow sphere, and make its position follow an oval path, for this we took the parametric functions of the sphere and from the angle it moved.


```
// Posicion de la pelota
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
```


On the other hand, to simulate that this ball was bouncing, we used a sinusoidal function with absolute values for its position in Y, so that the moment it hits the ground it rises again with some smoothness.


```
   // ANIMACION PELOTA
   posPelota.y = posPelotaY + abs(15 * sin(rotPelotaX * toRadians));
   rotPelotaX += deltaTime * 5.0f;
   if (rotPelotaX > 360) rotPelotaX = 0;
```


Finally, to make the ball spin when it bounces, we decided to make it spin in one direction and spin in another direction when it hits the ground with conditionals.


```
   float auxRotPelotax = (rotPelotaX < 180) ? rotPelotaX : -rotPelotaX;
```


Therefore, we have an animation where the ball follows an ellipse-shaped trajectory, bounces and rotates in both directions.



<a href="https://drive.google.com/uc?export=view&id=1EpbEqh5t0QiXtS9bYsEWUl_CQSsUPHvb"><img src="https://drive.google.com/uc?export=view&id=1EpbEqh5t0QiXtS9bYsEWUl_CQSsUPHvb" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


.Image Bouncing Ball.

In our second animation it was done with limits, where some of the toys that are lying on the floor are moved to the furniture to be stored. For this we decided to use variables for the position and rotation of each object that was going to be saved.


```
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
```


For each toy there are different states that determine the way it will move, as well as a conditional limit of this movement and the next state in case that limit is reached.


```
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
```


In this case, the code for the movement of the bus is shown where the position or rotation of the bus is modified in different axes because it first gets up and then turns around, goes up on the ramp and settles down by turning around again. At the end, the state of "BUS_LISTO" is reached, which indicates the end of this animation.

For the other toys it is something similar with different variables and states that start executing when you press the G key, but not all the objects finish at the same time.

Particularly, in the case of the building, it is pushed by a car and we use formulas of rotation and translation of axes used only in the status where the car pushes the building.


```
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
```


Below is the animation of the toys when they moved to the furniture to be stored.



<a href="https://drive.google.com/uc?export=view&id=1-MGA2iy85r2q7VlZOSaIUAlG4E0dMRzF"><img src="https://drive.google.com/uc?export=view&id=1-MGA2iy85r2q7VlZOSaIUAlG4E0dMRzF" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


Images of Toys getting put away

The following animation was a simple animation to make the fighting characters on the Mucha Lucha stage fight. This animation makes use of sine and cosine functions to move the characters and similar to how a child moves his toys when he plays wrestlers.

The following complex animation is Valorant-themed, it is about the characters Fenix and KillJoy, where the character Fenix shoots KillJoy while she is running, the attacker is turning and pointing at all times in the direction of KillJoy. This was done with variables that increase and decrease their value, this for the rotation and translation of the objects.

When Kill Joy runs, her legs move, this is achieved with a variable that increases and decreases the rotation of KillJoy's legs.


```
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
```


As we can see, the if and else if structure is used to achieve this movement, first the rotation variable of Kill Joy's right leg is increased, then it is decreased and this is repeated with the left leg.

When the Fenix character shoots, a small rotation is made on the weapon to simulate the shot, this is achieved similar to Kill Joy's leg movement.


```
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
```


As we can see, there is an increase and decrease of the variable that rotates the weapon, with a small angle so that the animation is not exaggerated.

In addition to the KillJoy animation, there is an animation for the Spike, this, unlike other animations, is not done automatically or by pressing a key, but is activated when the Jett character model is nearby. This is done using functions for the distance between points. Originally it was thought to carry out the vector subtraction to be able to find the distance, however, the distance function has already been implemented in C++, which returns the distance between two vectors. In this way, if the module of the resulting vector is less than or equal to 25 distance units, the Spike deactivation animation will start; This consists of rotating the central cylinder while the disk is raised and rotated, in turn there is a flashing of lights to give it a more visual effect and similar to the animation that is in the video game. Also, in the event that the character moves away, the defuse of the Spike is canceled and it returns to its initial position.

The next animation was using the _Mucha Lucha_ characters, having a small fight. This animation requires 8 different states, where the idea is that the character _La Pulga_ approaches _Buena Girl_ and they begin to hit each other, simply moving their arms rapidly, as if it were a children's fight. After doing this for a while, the character _Rikochet _approaches and kicks _La Pulga_ in the air, after a while they both fly off and return to their initial position.



<a href="https://drive.google.com/uc?export=view&id=1q5ugO4ccpSgRvuH3wig7eRgYNMYI_r-Q"><img src="https://drive.google.com/uc?export=view&id=1q5ugO4ccpSgRvuH3wig7eRgYNMYI_r-Q" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


Image Mucha Lucha Animation

The cases used where as follows:

 


```
//	ANIMACION LUCHADORES
		if (rotLuchador1 < 360.0f) rotLuchador1 += deltaTime * 2.5;
		else rotLuchador1 = 0.0f;

		//avanzaOffset = 0.5f;
		float offsetNew = 0.2f;

		switch (estado_ML)
		{
		case 0://la pulga camina hacia BG
			if (movX_LP < 3.5) {
				movX_LP += deltaTime * offsetNew;
				rotPiernasLP += deltaTime * avanzaOffset;
			}
			if (movZ_LP < 3.5) {
				movZ_LP += deltaTime * offsetNew;
			}
			if (rotLa_Pulga < 45) {
				rotLa_Pulga += deltaTime * avanzaOffset/2;
			}
			if (movX_LP >= 3.5 && movZ_LP >= 3.5 && rotLa_Pulga >= 45) {
				estado_ML ++;
				rotPiernasLP = 0; movY_LP = 4.0f;
			}
			break;
		case 1: //La pulga da golpe a BG
			if (rotBrazoIzq_LP < 90) {
				rotBrazoIzq_LP += deltaTime * avanzaOffset/4;
			}
			else {
				estado_ML ++;
			}
			break;
		case 2: //BG se lo regresa
			if (rotBrazoIzq_LP > 0) {
				rotBrazoIzq_LP -= deltaTime * avanzaOffset / 4;
			}
			if (rotBuena_Girl < 45) {
				rotBuena_Girl += deltaTime * avanzaOffset / 2;
			}
			if (rotBrazoIzq_BG < 90) {
				rotBrazoIzq_BG += deltaTime * avanzaOffset / 4;
			}
			if (rotBuena_Girl >= 45 && rotBrazoIzq_LP <= 0 && rotBrazoIzq_BG >= 90) {
				estado_ML ++;
				rotBrazoDer_BG = rotBrazoIzq_BG = 45;
			}
			break;
		case 3: // se golpean 
			if (rotBrazoIzq_LP < 1800) {
				sumaAngulo = 180 * toRadians;
				rotBrazoIzq_LP += deltaTime * avanzaOffset * 2;
				rotBrazoDer_LP += deltaTime * avanzaOffset * 2;
				rotBrazoIzq_BG += deltaTime * avanzaOffset * 2;
				rotBrazoDer_BG += deltaTime * avanzaOffset * 2;
			}
			else {
				sumaAngulo = 0;
				rotBrazoIzq_LP = rotBrazoDer_LP = rotBrazoIzq_BG = rotBrazoDer_BG = 0;
				estado_ML++;
			}
			break;
		case 4: // rikochet le entra
			if (rotBrazoIzq_LP < 1200) {
				sumaAngulo = 180 * toRadians;
				rotBrazoIzq_LP += deltaTime * avanzaOffset * 2;
				rotBrazoDer_LP += deltaTime * avanzaOffset * 2;
				rotBrazoIzq_BG += deltaTime * avanzaOffset * 2;
				rotBrazoDer_BG += deltaTime * avanzaOffset * 2;
			}
			
			if (movZ_Rik < 2.3) {
				if (movZ_Rik >= 1) {
					movY_Rik += deltaTime * offsetNew;
				}
				movZ_Rik += deltaTime * offsetNew;
				rotPiernasR += deltaTime * avanzaOffset;
			}
			else {
				sumaAngulo = 0;
				rotPiernasR = 0;
				estado_ML++;
			}
			
			break;
		case 5: // rikochet los patea
			if (rotBrazoIzq_LP < 600) {
				sumaAngulo = 180 * toRadians;
				rotBrazoIzq_LP += deltaTime * avanzaOffset * 2;
				rotBrazoDer_LP += deltaTime * avanzaOffset * 2;
				rotBrazoIzq_BG += deltaTime * avanzaOffset * 2;
				rotBrazoDer_BG += deltaTime * avanzaOffset * 2;
			}
			if (rotRikochet > -30) {
				rotRikochet -= deltaTime * avanzaOffset;
			}
			if (rotY_Rikochet > -30) {
				rotY_Rikochet -= deltaTime * avanzaOffset;
			}
			if (rotPiernasR < 1800) {
				rotPiernasR += deltaTime * avanzaOffset;
			}
			if (rotRikochet <= -30 && rotY_Rikochet <= -30 && rotPiernasR >= 1800) {
				sumaAngulo = 0;
				rotPiernasR = 0;
				estado_ML++;
			}
			break;
		case 6: //salen volando
			if (rotY_Rikochet > -360) {
				rotY_Rikochet -= deltaTime * avanzaOffset;
			}
			if (rotRikochet < 0) {
				rotRikochet += deltaTime * avanzaOffset;
			}
			if (rotPiernasR > 0) {
				rotPiernasR -= deltaTime * avanzaOffset;
			}
			if (movZ_Rik > -5) {
				movZ_Rik -= deltaTime * offsetNew;
			}
			if (rotY_La_Pulga < 450) {
				rotY_La_Pulga += deltaTime * avanzaOffset;
			}
			if (rotLa_Pulga > 0) {
				rotLa_Pulga -= deltaTime * avanzaOffset;
			}
			if (rotBuena_Girl > 0) {
				rotBuena_Girl -= deltaTime * avanzaOffset;
			}
			if (movX_LP > -5) {
				movX_LP -= deltaTime * offsetNew;
			}
			if (movZ_LP > -5) {
				movZ_LP -= deltaTime * offsetNew;
			}

			if (movZ_Rik <= -5 && movX_LP <= -5 && movZ_LP <= -5) {
				estado_ML++;
			}
			break;
		case 7: //espera unos segundos
			if (count_tiempo < 1000) {
				count_tiempo += deltaTime * avanzaOffset;
			}
			else {
				estado_ML++;
			}
			break;
		default:
			estado_ML = 0; count_tiempo = 0;
			rotRikochet = 0; rotY_Rikochet = 0;
			rotLa_Pulga = 0; rotY_La_Pulga = 0; rotBrazoDer_LP = 0; rotBrazoIzq_LP = 0;
			rotBuena_Girl = 0; rotBrazoDer_BG = 0; rotBrazoIzq_BG = 0;
			movX_Rik = 5.0f; movY_Rik = 4.0f; movZ_Rik = -5.0f;
			movX_LP = -5.0f; movY_LP = 4.0f, movZ_LP = -5.0;
			movX_BG = 5.0f; movY_BG = 4.0f; movZ_BG = 5.0f;
			rotPiernasR = 0.0f; rotPiernasLP = 0.0f; rotPiernasBG = 0.0f;
			break;
		}
```

<a name="audio"></a>
## **AUDIO**

For audio usage, irrklang library was used, to use this library it was necessary to download the .h, .ddl and .lib files from the following link:

[https://www.ambiera.com/irrklang/downloads.html](https://www.ambiera.com/irrklang/downloads.html)

Added the following to the project's input-linker: irrKlang.lib;



<a href="https://drive.google.com/uc?export=view&id=1md8CUPodQF-yHOrxeQ1LLEv3WVKEbWXy"><img src="https://drive.google.com/uc?export=view&id=1md8CUPodQF-yHOrxeQ1LLEv3WVKEbWXy" style="max-width: 100%; height: auto" title="Click to enlarge picture" />


A namespace had to be created for its use, as well as creating two ISoundEngine class objects .


```
using namespace irrklang;
       irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	ISoundEngine* ambiental = createIrrKlangDevice();
	//Sonido ambiente
	ambiental->play2D("Media/AmbienteToyStory.ogg", true);
	ambiental->setSoundVolume(0.1);
```


The play2D function was used to play the song in the entire virtual world, passing it as a parameter the location of the file and a boolean that tells us if the song is played in a loop. The songs used for this have .ogg format. Additionally, we use the _setSoundVolume _function, which will modify the volume of this track.

También se implementó el sonido 3D (se escucha el sonido al acercarnos a cierta posición y se desactiva si nos alejamos de esta misma), mediante la función _play3D._

3D audio was also added (it's only possible to hear the audio at a certain position and it will auto stop if we are far from that given point), for this the _play3D_ function was used_._


```
ISound* music = engine->play3D("Media/la-cumbia-de-valorant.ogg", vec3df(-80.0f, 69.0f, -330.0f), true, false, true);
music->setMinDistance(10.0f);
```


We send the location of the song as a parameter, as well as the position where we want the sound to be, a boolean for if we want it to be executed in a loop and if we want the track to start paused or not. We also use the _setMinDistance_ function, this is to set the minimum distance from which we want the song to start playing.

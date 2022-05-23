#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	carx = 2.0f;
	camaraVal = 0;
	LedCama = 0;
	saveToys = false;
	direccion = 0;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Proyecto final", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est� usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> muevex += 1.0f;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow-> muevex -= 1.0f;
	}

	if (key == GLFW_KEY_UP)
	{
		theWindow->carx -= 1.0f;
	}

	if (key == GLFW_KEY_DOWN)
	{
		theWindow->carx += 1.0f;
	}

	if (key == GLFW_KEY_G and action == GLFW_PRESS) {
		theWindow->saveToys = !theWindow->saveToys;
	}

	if (key == GLFW_KEY_C and action== GLFW_PRESS)
	{
		theWindow->camaraVal++;
		if (theWindow->camaraVal > 3) {
			theWindow->camaraVal=0;
		}
	}

	if (key == GLFW_KEY_P  and theWindow->LedCama == 0 and action == GLFW_PRESS)
	{
		//printf("\nHOLA = %d", theWindow->LedCama);
		theWindow->LedCama = 1;
	}
	else if (key == GLFW_KEY_P and theWindow->LedCama == 1 and action == GLFW_PRESS)
	{
		//printf("\nHOLA = %d", theWindow->LedCama);
		theWindow->LedCama = 0;
	}
	if (key == GLFW_KEY_O and theWindow->DeskLamp == 0 and action == GLFW_PRESS)
	{
		theWindow->DeskLamp = 1;
	}
	else if (key == GLFW_KEY_O and theWindow->DeskLamp == 1 and action == GLFW_PRESS)
	{
		theWindow->DeskLamp = 0;
	}

	if (key == GLFW_KEY_J and theWindow-> LampVal == 0 and action == GLFW_PRESS)
	{
		theWindow->LampVal = 1;
	}
	else if (key == GLFW_KEY_J and theWindow-> LampVal == 1 and action == GLFW_PRESS)
	{
		theWindow->LampVal = 0;
	}

	if (key == GLFW_KEY_W and action == GLFW_PRESS)
	{
		theWindow->direccion = 1;
	}
	else if (key == GLFW_KEY_A and action == GLFW_PRESS)
	{
		theWindow->direccion = 2;
	}
	else if (key == GLFW_KEY_S and action == GLFW_PRESS)
	{
		theWindow->direccion = 3;
	}
	else if (key == GLFW_KEY_D and action == GLFW_PRESS)
	{
		theWindow->direccion = 4;
	}
	else if (action == GLFW_RELEASE)
	{
		theWindow->direccion = 0;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
	theWindow->action = action;
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}

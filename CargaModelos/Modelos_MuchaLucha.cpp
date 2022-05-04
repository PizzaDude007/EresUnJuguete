#include "Modelos_MuchaLucha.h"

//glm::mat4 frijolito() {
//	glm::mat4 model(1.0);
//	model = glm::mat
//}
//
//glm::mat4 personaLuchador() {
//
//}
//
//glm::mat4 personaLuchador(float x, float y, float z){
//
//}

Modelos_MuchaLucha::Modelos_MuchaLucha() {
	ML_Ring_M.LoadModel("Models/ring_texturizado.obj");
}

void Modelos_MuchaLucha::RenderModels(GLuint color, GLuint model) {
	this->uniformColor = color;
	this->uniformModel = model;

	//Ring
	glm::mat4 model(1.0);
	model = glm::translate(model, glm::vec3(200.0f, 63.5f, -230.0f));
	model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ML_Ring_M.RenderModel();
}
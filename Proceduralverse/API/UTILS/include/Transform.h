#pragma once
#include <GLM/include/glm.hpp>
#include <GLM/include/gtc/matrix_transform.hpp>
#include <GLM/include/gtc/type_ptr.hpp>
class Transform
{
public:
	glm::mat4 model, view, proj;
	Transform();
	glm::mat4 MoveModel(glm::vec3 movement);
	glm::mat4  RotateModel(glm::vec3 rotationAxe, float degree);
	glm::mat4  ScaleModel(glm::vec3 scaling);
	glm::mat4  RotateCamera(glm::vec3 rotationAxe, float degree);
	void ResetModel();
	void ResetView();

private:

};


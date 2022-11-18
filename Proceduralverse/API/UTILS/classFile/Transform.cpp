#include <Transform.h>
#include <Constants.h>

Transform::Transform()
{
	model = glm::mat4{ 1.0f };
	view = glm::mat4{ 1.0f };
	proj = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

glm::mat4 Transform::MoveModel(glm::vec3 movement)
{
	model = glm::translate(model, movement);
	return model;
}

glm::mat4 Transform::RotateModel(glm::vec3 rotationAxe, float degree)
{
	model = glm::rotate(model, glm::radians(degree), rotationAxe);
	return model;
}

glm::mat4 Transform::ScaleModel(glm::vec3 scaling)
{
	model = glm::scale(model, scaling);
	return model;
}


glm::mat4 Transform::RotateCamera(glm::vec3 rotationAxe, float degree)
{
	view = glm::rotate(view, glm::radians(degree), rotationAxe);
	return view;
}

void Transform::ResetModel()
{
	model = glm::mat4{ 1.0f };
}

void Transform::ResetView()
{
	view = glm::mat4{ 1.0f };
}

#include "MovingBody.h"


MovingBody::MovingBody(glm::vec3 initialPos, glm::vec3 initialScale, float inicialRotationAngle, glm::vec3 rotationAxis)
{
	setPosAbsolute(initialPos);
	setScaleAbsolute(initialScale);
	setRotationAbsolute(inicialRotationAngle, rotationAxis);
}

void MovingBody::Draw(Shader& shader)
{
	glm::mat4 ModelMatrix = positionMatrix * scaleMatrix * rotationMatrix;
	shader.setMat4("model", ModelMatrix);
}

void MovingBody::setPosAbsolute(glm::vec3 newPos)
{
	positionMatrix = glm::mat4(1.0f);
	positionMatrix = glm::translate(positionMatrix, newPos);
}

void MovingBody::translateBy(glm::vec3 vector)
{
	positionMatrix = glm::translate(positionMatrix, vector);
}

void MovingBody::setScaleAbsolute(glm::vec3 newScale)
{
	scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, newScale);
}

void MovingBody::scaleBy(glm::vec3 vector)
{
	scaleMatrix = glm::scale(scaleMatrix, vector);
}

void MovingBody::setRotationAbsolute(float angle, glm::vec3 rotationAxis)
{
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, angle, rotationAxis);
}

void MovingBody::rotateBy(float angle, glm::vec3 rotationAxis)
{
	rotationMatrix = glm::rotate(rotationMatrix, angle, rotationAxis);
}

glm::vec3 MovingBody::getPos()
{
	return glm::vec3(positionMatrix[3][0], positionMatrix[3][1], positionMatrix[3][2]);
}

glm::vec3 MovingBody::getScale()
{
	return glm::vec3(scaleMatrix[0][0], scaleMatrix[1][1], scaleMatrix[2][2]);
}




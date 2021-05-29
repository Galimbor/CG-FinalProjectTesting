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

void MovingBody::Draw(Shader& shader, float deltaTime)
{
	Draw(shader);
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
	glm::vec4 frontVectorTemp = rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	frontVector.x = frontVectorTemp.x;
	frontVector.y = frontVectorTemp.y;
	frontVector.z = frontVectorTemp.z;
	glm::vec4 rightVectorTemp = rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	rightVector.x = rightVectorTemp.x;
	rightVector.y = rightVectorTemp.y;
	rightVector.z = rightVectorTemp.z;
}

void MovingBody::rotateBy(float angle, glm::vec3 rotationAxis)
{
	rotationMatrix = glm::rotate(rotationMatrix, angle, rotationAxis);
	glm::vec4 frontVectorTemp = rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	frontVector.x = frontVectorTemp.x;
	frontVector.y = frontVectorTemp.y;
	frontVector.z = frontVectorTemp.z;
	glm::vec4 rightVectorTemp = rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	rightVector.x = rightVectorTemp.x;
	rightVector.y = rightVectorTemp.y;
	rightVector.z = rightVectorTemp.z;

}

void MovingBody::translateBySpeed(glm::vec3 direction, float deltaTime)
{
	direction = glm::normalize(direction);
	translateBy(direction * moveSpeed * deltaTime);
}

void MovingBody::rotateBySpeed(float angle, glm::vec3 rotationAxis, float deltaTime)
{
	rotateBy(angle * rotSpeed * deltaTime, rotationAxis);
}

glm::vec3 MovingBody::getPos()
{
	return glm::vec3(positionMatrix[3][0], positionMatrix[3][1], positionMatrix[3][2]);
}

glm::vec3 MovingBody::getScale()
{
	return glm::vec3(scaleMatrix[0][0], scaleMatrix[1][1], scaleMatrix[2][2]);
}

glm::vec3 MovingBody::getFrontVector()
{
	return frontVector;
}

glm::vec3 MovingBody::getRightVector()
{
	return rightVector;
}

void MovingBody::getRotation(float& out_rotationAngle, glm::vec3& out_rotationAxis)
{
	//formula taken from: https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm
	out_rotationAngle = glm::acos
	(
		(
			rotationMatrix[0][0] +
			rotationMatrix[1][1] +
			rotationMatrix[2][2] -
			1
		)
		/ 2
	);

	//formula taken from https://en.wikipedia.org/wiki/Rotation_matrix#:~:text=for%20more%20details).-,Conversion%20from%20rotation%20matrix%20and%20to%20axis%E2%80%93angle,axis%20(Euler%20rotation%20theorem).
	out_rotationAxis.x = rotationMatrix[1][2] - rotationMatrix[2][1];
	out_rotationAxis.y = rotationMatrix[2][0] - rotationMatrix[0][2];
	out_rotationAxis.z = rotationMatrix[0][1] - rotationMatrix[1][0];
}

std::vector<float> MovingBody::computeTranslationEquation(float ini_position, float ini_velocity, float accelaration, float elapsedTime)
{
	std::vector<float> result = std::vector<float>(2, 0.0f);
	result[0] = ini_position + ini_velocity * elapsedTime + (accelaration / 2) * elapsedTime * elapsedTime;
	result[1] = ini_velocity + accelaration * elapsedTime;
	return result;
}




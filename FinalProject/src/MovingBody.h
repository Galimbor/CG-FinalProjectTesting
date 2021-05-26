#ifndef MOVINGBODY_CLASS_H
#define MOVINGBODY_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Shader.h"

class MovingBody
{
private:
	glm::mat4 positionMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 rotationMatrix = glm::mat4(1.0f);

	glm::vec3 frontVector = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 rightVector = glm::vec3(0.0f, 0.0f, 1.0f);

protected:
	float moveSpeed = 10.0f;
	float rotSpeed = 10.0f;

	float weight = 10.0f;

public:
	MovingBody
	(
		glm::vec3 initialPos = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 initialScale = glm::vec3(1.0f, 1.0f, 1.0f),
		float inicialRotationAngle = 0,
		glm::vec3 rotationAxis = glm::vec3(0.0f,1.0f,0.0f)
	);

	virtual void Draw(Shader& shader);

	virtual void setPosAbsolute(glm::vec3 newPos);

	virtual void translateBy(glm::vec3 vector);

	virtual void setScaleAbsolute(glm::vec3 newScale);

	virtual void scaleBy(glm::vec3 vector);

	virtual void setRotationAbsolute(float angle, glm::vec3 rotationAxis);

	virtual void rotateBy(float angle, glm::vec3 rotationAxis);

	void translateBySpeed(glm::vec3 direction, float deltaTime);
	void rotateBySpeed(float angle, glm::vec3 rotationAxis, float deltaTime);

	glm::vec3 getPos();
	glm::vec3 getScale();

	glm::vec3 getFrontVector();
	glm::vec3 getRightVector();

	void getRotation(float& out_rotationAngle, glm::vec3& out_rotationAxis);

	//result[0] == new pos && result[1] == new velocity
	static std::vector<float> computeTranslationEquation(float ini_position, float ini_velocity, float accelaration, float elapsedTime);
};
#endif

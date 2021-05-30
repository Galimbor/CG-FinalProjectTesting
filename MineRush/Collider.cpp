#include "Collider.h"

Collider::Collider(CollisionTypes::Type type, glm::vec3 boxOffset, glm::vec3 boxDimentions)
{
	this->colType = type;
	this->boxOffset = boxOffset;
	this->boxDimentions = boxDimentions;

}

CollisionResult Collider::isColliding(Collider* otherCollider)
{
	CollisionResult result;
	glm::vec3 thisBoxStart = getBoxStart();
	glm::vec3 otherBoxStart = otherCollider->getBoxStart();

	float xThisDimention = thisBoxStart.x + this->boxDimentions.x;
	float xOtherDimention = otherBoxStart.x + otherCollider->boxDimentions.x;
	bool xCollision = xThisDimention >= otherBoxStart.x
		&& xOtherDimention >= thisBoxStart.x;

	bool yCollision = thisBoxStart.y + this->boxDimentions.y >= otherBoxStart.y
		&& otherBoxStart.y + otherCollider->boxDimentions.y >= thisBoxStart.y;

	bool zCollision = thisBoxStart.z + this->boxDimentions.z >= otherBoxStart.z
		&& otherBoxStart.z + otherCollider->boxDimentions.z >= thisBoxStart.z;

	result.isColliding = xCollision && yCollision && zCollision;
	result.colType = this->colType;
	return result;
}

void Collider::setPosAbsolute(glm::vec3 newPos)
{
	parentPosition = newPos;
}

glm::vec3 Collider::getBoxStart()
{
	return boxOffset + parentPosition;
}


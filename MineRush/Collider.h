#ifndef COLLIDER_CLASS_H
#define COLLIDER_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace CollisionTypes {
	enum Type
	{
		Block,
		Overlap,
		None
	};
};

struct CollisionResult
{
	CollisionTypes::Type colType;
	bool isColliding = false;
};

class Collider
{
private:
	CollisionTypes::Type colType;
	glm::vec3 boxOffset;
	glm::vec3 boxDimentions;

	glm::vec3 parentPosition = glm::vec3(0.0f, 0.0f, 0.0f);

public:
	Collider(CollisionTypes::Type type, glm::vec3 boxOffset, glm::vec3 boxDimentions);

	CollisionResult isColliding(Collider* otherCollider);

	void setPosAbsolute(glm::vec3 newPos);

	glm::vec3 getBoxStart();
};



#endif
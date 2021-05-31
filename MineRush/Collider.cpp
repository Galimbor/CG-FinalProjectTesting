#include "Collider.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

Collider::Collider(CollisionTypes::Type type, glm::vec3 boxOffset, glm::vec3 boxDimentions)
{
	this->colType = type;
	this->boxOffset = boxOffset;
	this->boxDimentions = boxDimentions;

	if (debugDrawBox)
	{
		makeDrawableBox(vertices, indices);
		//debugShader = new Shader("Shaders/debugCollisions.vert", "Shaders/debugCollisions.frag");
		setupDebug();
	}
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

void Collider::DrawDebug(Shader& shader)
{
	if (debugDrawBox)
	{
		glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), parentPosition);
		shader.setMat4("model", ModelMatrix);
		vao->Bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		vao->Unbind();
	}
}

void Collider::makeDrawableBox(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices)
{
	vertices = std::vector<glm::vec3>(8);
	indices = std::vector<unsigned int>(36);

	vertices[0] = getBoxStart();
	vertices[1] = getBoxStart() - glm::vec3(boxDimentions.x, 0.0f, 0.0f);
	vertices[2] = getBoxStart() - glm::vec3(boxDimentions.x, 0.0f, boxDimentions.z);
	vertices[3] = getBoxStart() - glm::vec3(0.0f, 0.0f, boxDimentions.z);
	vertices[4] = getBoxStart() - glm::vec3(0.0f, boxDimentions.y, 0.0f);
	vertices[5] = getBoxStart() - glm::vec3(boxDimentions.x, boxDimentions.y, 0.0f);
	vertices[6] = getBoxStart() - glm::vec3(boxDimentions.x, boxDimentions.y, boxDimentions.z);
	vertices[7] = getBoxStart() - glm::vec3(0.0f, boxDimentions.y, boxDimentions.z);


	int count = 0;
	//top face (0-1-2-3)
	indices[count++] = 2;
	indices[count++] = 1;
	indices[count++] = 0;

	indices[count++] = 0;
	indices[count++] = 3;
	indices[count++] = 2;

	//face (4-5-6-7)
	indices[count++] = 4;
	indices[count++] = 5;
	indices[count++] = 6;

	indices[count++] = 4;
	indices[count++] = 6;
	indices[count++] = 7;

	//face (3-2-6-7)
	indices[count++] = 3;
	indices[count++] = 6;
	indices[count++] = 2;

	indices[count++] = 3;
	indices[count++] = 7;
	indices[count++] = 6;

	//face (2-1-5-6)
	indices[count++] = 2;
	indices[count++] = 6;
	indices[count++] = 5;

	indices[count++] = 5;
	indices[count++] = 1;
	indices[count++] = 2;

	//face (0-1-5-4)
	indices[count++] = 0;
	indices[count++] = 1;
	indices[count++] = 4;

	indices[count++] = 1;
	indices[count++] = 5;
	indices[count++] = 4;

	//face (3-0-4-7)
	indices[count++] = 0;
	indices[count++] = 4;
	indices[count++] = 3;

	indices[count++] = 4;
	indices[count++] = 7;
	indices[count++] = 3;


}

void Collider::setupDebug()
{
	//debugShader->Activate();
	vao = new VAO();
	vao->Bind();

	vbo = new VBO(&vertices[0].x, vertices.size() * sizeof(glm::vec3));

	ebo = new EBO(&indices[0], indices.size() * sizeof(unsigned int));

	//pos vertexes
	vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);

	vao->Unbind();
	vbo->Unbind();
	ebo->Unbind();
}


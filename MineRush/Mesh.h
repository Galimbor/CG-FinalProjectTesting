#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "MovingBody.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

struct Material {
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    glm::vec3 Ambient;
    float Shininess;
};


class Mesh : public MovingBody {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    Material mat;

    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 ModelMat;
    

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material mat_);
    virtual void Draw(Shader& shader) override;
private:
    //  render data
    class VAO* vao = nullptr;
    class VBO* vbo = nullptr;
    class EBO* ebo = nullptr;

    void setupMesh();
};
#endif
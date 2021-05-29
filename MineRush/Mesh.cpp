#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material mat_)
    : MovingBody()
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->mat = mat_;

    setupMesh();

    
    for (int i = 0; i < vertices.size(); i++)
    {
        center += vertices[i].Position;
    }
    center /= vertices.size();
}

void Mesh::setupMesh()
{
    vao = new VAO();
    vao->Bind();

	vbo = new VBO(&vertices[0], vertices.size() * sizeof(Vertex));

	ebo = new EBO(&indices[0], indices.size() * sizeof(unsigned int));

	//pos vertexes
	vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	vao->LinkAttrib(*vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    vao->LinkAttrib(*vbo, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    vao->LinkAttrib(*vbo, 4, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	vao->Unbind();
	vbo->Unbind();
	ebo->Unbind();
}


void Mesh::Draw(Shader& shader)
{
    MovingBody::Draw(shader);

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        shader.setFloat((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    shader.setVec3("material.ambient", mat.Ambient.r, mat.Ambient.g, mat.Ambient.b);
    shader.setVec3("material.diffuse", mat.Diffuse.r, mat.Diffuse.g, mat.Diffuse.b);
    shader.setVec3("material.specular", mat.Specular.r, mat.Specular.g, mat.Specular.b);
    shader.setFloat("material.shininess", mat.Shininess);

    // draw mesh
    vao->Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao->Unbind();
}
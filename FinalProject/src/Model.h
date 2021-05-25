#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb/stb_image.h>

#include "Shader.h"
#include "Mesh.h"
#include "MovingBody.h"

class Model : public MovingBody
{
public:
    Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }
    virtual void Draw(Shader& shader);

    virtual void setPosAbsolute(glm::vec3 newPos) override;

    virtual void translateBy(glm::vec3 vector) override;

    virtual void setScaleAbsolute(glm::vec3 newScale) override;

    virtual void scaleBy(glm::vec3 vector) override;

    virtual void setRotationAbsolute(float angle, glm::vec3 rotationAxis) override;

    virtual void rotateBy(float angle, glm::vec3 rotationAxis) override;
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;

    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);

    Material loadMaterial(aiMaterial* mat);
};

#endif
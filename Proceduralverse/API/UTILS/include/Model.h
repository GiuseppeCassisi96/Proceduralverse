#pragma once
#include <string>
#include "ASSIMP/assimp//Importer.hpp"
#include "ASSIMP/assimp/scene.h"
#include "ASSIMP/assimp/postprocess.h"
#include "UTILS/include/Mesh.h"


class Model
{
public:
	std::vector<Mesh> meshes;
	//Here I'm deleting copy constructor 
	Model(const Model& model) = delete;
	//Here I am prohibiting the copy operation going to overloading the copy operator (I delete this operator) 
	Model& operator=(const Model& copy) = delete;

	//I'm using '&&' operator because I manage R-Value 
	Model(Model&& model) = default;
	Model& operator=(Model&& model) noexcept = default;
	Model(const std::string& path);
	void DrawModel();
private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh);
};

#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "Logger.h"

Scene::Scene(std::string path, ResourceManager* resourceManager)
{
	models = std::vector<Entity*>();
	cameras = std::vector<Entity*>();
	sceneFile = resourceManager->getSceneFile(path);
	readSceneFile(sceneFile, resourceManager);
};

Scene::~Scene()
{
};

void Scene::deleteModel(Entity* entity){
	// destroy and delete passed entity from list
};

void Scene::updateEntities()
{
	for each (Entity* camera in cameras)
	{
		camera->update();
	}
	for each (Entity* model in models)
	{
		model->update();
	}
};

std::vector<Entity*> Scene::getModels()
{
	return models;
};

void Scene::addCamera(Entity* camera)
{
	cameras.push_back(camera);
};

void Scene::setActiveCamera(int camera)
{
	activeCamera = camera;
};

Entity* Scene::getActiveCamera()
{
	return cameras[activeCamera];
};

Terrain* Scene::getTerrain()
{
	return terrain;
};

Skybox* Scene::getSkybox()
{
	return skybox;
};

void Scene::readSceneFile(std::vector<std::string>* sceneFile, ResourceManager *resourceManager)
{
	std::string stringTerrainPath = sceneFile->at(0);
	char* terrainPath = new char[stringTerrainPath.length()+1];
	strcpy_s(terrainPath, stringTerrainPath.length()+1, stringTerrainPath.c_str());

	std::string stringTerrainTexturePath = sceneFile->at(1);
	char* terrainTexturePath = new char[stringTerrainTexturePath.length()+1];
	strcpy_s(terrainTexturePath, stringTerrainTexturePath.length()+1, stringTerrainTexturePath.c_str());
	terrain = new Terrain(terrainPath, terrainTexturePath, resourceManager);
	
	std::string stringSkyboxTexturePath = sceneFile->at(2);
	char* skyboxTexturePath = new char[stringSkyboxTexturePath.length()+1];
	strcpy_s(skyboxTexturePath, stringSkyboxTexturePath.length()+1, stringSkyboxTexturePath.c_str());
	skybox = new Skybox(skyboxTexturePath, resourceManager);

	for (unsigned int i = 4; i <= sceneFile->size(); ++i)
	{
		
		std::string infoString = sceneFile->at(i - 1);

		size_t nameComma = infoString.find_first_of(",");
		size_t positionXComma = infoString.find(",", nameComma + 1);
		size_t positionYComma = infoString.find(",", positionXComma + 1);
		size_t positionZComma = infoString.find(",", positionYComma + 1);
		size_t yawComma = infoString.find(",", positionZComma + 1);
		size_t pitchComma = infoString.find(",", yawComma + 1);
		size_t rollComma = infoString.find(",", pitchComma + 1);
		size_t scaleXComma = infoString.find(",", rollComma + 1);
		size_t scaleYComma = infoString.find(",", scaleXComma + 1);
		size_t scaleZComma = infoString.find(",", scaleYComma + 1);

		std::string xResourceName = infoString.substr(0, nameComma);
		std::string positionX = infoString.substr(nameComma + 1, positionXComma-nameComma - 1);
		std::string positionY = infoString.substr(positionXComma + 1, positionYComma - positionXComma - 1);
		std::string positionZ = infoString.substr(positionYComma + 1, positionZComma - positionYComma - 1);
		std::string yaw = infoString.substr(positionZComma + 1, yawComma - positionZComma - 1);
		std::string pitch = infoString.substr(yawComma + 1, pitchComma - yawComma - 1);
		std::string roll = infoString.substr(pitchComma + 1, rollComma - pitchComma - 1);
		std::string scaleX = infoString.substr(rollComma + 1, scaleXComma - rollComma - 1);
		std::string scaleY = infoString.substr(scaleXComma + 1, scaleYComma - scaleXComma - 1);
		std::string scaleZ = infoString.substr(scaleYComma + 1, scaleZComma - scaleYComma - 1);

		char* xResourceNameChar = new char[xResourceName.length() + 1];
		strcpy_s(xResourceNameChar, xResourceName.length() + 1, xResourceName.c_str());

		float positionXFloat = (float)atof(positionX.c_str());
		float positionYFloat = (float)atof(positionY.c_str());
		float positionZFloat = (float)atof(positionZ.c_str());
		float yawFloat = (float)atof(yaw.c_str());
		float pitchFloat = (float)atof(pitch.c_str());
		float rollFloat = (float)atof(roll.c_str());
		float scaleXFloat = (float)atof(scaleX.c_str());
		float pscaleYFloat = (float)atof(scaleY.c_str());
		float scaleZFloat = (float)atof(scaleZ.c_str());

		models.push_back(new Model((XResource*)resourceManager->getResource(xResourceNameChar), positionXFloat, positionYFloat, positionZFloat, yawFloat, pitchFloat, rollFloat, scaleXFloat, pscaleYFloat, scaleZFloat));
	}
};
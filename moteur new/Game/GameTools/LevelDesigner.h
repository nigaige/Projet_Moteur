#pragma once

class LevelDesigner
{
private:

    void addMeshList(std::vector<Mesh*> meImportedList);
    void addShaderList(std::vector<Shader*> shImportedList);
    void addColliderList(std::vector<Collider*> coImportedList);
    void addGoParent(std::vector<GameObject*> goImportedList);


public:
    LevelDesigner();
    ~LevelDesigner();

    void GenerateLevel();
    void CreateSection(std::string sectionPath);

    std::vector<GameObject*> prefabs;

    std::vector<GameObject*> GoList;
    std::vector<Mesh*> MeList;
    std::vector<Shader*> ShList;
    std::vector<Collider*> CoList;
};

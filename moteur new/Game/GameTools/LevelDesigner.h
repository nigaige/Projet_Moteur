#pragma once

class LevelDesigner
{
    void addMeshList(std::vector<Mesh*> meImportedList);
    void addShaderList(std::vector<Shader*> shImportedList);
    void addColliderList(std::vector<Collider*> coImportedList);
    
public:
    LevelDesigner();
    ~LevelDesigner();

    void CreateSection(std::string sectionPath);

    std::vector<GameObject*> GoList;
    std::vector<Mesh*> MeList;
    std::vector<Shader*> ShList;
    std::vector<Collider*> CoList;
};

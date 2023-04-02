#include "../Utils.h"

LevelDesigner::LevelDesigner()
{
    GameObject* previousPrefab = nullptr;

    for (GameObject* prefab : prefabs)
    {
        if (previousPrefab != nullptr) 
        {
            prefab->transform()->posZ(30);
        }else
        {
            prefab->transform()->posZ(10);
        }

        previousPrefab = prefab;
    }
}

LevelDesigner::~LevelDesigner()
{
}

void LevelDesigner::GenerateLevel()
{

    
}

void LevelDesigner::CreateSection(std::string sectionPath)
{
    Parser* testParsing = new Parser();
    testParsing->Filename(sectionPath);
    testParsing->ParseAll();

    //GoList = testParsing->GOlist();
    addGoParent(testParsing->GOlist());
    addMeshList(testParsing->MElist());
    addShaderList(testParsing->SHlist());
    addColliderList(testParsing->COlist());
}

void LevelDesigner::addGoParent(std::vector<GameObject*> goImportedList)
{
    GameObject* prefab = new GameObject();
    
    for(GameObject* go : goImportedList)
    {
        go->parent(prefab);
    }

    prefabs.push_back(prefab);
    GoList = goImportedList;
}

void LevelDesigner::addMeshList(std::vector<Mesh*> meImportedList)
{
    for(Mesh* meInLocList : meImportedList)
    {
        bool flag = true;

        for (Mesh* meInGloList : MeList)
        {
            if(meInLocList == meInGloList) flag = false;
        }

        if(flag) MeList.push_back(meInLocList);
    }
}

void LevelDesigner::addShaderList(std::vector<Shader*> shImportedList)
{
    for(Shader* shInLocList : shImportedList)
    {
        bool flag = true;

        for (Shader* shInGloList : ShList)
        {
            if(shInLocList == shInGloList) flag = false;
        }

        if(flag) ShList.push_back(shInLocList);
    }
}

void LevelDesigner::addColliderList(std::vector<Collider*> coImportedList)
{
    for(Collider* coInLocList : coImportedList)
    {
        bool flag = true;

        for (Collider* coInGloList : CoList)
        {
            if(coInLocList == coInGloList) flag = false;
        }

        if(flag) CoList.push_back(coInLocList);
    }
}

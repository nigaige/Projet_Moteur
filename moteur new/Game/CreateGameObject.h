#pragma once
class CreateGameObject
{

public :

	static GameObject* Wall(Mesh wallMesh, Shader* wallShader, D3DXVECTOR3* position, D3DXVECTOR3* rotation);

	static GameObject* Floor(Mesh floorMesh);


};


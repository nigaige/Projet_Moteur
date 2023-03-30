#include "Utils.h"
#include<sstream>
//using namespace std;
void Parser::ParseAll()
{
	D3DXVECTOR3* Pos = new D3DXVECTOR3();
	D3DXVECTOR3* Sca = new D3DXVECTOR3();
	D3DXVECTOR3* Rot = new D3DXVECTOR3();
	
	std::ifstream File;
	std::string line;
	
	std::string delimiter = " ";
	std::vector<std::string> vect;
	GameObject* currentGO = nullptr;
	Mesh* currentME = nullptr;
	Shader* currentSH = nullptr;
	std::vector<Shader*> SHlist;
	D3DXVECTOR3 vectfloat = D3DXVECTOR3(0.0f,0.0f,0.0f);
	File.open(Filename_);
	
	if (File.is_open())
	{
		while (getline(File, line))
			
			//
			switch (line[0])
			{
			case '-' :
				
				if (line == "--Mesh:")
				{
					Utils::DebugLogMessage("MESH DECLARATION FINDED");
					getline(File, line);
					currentME = new Mesh(line);
					MElist.push_back(currentME);
					break;
				}
				if (line == "--Shader:")
				{
					Utils::DebugLogMessage("SHADER DECLARATION FINDED");
					getline(File, line);
					currentSH = new Shader(line);
					SHlist.push_back(currentSH);
					break;
				}
				if (line == "--Gameobject:")
				{
					Utils::DebugLogMessage("GAMEOBJECT DECLARATION FINDED");
					currentGO = new GameObject();
					GOlist.push_back(currentGO);
					break;
				}
				
				break;
			case 'T':
				Utils::DebugLogMessage("TRANSFORM TOKEN FINDED");
				delimiter = ',';

				//position
					getline(File, line);
					vect = Utils::split(line , delimiter);
					vectfloat= D3DXVECTOR3(std::stof(vect[0]), std::stof(vect[1]), std::stof(vect[2]));
					currentGO->transform()->position(vectfloat);
				
				//Scale
					getline(File, line);
					vect = Utils::split(line, delimiter);
					vectfloat= D3DXVECTOR3(std::stof(vect[0]), std::stof(vect[1]), std::stof(vect[2]));
					currentGO->transform()->scale(vectfloat);
				
				//rotation
					getline(File, line);
					vect = Utils::split(line, delimiter);
					vectfloat = D3DXVECTOR3(std::stof(vect[0]), std::stof(vect[1]), std::stof(vect[2]));
					currentGO->transform()->setARotation(vectfloat[0],vectfloat[1], vectfloat[3]); //todo degtorad ?
					Utils::DebugLogMessage(&line);
					break;

			case 'C':
				Utils::DebugLogMessage("COMPONENT TOKEN FINDED");
				delimiter = ' ';
				vect = Utils::split(line, delimiter);

				if(vect[1] == "Mesh")
				{
					Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A MESH");
					getline(File, line);
					int indexMesh = std::stoi(line);
					currentGO->addComponent(MElist[indexMesh]);
					break;
				}
				if (vect[1] == "Collider")
				{
					bool op;
					delimiter = ',';
					Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A COLLIDER");
					getline(File, line);
					if (line == "Cube")
					{
						Utils::DebugLogMessage("		THIS COLLIDER IS A CUBE");
						getline(File, line);

						vect = Utils::split(line, delimiter);
						D3DXVECTOR3* center = new  D3DXVECTOR3(std::stof(vect[0]), std::stof(vect[1]), std::stof(vect[2]));
						getline(File, line);

						vect = Utils::split(line, delimiter);
						D3DXVECTOR3* size = new  D3DXVECTOR3(std::stof(vect[0]), std::stof(vect[1]), std::stof(vect[2]));
						ColliderCube* cc = new ColliderCube(center, size);


						getline(File, line);
						std::istringstream(line) >> op;
						cc->isTrigger(op);


						currentGO->addComponent(cc);
						COlist.push_back(cc);
						break;
						
					}
					if (line == "Sphere")
					{
						Utils::DebugLogMessage("		THIS COLLIDER IS A SPHERE");
						getline(File, line);

						vect = Utils::split(line, delimiter);
						D3DXVECTOR3* center = new  D3DXVECTOR3(std::stof(vect[0]), std::stof(vect[1]), std::stof(vect[2]));
						
						getline(File, line);
						float radius = std::stof(line);

						ColliderSphere* cs = new ColliderSphere(center, radius);

						
						getline(File, line);
						std::istringstream(line) >> op;
						cs->isTrigger(op);


						currentGO->addComponent(cs);
						COlist.push_back(cs);
						break;
					}
					
					break;
				}
				if (vect[1] == "RigidBody")
				{
					Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A RIGIDBODY");
					delimiter = ',';
					RigidBody* rb = new RigidBody();
					
					getline(File, line);
					vect = Utils::split(line, delimiter);
					
					bool op;
					std::istringstream(vect[0]) >> op;
					rb->isKinematic(op);
					std::istringstream(vect[1]) >> op;
					rb->hasGravity(op);
					currentGO->addComponent(rb);
					break;


				}
				if (vect[1] == "Shader")
				{
					Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A SHADER");
					getline(File, line);
					int indexShader = std::stoi(line);
					getline(File, line);
					int indexMesh = std::stoi(line);
					currentGO->setShaderLinker(MElist[indexMesh], SHlist[indexShader]);
					break;
				}
				
				
				}

	}


	File.close();
}

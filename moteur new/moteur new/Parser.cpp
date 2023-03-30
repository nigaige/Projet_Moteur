#include "Utils.h"
#include<sstream>
Parser::Parser(bool DrawDebug)
{
	DrawDebug_ = DrawDebug;
}

Parser::~Parser()
{
	for (Shader* sh : SHlist_) delete sh;
	for (GameObject* go : GOlist_) delete go;
	for (Mesh* me : MElist_) delete me;
	for (Collider* col : COlist_) delete col;
}


void Parser::ParseAll()
{
	std::ifstream File;
	std::string line;

	std::string delimiter = " ";

	std::vector<std::string> vect;


	GameObject* currentGO = nullptr;
	Mesh* currentME = nullptr;
	Shader* currentSH = nullptr;

	D3DXVECTOR3 vectfloat = D3DXVECTOR3(0.0f,0.0f,0.0f);
	
	File.open(Filename_); // open the map file
	
	if (File.is_open())
	{
		while (getline(File, line))

			switch (line[0])
			{
			case '-' :
				
				if (line == "--Mesh:")
				{
					if(DrawDebug_)
						Utils::DebugLogMessage("MESH DECLARATION FINDED");
					getline(File, line);
					currentME = new Mesh(line);
					MElist_.push_back(currentME);
					break;
				}
				if (line == "--Shader:")
				{
					if (DrawDebug_)
						Utils::DebugLogMessage("SHADER DECLARATION FINDED");
					getline(File, line);
					currentSH = new Shader(line);
					SHlist_.push_back(currentSH);
					break;
				}
				if (line == "--Gameobject:")
				{
					if (DrawDebug_)
						Utils::DebugLogMessage("GAMEOBJECT DECLARATION FINDED");
					currentGO = new GameObject();
					GOlist_.push_back(currentGO);
					break;
				}
				
				break;
			case 'T':
				if (DrawDebug_)
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
					currentGO->transform()->setARotation(Utils::DegToRad(vectfloat[0]),Utils::DegToRad(vectfloat[1]), Utils::DegToRad(vectfloat[2])); //todo degtorad ?
					Utils::DebugLogMessage(&line);
					break;

			case 'C':
				if (DrawDebug_)
					Utils::DebugLogMessage("COMPONENT TOKEN FINDED");
				delimiter = ' ';
				vect = Utils::split(line, delimiter);

				if(vect[1] == "Mesh")
				{
					Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A MESH");
					getline(File, line);
					int indexMesh = std::stoi(line);
					currentGO->addComponent(MElist_[indexMesh]);
					break;
				}
				if (vect[1] == "Collider")
				{
					bool op;
					delimiter = ',';
					if (DrawDebug_)
						Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A COLLIDER");
					getline(File, line);
					if (line == "Cube")
					{
						if (DrawDebug_)
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
						COlist_.push_back(cc);
						break;
						
					}
					if (line == "Sphere")
					{	
						if (DrawDebug_)
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
						COlist_.push_back(cs);
						break;
					}
					
					break;
				}
				if (vect[1] == "RigidBody")
				{
					if (DrawDebug_)
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
					if (DrawDebug_)
						Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A SHADER");
					getline(File, line);
					int indexShader = std::stoi(line);
					getline(File, line);
					int indexMesh = std::stoi(line);
					currentGO->setShaderLinker(currentGO->GetMeshList()[indexMesh], SHlist_[indexShader]);
					break;
				}
				
			default:	
				Utils::DebugLogMessage("UNKNOW TOKEN");
				break;
			}
			
				


	}


	File.close();
}

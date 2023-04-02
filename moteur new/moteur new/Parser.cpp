#include "Utils.h"
#include<sstream>
Parser::Parser(bool DrawDebug)
{
	DrawDebug_ = DrawDebug;
}

Parser::~Parser()
{
}

void Parser::debuging(std::string str)
{
	if (DrawDebug_)	Utils::DebugLogMessage(&str);
}

bool Parser::getNextLine()
{ 
	if (file_.eof()) return notEof_ = false;
	;
	getline(file_, currentLine_);
	return notEof_ = true;
	
}

void Parser::processNewObject(std::vector<GameObject*>* goList, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList)
{
	if (currentLine_[0] != '-') return;
	if (currentLine_ == "--Mesh:") {
		debuging("MESH DECLARATION FINDED");
		processNewMesh(meList);
	}
	else if (currentLine_ == "--Shader:") {
		debuging("SHADER DECLARATION FINDED");
		processNewShader(shList);
	}
	else if (currentLine_ == "--Gameobject:") {
		debuging("GAMEOBJECT DECLARATION FINDED");
		processNewGameobject(goList, meList, coList, shList);
	}
}

void Parser::processNewMesh(std::vector<Mesh*>* meList)
{	//TODO template
	if (getNextLine()) {
		meList->push_back(new Mesh(currentLine_));
	}
}

void Parser::processNewShader(std::vector<Shader*>* shList)
{
	if (getNextLine()) {
		shList->push_back(new Shader(currentLine_));
	}
}

void Parser::processNewGameobject(std::vector<GameObject*>* goList, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList)
{
	goList->push_back(new GameObject());
	processGameobjectComponent(goList, meList, coList, shList);

}

void Parser::processGameobjectComponent(std::vector<GameObject*>* goList, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList)
{
	if (getNextLine()) {
			while (notEof_) {
				switch (currentLine_[0]) {
				case '-'://end of currentgameobject
					processNewObject(goList, meList, coList, shList);
					break;
				case 'T':
					processTransform(goList->back());
					break;
				case 'C':
					processComponent(goList->back(), meList, coList, shList);
					break;
				}
				getNextLine();
			}
		}
}

void Parser::processTransform(GameObject* go)
{
	debuging("TRANSFORM TOKEN FINDED");
	if (!getNextLine())return;//position
	go->transform()->position(parseTransformLine());
	if (!getNextLine())return;//Scale
	go->transform()->scale(parseTransformLine());
	if (!getNextLine())return;//rotation
	go->transform()->addRollPitchYaw(Utils::DegToRad(parseTransformLine().x), Utils::DegToRad(parseTransformLine().y), Utils::DegToRad(parseTransformLine().z));
}
void Parser::processComponent(GameObject* go, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList)
{
	if (currentLine_ == "C: RigidBody") {
		processRigidBody(go);
	}
	else if (currentLine_ == "C: Collider") {
		processCollider(go, coList);
	}
	else if (currentLine_ == "C: Mesh") {
		processMesh(go, meList);
	}
	else if (currentLine_ == "C: Shader") {
		processShader(go, shList);
	}


}

void Parser::processRigidBody(GameObject* go)
{
	Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A RIGIDBODY");
	if (getNextLine()) {
		std::vector<std::string> vect_ = Utils::split(currentLine_, delimiter_);
		go->addComponent(new RigidBody());
		go->rb()->isKinematic(vect_[0] == "1");
		go->rb()->hasGravity(vect_[1] == "1");
	}
}

void Parser::processCollider(GameObject* go, std::vector<Collider*>* coList)
{
	Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A COLLIDER");
	if (!getNextLine()) return;
	if (currentLine_ == "Cube") {
		processColliderCube(coList);
	}
	else if (currentLine_ == "Sphere") {
		processColliderSphere(coList);
	}
	else {
		throw "UNKNOWN COLLIDER TYPE";
	}
	if (!getNextLine())	throw "UNKNOWN COLLIDER TYPE";//trigger
	coList->back()->isTrigger(currentLine_ == "1");

	go->addComponent(coList->back());
}

void Parser::processColliderCube(std::vector<Collider*>* coList)
{
	Utils::DebugLogMessage("		THIS COLLIDER IS A CUBE");
	if (!getNextLine())	throw "UNKNOWN COLLIDER TYPE";//center 
	D3DXVECTOR3 center = parseTransformLine();
	if (!getNextLine())	throw "UNKNOWN COLLIDER TYPE";//size
	D3DXVECTOR3 size = parseTransformLine();
	coList->push_back(new ColliderCube(&center, &size));
}

void Parser::processColliderSphere(std::vector<Collider*>* coList)
{
	Utils::DebugLogMessage("		THIS COLLIDER IS A SPHERE");
	if (!getNextLine())	throw "UNKNOWN COLLIDER TYPE";//center 
	D3DXVECTOR3 center = parseTransformLine();
	if (!getNextLine())	throw "UNKNOWN COLLIDER TYPE";//radius 
	coList->push_back(new ColliderSphere(&center, std::stof(currentLine_)));
}

void Parser::processMesh(GameObject* go, std::vector<Mesh*>* meList)
{
	Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A MESH");
	if (!getNextLine())	throw "UNKNOWN MESH";
	go->addComponent((*meList)[std::stoi(currentLine_)]);
}

void Parser::processShader(GameObject* go, std::vector<Shader*>* shList)
{
	Utils::DebugLogMessage("	THIS COMPONENT TOKEN IS A SHADER");
	if (!getNextLine())	throw "UNKNOWN SHADER";
	int indexShader = std::stoi(currentLine_);
	if (!getNextLine())	throw "UNKNOWN MESH";
	int indexMesh = std::stoi(currentLine_);
	go->setShaderLinker(go->GetMeshList()[indexMesh], (*shList)[indexShader]);

}

D3DXVECTOR3 Parser::parseTransformLine()
{
	std::vector<std::string> vect_ = Utils::split(currentLine_, delimiter_);
	if (vect_.size() != 3) throw "bad transform value";
	return D3DXVECTOR3(std::stof(vect_[0]), std::stof(vect_[1]), std::stof(vect_[2]));	
}



void Parser::ParseAll(std::vector<GameObject*>* goList, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList)
{
	if (&goList == NULL || &meList == NULL || &coList == NULL || &shList == NULL)
		throw "No pointor";

	
	file_.open(Filename_); // open the map file
	
	if (file_.is_open())
	{
		notEof_ = true;
		while (notEof_) {
			notEof_ = getNextLine();
			processNewObject(goList, meList, coList, shList);

		}

	}

	file_.close();
}

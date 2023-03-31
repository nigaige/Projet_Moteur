#pragma once
class Parser
{
private :
	std::string Filename_;

	bool DrawDebug_ = true;
	bool notEof_ = true;
	std::ifstream file_;
	std::string currentLine_;
	const std::string delimiter_ = ",";


	void debuging(std::string str);

	bool getNextLine();

	void processNewObject(std::vector<GameObject*>* goList, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList);

	void processNewMesh(std::vector<Mesh*>* meList);
	void processNewShader(std::vector<Shader*>* shList);
	void processNewGameobject(std::vector<GameObject*>* goList, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList);

	void processGameobjectComponent(std::vector<GameObject*>* goList, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList);
	void processTransform(GameObject* go);
	void processComponent(GameObject* go, std::vector<Mesh*>* meList, std::vector<Collider*>* coList, std::vector<Shader*>* shList);
	void processRigidBody(GameObject* go);
	void processCollider(GameObject* go, std::vector<Collider*>* coList);
	void processColliderCube(std::vector<Collider*>* coList);
	void processColliderSphere(std::vector<Collider*>* coList);
	void processMesh(GameObject* go, std::vector<Mesh*>* meList);
	void processShader(GameObject* go, std::vector<Shader*>* shList);

	D3DXVECTOR3 parseTransformLine();



public :
	Parser(bool DrawDebug = true);
	~Parser();

	// GETTER / SETTER
	void Filename(std::string path)		{ Filename_ = path; }
	std::string Filename()				{ return Filename_; }


	void ParseAll(std::vector<GameObject*>*, std::vector<Mesh*>*, std::vector<Collider*>*, std::vector<Shader*>*);
};


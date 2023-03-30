#pragma once
class Parser
{
private :
	std::string Filename_;
	std::vector<Shader*> SHlist_;
	std::vector<GameObject*> GOlist_;
	std::vector<Mesh*> MElist_;
	std::vector<Collider*> COlist_;

public :
	void Filename(std::string path) { Filename_ = path; }
	std::string Filename()			{ return Filename_; }



	std::vector<Shader*> SHlist() { return SHlist_; }
	std::vector<GameObject*> GOlist() { return GOlist_; }
	std::vector<Mesh*> MElist() { return MElist_; }
	std::vector<Collider*> COlist() { return COlist_; }



	void ParseAll();
};


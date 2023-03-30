#pragma once
class Parser
{
private :
	std::string Filename_;
	//std::map<std::string,  > typemap;
public :
	void Filename(std::string path) { Filename_ = path; }
	std::string Filename()			{ return Filename_; }
	std::vector<GameObject*> GOlist;
	std::vector<Mesh*> MElist;
	std::vector<Collider*> COlist;

	void ParseAll();
};


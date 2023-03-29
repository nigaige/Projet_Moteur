#pragma once
class Parser
{
private :
	std::string Filename_;
public :
	void Filename(std::string path) { Filename_ = path; }
	std::string Filename()			{ return Filename_; }


	void ParseAll();
};


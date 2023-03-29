#include "Utils.h"
//using namespace std;
void Parser::ParseAll()
{
	D3DXVECTOR3* Pos = new D3DXVECTOR3();
	D3DXVECTOR3* Sca = new D3DXVECTOR3();
	D3DXVECTOR3* Rot = new D3DXVECTOR3();
	
	std::ifstream File;
	std::string line;
	char token = ' ';
	char ah = ' ';

	File.open(Filename_);
	
	if (File.is_open())
	{
		while (getline(File, line))

			//
			switch (line[0])
			{
			case '-' :
				Utils::DebugLogMessage("GAMEOBJECT");
				break;
			case 'T':
				Utils::DebugLogMessage("Transform find");
				
					getline(File, line);
					
					getline(File, line);
					getline(File, line);
					Utils::DebugLogMessage(&line);
				
				
		}
	}


	File.close();
}

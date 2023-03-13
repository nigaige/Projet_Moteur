#include "Shader.h"

Shader::Shader() 
{

}

Shader::~Shader()
{
}

void Shader::LoadShader(LPD3DXBUFFER shaderContent_)
{
}

void Shader::LoadShader(std::string* shaderPath)
{

	LPCSTR text = &shaderPath;
	/*LPTSTR text = L"";
	HWND hEdit = GetDlgItem(hWnd, EDIT_MAIN);
	int len = GetWindowTextLengthA(hEdit);
	std::vector<CHAR> text(len + 1, 0);
	GetWindowTextA(hEdit, &text[0], len);
	ofstream file;
	file.open("filePathName");
	file << &text[0];
	file.close();
	FILE* f;
	int a = 78, i, t1[6];
	double b = 9.87;
	char c = 'W', t2[10];

	auto my_path = std::experimental::filesystem::path(R"(C:\mon fichier.exe)").concat;*/
}


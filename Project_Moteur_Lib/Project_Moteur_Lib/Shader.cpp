#include "Shader.h"

Shader::Shader(LPDIRECT3DDEVICE9 d3ddev)
{
    _d3ddev = d3ddev;
}

Shader::~Shader()
{
}

void Shader::LoadShader(const LPD3DXBUFFER* shaderContent_)
{
    IDirect3DVertexShader9** ppShader;
    _d3ddev->CreateVertexShader((DWORD*)shaderContent_, ppShader);
}

void Shader::LoadShader(std::string* shaderPath)
{
    ID3DXBuffer* listing_f = NULL;
    ID3DXBuffer* listing_v = NULL;
    ID3DXBuffer* code_f = NULL;
    ID3DXBuffer* code_v = NULL;
    LPD3DXCONSTANTTABLE* ppConstantTable_OUT = NULL;
    LPD3DXBUFFER shaderContent_ = NULL;

    std::ifstream file;

    file.open("C:/Users/asabi/Desktop/text.hlsl", std::ios_base::binary);
    //file.open(*shaderPath, std::ios_base::binary);

    if (!file)
    {
        Utils::DebugLogMessage("Error : Can't open the file");
    }
    else
    {
        file.seekg(0, file.end);
        int length = file.tellg();
        file.seekg(0, file.beg);
        char* _Str = new char[length + 1];
        file.read(_Str, length);
        _Str[length] = 0;

        HRESULT Buffer = D3DXCompileShader((LPCSTR)_Str, strlen(_Str), NULL, NULL, "main_vertex", "vs_3_0", 0, &code_v, &listing_v, ppConstantTable_OUT);

        LoadShader((LPD3DXBUFFER)Buffer);

        Utils::DebugLogMessage(_Str);
    }

    //Closing the file


	//LPCSTR text = &shaderPath;
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
	//std::string content = std::experimental::filesystem::path(R"(C:\mon fichier.exe)").;


}


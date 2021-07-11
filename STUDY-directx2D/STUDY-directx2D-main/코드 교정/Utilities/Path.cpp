#include "stdafx.h"
#include "Path.h"
#include <string.h>
#include "String.h"

//std::wstring은 std::string의 wchar_t(unsigned short) 버전
//영어 이외의 언어를 표현할 때 사용 가능

bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWString(path)); //wstring으로 변환하여 파일 찾기 (파일 존재할 때 true 리턴)
}

bool Path::ExistFile(wstring path) 
{
	DWORD fileValue = GetFileAttributes(path.c_str()); //DWORD: double word (word=CPU가 처리할 수 있는 한 단위)
	//GetFileAttributes: 지정한 파일이나 폴더의 속성 확인

	return fileValue < 0xFFFFFFFF; //파일이 존재할 때 true 리턴
}

bool Path::ExistDirectory(string path)
{
	return ExistDirectory(String::ToWString(path)); //wstring으로 변환하여 디렉터리 찾기 (디렉터리가 존재할 때 true 리턴)
}

bool Path::ExistDirectory(wstring path)
{
	DWORD attribute = GetFileAttributes(path.c_str());

	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES && //파일/폴더가 없는 경우 GetFileAttributes는 INVALID_FILE_ATTRIBUTES 리턴
		(attribute & FILE_ATTRIBUTE_DIRECTORY)); //해당 attribute가 디렉터리에 관한 것일 때 temp==true

	return temp == TRUE; //찾고자하는 디렉터리가 존재할 때 true 리턴
}

string Path::Combine(string path1, string path2)
{
	return path1 + path2; //string형 경로 2개 합치기
}

wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2; //wstring형 경로 2개 합치기
}

string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp; //vector형으로 저장된 여러 string형 경로들 합치기
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp; //vector형으로 저장된 여러 wstring형 경로들 합치기
}

string Path::GetDirectoryName(string path)
{
	String::Replace(&path, "\\", "/"); //경로 상에 있는 모든 "\\"에 대해 "/"로 변경
	size_t index = path.find_last_of('/'); //마지막 "/"의 위치 index에 저장

	return path.substr(0, index + 1); //디렉터리 경로 리턴
}

wstring Path::GetDirectoryName(wstring path) //string과 동일한 작업 수행
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

string Path::GetExtension(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());; //확장자 리턴
}

wstring Path::GetExtension(wstring path) //string과 동일한 작업 수행
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());;
}

string Path::GetFileName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length()); //파일 이름 리턴 (확장자 포함)
}

wstring Path::GetFileName(wstring path) //string과 동일한 작업 수행
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index); //뒤에 확장자명 제거하고 파일명만 리턴
}

wstring Path::GetFileNameWithoutExtension(wstring path) //string과 동일한 작업 수행
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}


const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::BinModelFilter = L"Binary Model\0*.model";
const WCHAR* Path::FbxModelFilter = L"Fbx Model\0*.fbx;*.obj\0";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";

void Path::OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{ //OpenFileDialog: 컴퓨터에 있는 하나 이상의 파일을 열게 해줌
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = L"불러오기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");

			func(loadName);
		}
	}
}

void Path::SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{ //SaveFileDialog: 파일 저장
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = L"저장하기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");

			func(loadName);
		}
	}
}

void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{ //wstring에 대해서 파일 탐색 수행
	vector<wstring> wFiles;
	wstring wPath = String::ToWString(path);
	wstring wFilter = String::ToWString(filter);

	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	for (wstring str : wFiles)
		files->push_back(String::ToString(str));
}

//path : ../Temp/
//filter : *.txt
void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{ //path에 전달받은 경로를 통해 파일을 찾음
	wstring file = path + filter;

	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(file.c_str(), &findData);

	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					wstring folder = path + wstring(findData.cFileName) + L"/";

					GetFiles(files, folder, filter, bFindSubFolder);
				}
			}
			else
			{
				wstring fileName = path + wstring(findData.cFileName);
				files->push_back(fileName);
			}
		} while (FindNextFile(handle, &findData));

		FindClose(handle);
	}
}

void Path::CreateFolder(string path)
{
	CreateFolder(String::ToWString(path)); //wstring으로 변환해서 작업 수행
}

void Path::CreateFolder(wstring path)
{
	if (ExistDirectory(path) == false) //기존에 존재하는 디렉터리가 없을 때
		CreateDirectory(path.c_str(), NULL); //디렉터리 생성
}

void Path::CreateFolders(string path) //상위 디렉터리가 존재하지 않을 때 상위 디렉터리부터 현재 디렉터리까지 한꺼번에 만들어주기
{
	CreateFolders(String::ToWString(path)); //wstring으로 변환해서 작업 수행
}

void Path::CreateFolders(wstring path)
{
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;
	String::SplitString(&folders, path, L"/"); //각각의 디렉터리로 나눔

	wstring temp = L"";
	for (wstring folder : folders)
	{
		temp += folder + L"/"; //알맞은 경로에 디렉터리가 위치하도록 temp에 경로 추가

		CreateFolder(temp); //존재하지 않는 상위 디렉터리에 대해 새로운 디렉터리 생성
	}
}

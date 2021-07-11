#include "stdafx.h"
#include "String.h"

//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ� �ڸ���
///@param orgin : ���� ���ڿ�
///@param tok : �ڸ� ������ �Ǵ� ���ڿ�
///@return �Ϸ�� ���ڿ� �迭
//////////////////////////////////////////////////////////////////////////

//std::wstring�� std::string�� wchar_t(unsigned short) ����
//���� �̿��� �� ǥ���� �� ��� ����

void String::SplitString(vector<string>* result, string origin, string tok) //string�� �� ����
{
	result->clear(); //vector�� �޼ҵ� clear: vector�� ����� ���鸸 �����ϰ� �Ҵ�� �޸𸮴� �������� ����

	int cutAt = 0; //�ڸ� ��ġs
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos) //tok�� ��ġ �߰� (string::npos-ã�� ���ڰ� ���� �� ���ϵǴ� ��)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0����ũ��
			result->push_back(origin.substr(0, cutAt)); //�ڸ��� ��ġ�� �������� �պκп� �ش��ϴ� ���ڿ��� result�� ����

		origin = origin.substr(cutAt + 1); //origin ���ڿ����� ������ �޺κ� ���ڿ� ����	
	}

	if (origin.length() > 0) //�ڸ��� ���� ���� �ִٸ� (tok ���� ������ ���� ������ ���ڿ�)
		result->push_back(origin.substr(0, cutAt)); //������ ���ڿ� ����
}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok) //wstring�� ���ؼ��� string�� ���� ��� ����
{
	result->clear();

	int cutAt = 0; //�ڸ� ��ġs
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0����ũ��
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� ���� ���� �ִٸ�
		result->push_back(origin.substr(0, cutAt));
}


//////////////////////////////////////////////////////////////////////////
///@brief ���� ���ڿ��� ������ üũ
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : ���� �񱳹��ڿ�
//////////////////////////////////////////////////////////////////////////
bool String::StartsWith(string str, string comp) //string�� ���ؼ� ����
{
	wstring::size_type index = str.find(comp); //string::size_type - find �Լ��� �� �� ã�����ϴ� ���ڿ��� ���� ��ġ�� npos ����
	if (index != wstring::npos && (int)index == 0) //str ���ڿ��� comp ���ڿ��� ������ ��(comp�� str�� �� �տ� ��ġ)
		return true; //true ����

	return false; //comp ���ڿ��� str ���ڿ��� �� �տ� ��ġ���� ���� �� false ����
}

bool String::StartsWith(wstring str, wstring comp) //wstring�� ���ؼ� string�� ���� �����ϰ� ����
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////
///@brief �ش� ���ڿ��� ���ԵǾ� �ִ���
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : �񱳹��ڿ�
//////////////////////////////////////////////////////////////////////////
bool String::Contain(string str, string comp) 
{
	size_t found = str.find(comp); //str���� comp ���ڿ��� ã�� �ش� ��ġ�� found�� ����

	return found != wstring::npos; //ã�����ϴ� ���ڿ��� �����ϸ� true ����
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}


//////////////////////////////////////////////////////////////////////////
///@brief �ش� ���ڿ����� comp ���ڸ� rep�� ����
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : �񱳹��ڿ�
///@param rep : �ٲܹ��ڿ�
//////////////////////////////////////////////////////////////////////////
void String::Replace(string * str, string comp, string rep)
{
	string temp = *str; //���� ���ڿ��� temp�� ����

	size_t start_pos = 0; //���� �ε��� 0
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos) //�ٲٷ��� ���ڿ� comp�� �߰����� ��
	{
		temp.replace(start_pos, comp.length(), rep); //temp�� �ִ� comp ���ڿ��� rep ���ڿ��� �ٲ�
		start_pos += rep.length(); //�� ���� comp ���ڿ��� ���� rep ��ġ ���Ŀ��� ã��
	}

	*str = temp; //�ٲ� ���ڿ��� str�� ����
}

void String::Replace(wstring* str, wstring comp, wstring rep) //string�� ���� �����ϰ� �۾�
{
	wstring temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief string���� wstring������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
wstring String::ToWString(string value) //string������ wstring������ ��ȯ
{
	wstring temp = L""; //wstring�� ������ L"~~"�� ����
	temp.assign(value.begin(), value.end()); //.assign() - ���ڿ� �Ҵ�

	return temp; //wstring���� ��ȯ�� �� ����
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring���� string������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
string String::ToString(wstring value) //wstring������ string������ ��ȯ
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "String.h"

//////////////////////////////////////////////////////////////////////////
///@brief 문자열 자르기
///@param orgin : 원본 문자열
///@param tok : 자를 기준이 되는 문자열
///@return 완료된 문자열 배열
//////////////////////////////////////////////////////////////////////////

//std::wstring은 std::string의 wchar_t(unsigned short) 버전
//영어 이외의 언어를 표현할 때 사용 가능

void String::SplitString(vector<string>* result, string origin, string tok) //string일 때 수행
{
	result->clear(); //vector의 메소드 clear: vector에 저장된 값들만 삭제하고 할당된 메모리는 삭제하지 않음

	int cutAt = 0; //자를 위치s
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos) //tok의 위치 발견 (string::npos-찾는 문자가 없을 때 리턴되는 값)
	{
		if (cutAt > 0) //자르는 위치가 0보다크면
			result->push_back(origin.substr(0, cutAt)); //자르는 위치를 기준으로 앞부분에 해당하는 문자열을 result에 저장

		origin = origin.substr(cutAt + 1); //origin 문자열에는 나머지 뒷부분 문자열 저장	
	}

	if (origin.length() > 0) //자르고도 남은 것이 있다면 (tok 값을 가지지 않은 나머지 문자열)
		result->push_back(origin.substr(0, cutAt)); //나머지 문자열 저장
}

void String::SplitString(vector<wstring>* result, wstring origin, wstring tok) //wstring에 대해서도 string과 같은 방식 수행
{
	result->clear();

	int cutAt = 0; //자를 위치s
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다크면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은 것이 있다면
		result->push_back(origin.substr(0, cutAt));
}


//////////////////////////////////////////////////////////////////////////
///@brief 시작 문자열이 같은지 체크
///@param str : 체크하려는 문자열
///@param comp : 시작 비교문자열
//////////////////////////////////////////////////////////////////////////
bool String::StartsWith(string str, string comp) //string에 대해서 수행
{
	wstring::size_type index = str.find(comp); //string::size_type - find 함수를 쓸 때 찾고자하는 문자열의 시작 위치나 npos 저장
	if (index != wstring::npos && (int)index == 0) //str 문자열이 comp 문자열로 시작할 때(comp가 str의 맨 앞에 위치)
		return true; //true 리턴

	return false; //comp 문자열이 str 문자열의 맨 앞에 위치하지 않을 때 false 리턴
}

bool String::StartsWith(wstring str, wstring comp) //wstring에 대해서 string일 때와 동일하게 수행
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////
///@brief 해당 문자열이 포함되어 있는지
///@param str : 체크하려는 문자열
///@param comp : 비교문자열
//////////////////////////////////////////////////////////////////////////
bool String::Contain(string str, string comp) 
{
	size_t found = str.find(comp); //str에서 comp 문자열을 찾아 해당 위치를 found에 저장

	return found != wstring::npos; //찾고자하는 문자열이 존재하면 true 리턴
}

bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}


//////////////////////////////////////////////////////////////////////////
///@brief 해당 문자열에서 comp 문자를 rep로 변경
///@param str : 체크하려는 문자열
///@param comp : 비교문자열
///@param rep : 바꿀문자열
//////////////////////////////////////////////////////////////////////////
void String::Replace(string * str, string comp, string rep)
{
	string temp = *str; //원본 문자열을 temp에 저장

	size_t start_pos = 0; //시작 인덱스 0
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos) //바꾸려는 문자열 comp를 발견했을 때
	{
		temp.replace(start_pos, comp.length(), rep); //temp에 있는 comp 문자열을 rep 문자열로 바꿈
		start_pos += rep.length(); //그 다음 comp 문자열을 현재 rep 위치 이후에서 찾음
	}

	*str = temp; //바꾼 문자열을 str에 저장
}

void String::Replace(wstring* str, wstring comp, wstring rep) //string일 때와 동일하게 작업
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
///@brief string형을 wstring형으로 변경
///@param value : 변환할 문자열
///@return 변환 완료 문자열
//////////////////////////////////////////////////////////////////////////
wstring String::ToWString(string value) //string형에서 wstring형으로 변환
{
	wstring temp = L""; //wstring형 변수는 L"~~"로 선언
	temp.assign(value.begin(), value.end()); //.assign() - 문자열 할당

	return temp; //wstring으로 변환한 것 리턴
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring형을 string형으로 변경
///@param value : 변환할 문자열
///@return 변환 완료 문자열
//////////////////////////////////////////////////////////////////////////
string String::ToString(wstring value) //wstring형에서 string형으로 변환
{
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}
//////////////////////////////////////////////////////////////////////////
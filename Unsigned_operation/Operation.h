#pragma once

#include <vector>
#include <string>

void reverse(std::string& s);

class Operation
{

private:
	std::vector<__int8> v_Num;
	std::vector<__int8> v_OtherNum; // 값을 실제로 계산할 벡터 최대 2자리수 계산만 할 것이기 때문에 숫자의 크기가 커지면 일반 int형은 손해다

	int i_Size = 0; // 두 벡터중 작은 값의 크기를 저장할 변수
	bool negativeNum = false; // 음수면 양수로 바꿔버림
	std::string m_Str_Num = " "; // 입력받은 값을 저장 할 변수
public:
	
	Operation(int a) { a < 0 ? negativeNum = true : negativeNum;	m_Str_Num = std::to_string(a); } // 입력받은 타입을 string형식으로 변환하여 저장하고 음수면 negativeNum = true
	Operation(unsigned int a) { a < 0 ? negativeNum = true : negativeNum;	m_Str_Num = std::to_string(a); }
	Operation(short a) { a < 0 ? negativeNum = true : negativeNum;	m_Str_Num = std::to_string(a); }
	Operation(unsigned short a) { a < 0 ? negativeNum = true : negativeNum;	m_Str_Num = std::to_string(a); }
	Operation(long a) { a < 0 ? negativeNum = true : negativeNum;	m_Str_Num = std::to_string(a); }
	Operation(unsigned long a) { a < 0 ? negativeNum = true : negativeNum;	m_Str_Num = std::to_string(a); }
	Operation(long long a) { a < 0 ? negativeNum = true : negativeNum;	m_Str_Num = std::to_string(a); }
	Operation(unsigned long long a) { a < 0 ? negativeNum = true : negativeNum;	m_Str_Num = std::to_string(a); }
	Operation(std::string a) { m_Str_Num = a; }


	void ReadyToCalculation(const Operation& other); // 계산하기 위해 준비하는 함수

	std::string operator +(const Operation& other);	
	std::string operator *(const Operation& other);
	bool operator !=(const Operation& other) { return this->m_Str_Num != other.m_Str_Num; }
	bool operator ==(const Operation& other) { return this->m_Str_Num == other.m_Str_Num; }
};

inline void Operation::ReadyToCalculation(const Operation& other)
{
	bool b_biggerValue = false; // 더 큰 값을 판별할 변수 this 값을 기준으로 계산함

	b_biggerValue = this->m_Str_Num.size() > other.m_Str_Num.size() ? true : false; // 서로 더할 다른 값보다 자리수가 많다면 true
	i_Size = b_biggerValue ? this->m_Str_Num.size() - negativeNum : other.m_Str_Num.size() -  other.negativeNum; // 비교하여 나온 값중 큰 값을 size로 지정

	// 첫 번째 자리부터 역순으로 벡터에 한자리씩 넣는다
	for (int i = this->m_Str_Num.size() - 1; i >= 0 + negativeNum; i--)
	{
		v_Num.push_back(stoi(this->m_Str_Num.substr(i, 1))); // 맨 첫번째 자리부터 맨 앞자리까지 하나씩 끊어서 int형으로 벡터에 저장
	}

	for (int i = other.m_Str_Num.size() - 1; i >= 0 + other.negativeNum; i--)
	{
			v_OtherNum.push_back(stoi(other.m_Str_Num.substr(i, 1))); // 맨 첫번째 자리부터 맨 앞자리까지 하나씩 끊어서 int형으로 벡터에 저장
	}

	// 벡터의 길이를 0을 채워 넣어서 맞춰준다
	for (int i = 0; i < i_Size; i++)
	{
		if (i_Size != v_Num.size() - negativeNum && i_Size - i != 0) v_Num.push_back(0);
		else if (i_Size != v_OtherNum.size() - other.negativeNum && i_Size - i != 0) v_OtherNum.push_back(0);
		else break;
	}
}

std::string Operation::operator+(const Operation& other)
{
	ReadyToCalculation(other);

	std::string m_Str_Result; // 연산 결과 값을 저장 할 변수
	__int8 sum = 0;
	__int8 carry = 0; // 10이 넘어가는 경우 다음 자리수에 저장할 변수

	// 각 자리수를 더한다.
	for (int i = 0; i < i_Size; i++)
	{
		sum = ((v_Num[i] + v_OtherNum[i] + carry) % 10);
		m_Str_Result += std::to_string(sum);
		carry = (v_Num[i] + v_OtherNum[i] + carry) / 10;
	}

	m_Str_Result = carry == 0 ? m_Str_Result : m_Str_Result + (carry += '0'); // to_string이 식에서 적용이 안되기 때문에 아스키 코드로 carry값을 구한다. carry의 값을 더해준다

	reverse(m_Str_Result); // result는 거꾸로 되어 있는 상태이기 때문에 뒤집어 준다
	return m_Str_Result;
}

std::string Operation::operator*(const Operation& other)
{
	ReadyToCalculation(other);

	std::string m_Str_Result; // 연산 결과 값을 저장 할 변수
	__int8 sum = 0;
	__int8 carry = 0; // 10이 넘어가는 경우 다음 자리수에 저장할 변수

	// 덧셈과 달리 1회에 거쳐 계산이 끝나지 않기 때문에 저장해 놓을 벡터가 필요하다. carry를 더할 것이지만 무한대에 가까운 수가 아닌이상 __int16(32000)정도면 충분하다.
	std::vector<__int16> v_temp((i_Size) * 2, 0); // 곱셈의 최대 자리수는 곱셈에 필요한 큰 값의 자릿수 * 2이다. -> 99999 * 99999 = 10자리이다.


	for (int i = 0; i < i_Size; i++)
	{
		// 곱셈이기 때문에 자릿수 덧셈 규칙이 달라진다. 1의 자리부터 시작해서 곱해서 더했으면 다음번엔 10의 자리에 더하기 시작해야한다.
		int j = 0;
		carry = 0;
		while (true)
		{
			if (j == i_Size)
			{
				v_temp[i + j] += carry;
				break;
			}
			sum = (v_Num[j] * v_OtherNum[i]) % 10; // 어차피 한자리수만 곱하기 때문에 3자리 넘어갈 일이 없다 각 자리를 곱한것의 첫째자리 가져옴
			v_temp[i + j] += sum + carry; // 각 자리의 첫째 자리와 올림값을 더한다.
			carry = (v_Num[j] * v_OtherNum[i]) / 10; // v_Num의 첫째자리 부터 마지막 자리까지 차례대로 곱한다.
			j++;
		}
	}
	
	carry = 0;
	// 나온 값을 1의 자리 수로 계산하고 string으로 바꿔서 넣는다.
	for (int i = 0; i < v_temp.size(); i++)
	{
		sum = (v_temp[i] + carry) % 10;
		m_Str_Result += std::to_string(sum);
		carry = (v_temp[i] + carry) / 10;
	}

	// 뒤집기전에 맨 뒤부터 0을 탐색하고 0이면 NULL로 바꿔버린다.
	for (int i = m_Str_Result.size()- 1; i >= 0; i--)
	{
		if (m_Str_Result[i] == '0')
		{
			m_Str_Result[i] = NULL;
		}
		else break;
	}

	reverse(m_Str_Result); // result는 거꾸로 되어 있는 상태이기 때문에 뒤집어 준다
	return m_Str_Result;
}

// string 반전 표준 알고리즘
void reverse(std::string& s)
{
	reverse(s.begin(), s.end());
}
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Test
{
	string question;
	string variants[4];
	int rightAnsw;//правильный ответ
	int cost;//стоимость правильного ответа на вопрос
	int GetInt(int left, int right);
public:
	Test() {}

	int Cost()
	{
		return cost;
	}

	void CreateTest();
	int RunTest();//возвращает количество баллов за правильный ответ или 0

	friend ostream& operator << (ostream& out, Test& test)
	{
		out << test.question << endl;
		for (size_t i = 0; i < 4; i++)
		{
			out << test.variants[i] << endl;
		}
		out << test.rightAnsw << endl;
		out << test.cost << endl;		
		return out;
	}

	friend istream& operator >> (istream& in, Test& test)
	{
		string temp = "0";
		getline(in, test.question);
		for (size_t i = 0; i < 4; i++)
		{
			getline(in, test.variants[i]);
		}
		getline(in, temp);
		test.rightAnsw = stoi(temp);
		getline(in, temp);
		test.cost = stoi(temp);		
		return in;
	}
};


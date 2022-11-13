#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Expence//Трата
{
	string _name;	
	string _category;	
	float _value;
	int _date[3];//формат год, месяц, день
	int _id;//нужен для сортировки трат в кошельке по дате
	
public:
	Expence(string nameP, float valueP, string categoryP, int dateP[3]) : _name{ nameP }, _value{ valueP }, _category{ categoryP }
	{
		
		for (int i = 0; i < 3; i++)
		{
			_date[i] = dateP[i];
		}
		_id = _date[0] * 10000 + _date[1] * 100 + _date[2];
	}	

	Expence() :Expence("", 0.0f, "", new int [3] {0, 0, 0}) {}
	
	~Expence() {}

	int id()
	{
		return _id;
	}

	float value()
	{
		return _value;
	}

	void value(float newValue)
	{
		_value = newValue;
	}
	
	string category()
	{
		return _category;
	}

	int date(int index)
	{
		return _date[index];
	}	

	friend ostream& operator << (ostream& out, const Expence& exp)
	{
		out << exp._id <<" ";
		for (int i = 0; i < 3; i++)
		{
			out << exp._date[i] << " ";
		}
		out << exp._value << endl << exp._name << endl << exp._category << endl;
		return out;
	}

	friend istream& operator >> (istream& in, Expence& exp)
	{
		in >> exp._id;

		for (int i = 0; i < 3; i++)
		{
			in >> exp._date[i];
		}
		in >> exp._value;
		getline(in, exp._name);
		getline(in, exp._name);
		getline(in, exp._category);		
		return in;
	}

	void Print();
};


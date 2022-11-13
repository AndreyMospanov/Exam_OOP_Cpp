#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Expence.h"


class Wallet//Кошелёк (банковская карта)
{
	string name;
	string currency;	
	std::multimap <int, Expence> expences;
	float value;	
	vector<float> catValues;
	vector<string> categories;	

public:

	Wallet(string nameP, string currencyP, int catSize, string* categoriesP,  float value = 0.0f ) :name{ nameP }, currency{ currencyP }, value{ 0.0f }
	{
		for (int i = 0; i < catSize; i++)
		{
			catValues.push_back(0.0f);
			categories.push_back(categoriesP[i]);
		}
	}	

	Wallet(int catSize, string* categoriesP) : Wallet("default", "rub", catSize, categoriesP) {}
		
	string Name()
	{
		return name;
	}

	void Name(string nameP)
	{
		name = nameP;
	}

	string Currency()
	{
		return currency;
	}

	void Currency(string curr)
	{
		currency = curr;
	}

	int Count()
	{
		return expences.size();
	}

	float Value()
	{
		return value;
	}

	float CatValues(int index)
	{
		return catValues[index];
	}

	string Categories(int index)
	{
		return categories[index];
	}
	
	Expence& operator [] (int index)
	{
		multimap <int, Expence>::iterator it = expences.begin();
		advance(it, index);// присваиваем итератору нужный индекс
		try
		{
			if (index < 0 || index > expences.size())
				throw index;

			return it->second;
		}
		catch (const std::exception&) {}
		catch(int)
		{
			cerr << "Ошибка. Число за пределами допустимых значений!\n";
		}
	}
	void Add(Expence exp);

	void Delete(int index);

	void ShowExpences();
	
	void ShowExpences(int index, int year, int selector);
	
};
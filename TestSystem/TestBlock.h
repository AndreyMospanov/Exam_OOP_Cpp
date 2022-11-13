#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"Test.h"
using namespace std;

class TestBlock
{
	string name;
	vector<Test> tests;
	vector<string> score;
public:
	TestBlock(string nameP, vector<Test> testP, vector<string> scoreP) :name{ nameP }
	{
		for (size_t i = 0; i < testP.size(); i++)
		{
			tests.push_back(testP[i]);
		}
		for (size_t i = 0; i < score.size(); i++)
		{
			score.push_back(score[i]);
		}
	}

	TestBlock(): name{ "" } {}

	void CreateTestBlock(bool createOnly = true);

	string RunTestBlock(string username);

	string Name()
	{
		return name;
	}
	
	Test& operator [] (int index)
	{
		return tests[index];
	}

	string GetScore()
	{
		string temp;
		for (size_t i = 0; i < score.size(); i++)
		{
			temp += score[i] + "\n";
		}
		return temp;
	}

	friend ostream& operator << (ostream& out, TestBlock& tb)
	{
		out << tb.name << endl;
		out << tb.tests.size() << endl;
		for (size_t i = 0; i < tb.tests.size(); i++)
		{
			out << tb[i];
		}
		/*if (tb.score.size() == 0)
			out << 0;
		else*/
			out << tb.score.size() << endl;
		for (size_t i = 0; i < tb.score.size(); i++)
		{
			out << tb.score[i];
		}
		return out;
	}

	friend istream& operator >> (istream& in, TestBlock& tb)
	{
		string temp = "0";
		int size = 0;
		Test tempTest;
		getline(in, tb.name);
		getline(in, temp);
		size = stoi(temp);
		for (size_t i = 0; i < size; i++)
		{
			in >> tempTest;
			tb.tests.push_back(tempTest);
		}
		getline(in, temp);
		size = stoi(temp);
		for (size_t i = 0; i < size; i++)
		{
			in >> temp;
			tb.score.push_back(temp);
		}
		return in;
	}

};


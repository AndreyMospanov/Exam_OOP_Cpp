#include "TestBlock.h"
#include <Windows.h>
#include <string>

void TestBlock::CreateTestBlock(bool createOnly)
{	
	int continuer;
	Test temp;
	if (createOnly)
	{		
		cout << "������� �������� ����������\n";
		cin.ignore(1024, '\n');
		getline(cin, name);		
	}
	do
	{
		temp.CreateTest();
		tests.push_back(temp);
		cout << "�������� ��� ������?\n 1 - ��, ����� ����� - ���\n";
		cin >> continuer;
		system("cls");
	} while (continuer == 1);
}

string TestBlock::RunTestBlock(string username)
{
	SYSTEMTIME today;
	int thisScore = 0;
	int overallTestCost = 0;
	int usersScore;
	string userResult;
	string testResult;
	string date;
	GetLocalTime(&today);
	for (size_t i = 0; i < tests.size(); i++)
	{
		thisScore += tests[i].RunTest();
		overallTestCost += tests[i].Cost();
		system("cls");
	}
	cout << "���� �������� � �����������: " << thisScore << " ������ �� " << overallTestCost << "\n�� 12-������� �����: " << (thisScore / overallTestCost) * 12 << " ������\n";
	system("pause");
	date = to_string(today.wYear) + "." + to_string(today.wMonth) + "." + to_string(today.wDay) + " " + to_string(today.wHour) + ":" + to_string(today.wMinute);	
	usersScore = (thisScore / overallTestCost) * 12;
	userResult += date + " " + name + " " + to_string(usersScore) + "�.";//����� name - ��� �������� �����
	testResult = date + " " + username + " " + to_string(usersScore) + "�.";	
	score.push_back(testResult);

	return userResult;
}

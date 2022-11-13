#include "Test.h"

int Test::GetInt(int left, int right)//����� ��� ����������� ����� ����� �����
{
    int result;
    string input;
    try
    {
        cout << "������� ��������:\n";

        cin >> input;
        for (size_t i = 0; i < input.size(); i++)
        {
            int temp = (int)(input[i]);
            if (temp < 48 || temp >57)
                throw input;
        }
        result = stoi(input);
        if (result < left || result > right)
            throw result;
        return result;
    }
    catch (int)
    {
        cerr << "������. ����� �� ��������� ���������� ��������! ";
        GetInt(left, right);
    }
    catch (string)
    {
        cerr << "������. �������� �� �������� ������! ";
        GetInt(left, right);
    }
}

void Test::CreateTest()
{    
    cin.ignore(1024, '\n');
	cout << "�������� ������\n";    
	getline(cin, question);
	for (size_t i = 0; i < 4; i++)
	{
		cout << "�������� ������� ������ �" << i + 1 << endl;
		getline(cin, variants[i]);
	}
	cout << "�������� ����� ����������� ������\n";
    rightAnsw = GetInt(1, 4);
	cout << "�������� ��������� ������ � ������\n";
	cost = GetInt(0,100);
}

int Test::RunTest()//���������� ���������� ������ �� ���������� ����� ��� 0
{
    int studAnswer;
    cout << "������:\n" << question << endl;
    cout << "��������:\n";
    for (size_t i = 0; i < 4; i++)
    {
        cout << i + 1 << "). " << variants[i] << endl;
    }
    cout << "��� �����. ";
    studAnswer = GetInt(1, 4);

    if (studAnswer == rightAnsw)
        return cost;
    else
        return 0;
}